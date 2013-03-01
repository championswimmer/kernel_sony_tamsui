/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 * Copyright(C) 2011-2012 Foxconn International Holdings, Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
/*===========================================================================

   FIH Comment: Provide mt9v115.c / mt9v115.h base on s5k5cag sensor.

============================================================================*/
#include <linux/debugfs.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <mach/vreg.h>
#include <mach/camera.h>
#include <media/msm_camera.h>
#include "mt9v115.h"

/* HW standby: 1: Enable, 0: Disable */
#define MT9V115_ENABLE_HW_STANDBY 1 //FIH-SW-MM-MC-EnableHWStandby-00+

/* 16bit address - 8 bit context register structure */
#define Q8    0x00000100
#define Q10    0x00000400

/* Product register address */
#define    MT9V115_CID_REG    0x0000//Chip ID address

/* Product register value */
#define    MT9V115_CID        0x2284//Chip ID

/* MCLK */
#define MT9V115_MASTER_CLK_RATE 24000000

#define MT9V115_MSB_MASK            0xFF00
#define MT9V115_LSB_MASK            0x00FF

/* AF Total steps parameters */
#define MT9V115_TOTAL_STEPS_NEAR_TO_FAR    32

#define MT9V115_REG_PREV_FRAME_LEN_1    30
#define MT9V115_REG_PREV_FRAME_LEN_2    31
#define MT9V115_REG_PREV_LINE_LEN_1    32
#define MT9V115_REG_PREV_LINE_LEN_2    33

#define MT9V115_REG_SNAP_FRAME_LEN_1    14
#define MT9V115_REG_SNAP_FRAME_LEN_2    15
#define  MT9V115_REG_SNAP_LINE_LEN_1    16
#define MT9V115_REG_SNAP_LINE_LEN_2    17

static const struct msm_camera_sensor_info *mt9v115_info;

struct mt9v115_work_t {
    struct work_struct work;
};

static struct mt9v115_work_t *mt9v115_sensorw;

static struct i2c_client *mt9v115_client;

struct mt9v115_ctrl_t {
    const struct  msm_camera_sensor_info *sensordata;

    uint32_t sensormode;
    uint32_t fps_divider;/* init to 1 * 0x00000400 */
    uint32_t pict_fps_divider;/* init to 1 * 0x00000400 */
    uint16_t fps;

    uint16_t curr_lens_pos;
    uint16_t curr_step_pos;
    uint16_t my_reg_gain;
    uint32_t my_reg_line_count;
    uint16_t total_lines_per_frame;

    enum mt9v115_resolution_t prev_res;
    enum mt9v115_resolution_t pict_res;
    enum mt9v115_resolution_t curr_res;
};

static bool CSI_CONFIG = false;
static bool STARTUP = false;//FIH-SW-MM-MC-EnableHWStandby-00*
static bool bSubInitDone = false;//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+
static struct mt9v115_ctrl_t *mt9v115_ctrl;
struct platform_device *pdev_mt9v115 = NULL;//Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00+


static DECLARE_WAIT_QUEUE_HEAD(mt9v115_wait_queue);
static DECLARE_WAIT_QUEUE_HEAD(mt9v115_af_wait_queue);
DEFINE_MUTEX(mt9v115_mut);

static uint16_t prev_line_length_pck;
static uint16_t prev_frame_length_lines;
static uint16_t snap_line_length_pck;
static uint16_t snap_frame_length_lines;

/*MM-UW-EnableHWStandby-00+*/
//FIH-SW-MM-MC-EnableHWStandby-00+{
int mt9v115_enter_standby(void)
{
    int rc = 0;
    int i = 0;
    uint16_t read_value;
    printk ("mt9v115_enter_standby \n");    

    fih_i2c_read(mt9v115_client, 0x0018, &read_value, WORD_LEN);   
    read_value = read_value | 0x0001;  
    //rc = fih_set_gpio_output_value(mt9v115_info->sensor_f_pwd, "CAM_VGA_STBY" , HIGH);
    rc = fih_i2c_write(mt9v115_client, 0x0018, read_value, WORD_LEN);
    if (rc < 0) {
        printk("mt9v115_enter_standby: enter standy failed !\n");
    }    

    for (i = 0; i < 80; i++)
    {
        fih_i2c_read(mt9v115_client, 0x0018, &read_value, WORD_LEN);
        read_value = read_value >> 14;
        read_value = read_value & 0x0001;
        
        printk("mt9v115_enter_standby: polling standy mode i = %d\n", i);
        if(read_value == 0x0001)
            break;
        cam_msleep(10);
     }
    cam_msleep(10);

    rc = fih_disable_mclk(mt9v115_info->mclk, MT9V115_MASTER_CLK_RATE);
    if (rc < 0) {
        printk ("mt9v115_enter_standby: disable mclk fail \n");    
    }    
    cam_msleep(5);
    
    return 0;
}

/*MM-UW-improve camera performance-00+*/
int mt9v115_exit_standby(void)
{
    int rc = 0;
    int i = 0;
    uint16_t read_value;
    printk ("mt9v115_exit_standby \n");    

    rc = fih_enable_mclk(mt9v115_info->mclk, MT9V115_MASTER_CLK_RATE);
    if (rc < 0) {
        printk ("mt9v115_exit_standby: enable mclk fail\n");    
        
    }    
    cam_msleep(10);

    fih_i2c_read(mt9v115_client, 0x0018, &read_value, WORD_LEN);
    read_value = read_value & 0xFFFE;

    //rc = fih_set_gpio_output_value(mt9v115_info->sensor_f_pwd, "CAM_VGA_STBY" , HIGH);
    rc = fih_i2c_write(mt9v115_client, 0x0018, read_value, WORD_LEN);
    if (rc < 0) {
        printk("mt9v115_exit_standby: enter standy failed !\n");
    }    

    for (i = 0; i < 80; i++)
    {
        fih_i2c_read(mt9v115_client, 0x0018, &read_value, WORD_LEN);
        read_value = read_value >> 14;
        read_value = read_value & 0x0001;

        printk("mt9v115_exit_standby: polling standy mode i = %d\n", i);
        if(read_value == 0x0000)
            break;
        cam_msleep(10);
     }

    return 0;

}
//FIH-SW-MM-MC-EnableHWStandby-00+}
/*MM-UW-EnableHWStandby-00-*/
/*MM-UW-improve camera performance-00-*/

/*MM-UW-improve camera performance-00+*/
/* FIH-SW3-MM-UW-performance tune-00+*/
//FIH-SW-MM-MC-EnableHWStandby-00*{
/* FIH-SW3-MM-SL-ModifyGPIODefine-01*{ */
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02*{
int mt9v115_power_on(const struct msm_camera_sensor_info *data)
{
    int rc = 0;
    printk("mt9v115_power_on: Start. \n");   

    if(STARTUP == 0)
    {    
        printk("mt9v115_power_on: STARTUP == 0. \n");       
        rc = fih_set_gpio_output_value(mt9v115_info->sensor_f_pwd, "CAM_VGA_STBY" , LOW);//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00*
        if (rc < 0) {
            goto error;
        }    

        rc = fih_set_gpio_output_value(mt9v115_info->vreg_v1p8, "CAM_VDDIO_V1P8" , HIGH);
        if (rc < 0) {
            goto error;
        }    

        rc = fih_set_gpio_output_value(mt9v115_info->vreg_v2p8, "CAM_VAA_V2P8" , HIGH);
        if (rc < 0) {
            goto error;
        }    

        rc = fih_set_gpio_output_value(26, "CAM_5M_RSTN", LOW);
        if (rc < 0) {
            goto error;
        }        

        /*MM-UW-reduce boot time+++*/
        //cam_msleep(500);//cam_msleep(500); //Typical : 500ms
        /*MM-UW-reduce boot time---*/
        rc = fih_enable_mclk(mt9v115_info->mclk, MT9V115_MASTER_CLK_RATE);
        if (rc < 0) {
            goto error;
        }    
    }
    else
    {
        /*MM-UW-fix unbalance warning-00+*/
        printk("mt9v115_power_on: STARTUP == 1. \n");   
        mt9v115_exit_standby();
        //cam_msleep(5);
        /*MM-UW-fix unbalance warning-00-*/
    }

    printk("mt9v115_power_on: End. \n");  
    return rc;
    
error:
    pr_err("mt9v115_power_on: failed !, rc = %d.\n", rc);
    return rc;
}
/* FIH-SW3-MM-UW-performance tune-00-*/
/*MM-UW-improve camera performance-00-*/

int mt9v115_power_off(void)
{
    int rc=0;
    printk ("mt9v115_power_off: Start. \n");

    if(STARTUP == 0)
    {        
        printk("mt9v115_power_off: STARTUP == 0. \n");   
        rc = fih_set_gpio_output_value(mt9v115_info->sensor_f_pwd, "CAM_VGA_STBY" , LOW);//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00*
        if (rc < 0) {
            goto error;
        }    

        rc = fih_set_gpio_output_value(mt9v115_info->vreg_v1p8, "CAM_VDDIO_V1P8" , LOW);
        if (rc < 0) {
            goto error;
        }    
        /*MM-UW-reduce boot time+++*/ 
        cam_msleep(5);//cam_msleep(5); //0~500ms
        /*MM-UW-reduce boot time---*/
        rc = fih_set_gpio_output_value(mt9v115_info->vreg_v2p8, "CAM_VAA_V2P8" , LOW);
        if (rc < 0) {
            goto error;
        }    

        rc = fih_disable_mclk(mt9v115_info->mclk, MT9V115_MASTER_CLK_RATE);
        if (rc < 0) {
            goto error;
        }    
        /*MM-UW-reduce boot time+++*/
        cam_msleep(100);//cam_msleep(100); //Minimum: 100ms    
        /*MM-UW-reduce boot time---*/ 
    }
    else
    {
        /*MM-UW-Standby with MCLK off-00+*/
        printk("mt9v115_power_off: STARTUP == 1. \n");   
        mt9v115_enter_standby();
        /*MM-UW-Standby with MCLK off-00-*/
    }
    printk ("mt9v115_power_off: End. \n");  
    return rc;
error:
    pr_err("mt9v115_power_off: failed !, rc = %d.\n", rc);
    return rc;
}
/* FIH-SW3-MM-SL-ModifyGPIODefine-01*} */
//FIH-SW-MM-MC-EnableHWStandby-00*}

/*MM-UW-improve camera performance-00+*/
/*MM-UW-fix unbalance warning-00+*/
//FIH-SW-MM-MC-EnableHWStandby-00+{
int mt9v115_suspend(struct platform_device *pdev, pm_message_t state)
{    
    int rc;
    printk ("mt9v115_suspend \n");  

    rc = fih_enable_mclk(mt9v115_info->mclk, MT9V115_MASTER_CLK_RATE);
    if (rc < 0) {
        printk("mt9v115_suspend: enable mclk fail \n");
    }   
    cam_msleep(5);

    bFrontCameraIsReset = false;//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*
    STARTUP  = 0;    
    mt9v115_power_off();    
    if (rc < 0) {
        printk("mt9v115_suspend: poweroff fail \n"); 
    }  
    return 0;
}
/*MM-UW-fix unbalance warning-00-*/
/*MM-UW-improve camera performance-00-*/

int mt9v115_resume(struct platform_device *pdev)
{
    int rc = 0;
    printk ("mt9v115_resume \n");  
    //STARTUP  = 0;

    return rc;
}
//FIH-SW-MM-MC-EnableHWStandby-00+}

//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00*{
static int32_t mt9v115_i2c_write_table(
    struct fih_i2c_reg_conf const *reg_conf_tbl,
    int num_of_items_in_table)
{
    int i;
    int32_t rc = -EIO;

    for (i = 0; i < num_of_items_in_table; i++) {

        if (reg_conf_tbl->waddr == 0x001A && reg_conf_tbl->wdata == 0x0106)//Div2-SW6-MM-MC-PortingMt9v115NewSetting_0701-00*
        {
            fih_i2c_no_ack_write(mt9v115_client,
            reg_conf_tbl->waddr, reg_conf_tbl->wdata,
            reg_conf_tbl->width);
            rc = 0x1;
            printk("ByPass: Write Reg_0x001A to 0x0106, no return ACK !\n");
        }
        else
        {
            rc = fih_i2c_write(mt9v115_client,
            reg_conf_tbl->waddr, reg_conf_tbl->wdata,
            reg_conf_tbl->width);
        }
                
        if (rc < 0)
        {
            printk ("mt9v115_i2c_write_table: Write count %d, addr 0x%x, val 0x%x failed !\n", i, reg_conf_tbl->waddr, reg_conf_tbl->wdata);  
            break;
        }

        if (reg_conf_tbl->mdelay_time != 0)
        {        
            cam_msleep(reg_conf_tbl->mdelay_time); /* FIH-SW3-MM-SL-DecreaseLaunchTime-00* */
        }
        reg_conf_tbl++;

    }

    return rc;
}
//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00*}
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02*}

/*=============================================================*/
static void mt9v115_get_pict_fps(uint16_t fps, uint16_t *pfps)
{
    /* input fps is preview fps in Q8 format */
    uint32_t divider, d1, d2;

    d1 = (prev_frame_length_lines * 0x00000400) / snap_frame_length_lines;
    d2 = (prev_line_length_pck * 0x00000400) / snap_line_length_pck;
    divider = (d1 * d2) / 0x400;

    /*Verify PCLK settings and frame sizes.*/
    *pfps = (uint16_t) (fps * divider / 0x400);
}

static uint16_t mt9v115_get_prev_lines_pf(void)
{
    if (mt9v115_ctrl->prev_res == QTR_SIZE)
        return prev_frame_length_lines;
    else
        return snap_frame_length_lines;
}

static uint16_t mt9v115_get_prev_pixels_pl(void)
{
    if (mt9v115_ctrl->prev_res == QTR_SIZE)
        return prev_line_length_pck;
    else
        return snap_line_length_pck;
}

static uint16_t mt9v115_get_pict_lines_pf(void)
{
    if (mt9v115_ctrl->prev_res == QTR_SIZE)
        return prev_frame_length_lines;
    else
        return snap_frame_length_lines;
}

static uint16_t mt9v115_get_pict_pixels_pl(void)
{
    if (mt9v115_ctrl->prev_res == QTR_SIZE)
        return prev_line_length_pck;
    else
        return snap_line_length_pck;
}

static uint32_t mt9v115_get_pict_max_exp_lc(void)
{
    if (mt9v115_ctrl->prev_res == QTR_SIZE)
        return prev_frame_length_lines;
    else
        return snap_frame_length_lines;
}

/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01*{ */
static int32_t mt9v115_set_fps(uint16_t fps)
{
    int32_t rc = 0;

    if(fps <=15){ //fps=15
        printk("mt9v115_set_fps: mt9v115_i2c_write_table (reg_fps_15_tbl) \n");
        mt9v115_i2c_write_table(&mt9v115_regs.reg_fps_15_tbl[0], mt9v115_regs.reg_fps_15_tbl_size);    
        if (rc < 0){
            printk("mt9v115_set_fps: mt9v115_i2c_write_table(reg_fps_15_tbl) failed !\n");
            return rc;
        }
    }else{ //fps =30 
        printk("mt9v115_set_fps: mt9v115_i2c_write_table (reg_fps_30_tbl) \n");
        mt9v115_i2c_write_table(&mt9v115_regs.reg_fps_30_tbl[0], mt9v115_regs.reg_fps_30_tbl_size); 
        if (rc < 0){
            printk("mt9v115_set_fps: mt9v115_i2c_write_table(reg_fps_30_tbl) failed !\n");
            return rc;
        }

    }

    return rc;

}
/* FIH-SW3-MM-SL-SetFPSForRecordMMS-01*} */

static int32_t mt9v115_write_exp_gain(uint16_t gain, uint32_t line)
{
    int32_t rc = 0;
    uint16_t max_legal_gain  = 0x0200;
    uint8_t gain_msb, gain_lsb;
    uint8_t intg_time_msb, intg_time_lsb;

    if (gain > max_legal_gain)
        gain = max_legal_gain;

    /* update gain registers */
    gain_msb = (uint8_t) ((gain & 0xFF00) >> 8);
    gain_lsb = (uint8_t) (gain & 0x00FF);

    intg_time_msb = (uint8_t) ((line & 0xFF00) >> 8);
    intg_time_lsb = (uint8_t) (line & 0x00FF);

    /*mt9v115_group_hold_on();

    mt9v115_i2c_write_b_sensor(0x0204, gain_msb); //Analogue Gain 
    mt9v115_i2c_write_b_sensor(0x0205, gain_lsb);

    //Coarse Integration Time 
    mt9v115_i2c_write_b_sensor(0x0202, intg_time_msb);
    mt9v115_i2c_write_b_sensor(0x0203, intg_time_lsb);
    mt9v115_group_hold_off()*/;

    return rc;
}

static int32_t mt9v115_set_pict_exp_gain(uint16_t gain, uint32_t line)
{
    int32_t rc = 0;

    rc = mt9v115_write_exp_gain(gain, line);
    return rc;
}

/*MM-UW-improve camera performance-00+*/
/*MM-UW-fix unbalance warning-00+*/
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02*{
static int32_t mt9v115_sensor_setting(int update_type, int rt)
{
    int32_t rc = 0;
    struct msm_camera_csi_params mt9v115_csi_params;

    switch (update_type) {
    case REG_INIT:
        if (rt == RES_PREVIEW || rt == RES_CAPTURE) 
        {
            printk("mt9v115_sensor_setting: case REG_INIT \n");
            bSubInitDone = false;//FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+

            /* set sensor init table */
            rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_init_tbl[0], mt9v115_regs.reg_init_tbl_size);
            if (rc < 0)
            {
                printk("mt9v115_sensor_setting: mt9v115_i2c_write_table(reg_init_tbl) failed !\n");
                return rc;
            }
            printk("mt9v115_sensor_setting: mt9v115_i2c_write_table(reg_init_tbl) success. \n");

            CSI_CONFIG = false;
            STARTUP = MT9V115_ENABLE_HW_STANDBY;//FIH-SW-MM-MC-EnableHWStandby-00+
            //Remove cam_msleep() because we implement polling machine in reg_init_tbl.
            //cam_msleep(10);//Waitting for sensor init done.
            return rc;
        }
        break;

    case UPDATE_PERIODIC:
        if ((rt == RES_PREVIEW) && (CSI_CONFIG == false)) 
        {
            printk("mt9v115_sensor_setting: case UPDATE_PERIODIC \n");

            //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*{
            if (bFrontCameraIsReset == false)
            {
                /* stop streaming */
                rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_stop_tbl[0], mt9v115_regs.reg_stop_tbl_size);//Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00*
                //rc = fih_i2c_write(mt9v115_client, 0x8400, 0x01, BYTE_LEN);
                if (rc < 0)
                {
                    printk("mt9v115_sensor_setting: Stop streaming failed !\n");
                    return rc;
                }
            }
            //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*}
            printk("mt9v115_sensor_setting: Stop streaming success, bFrontCameraIsReset = %d. \n", bFrontCameraIsReset);
            //Remove cam_msleep() because we implement polling machine in reg_stop_tbl and reg_start_tbl.
            //cam_msleep(50);//Waitting for streaming stop.

            if (CSI_CONFIG == false) {
                printk("mt9v115_sensor_setting: CSI_CONFIG  = 0, Pre CSI config. \n");
                msm_camio_vfe_clk_rate_set(192000000);
                mt9v115_csi_params.lane_cnt = 1;
                mt9v115_csi_params.data_format = CSI_8BIT;
                mt9v115_csi_params.lane_assign = 0xe4;
                mt9v115_csi_params.dpcm_scheme = 0;
                mt9v115_csi_params.settle_cnt = 20;
                rc = msm_camio_csi_config(&mt9v115_csi_params);
                cam_msleep(20);//cam_msleep(100);//Waitting for csi config done.
                
                CSI_CONFIG = true;
            }

            //FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00*{
            if (bSubInitDone == true)
            {
                /* Sensor start streaming */
                rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_start_tbl[0], mt9v115_regs.reg_start_tbl_size);//Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00*
                //rc = fih_i2c_write(mt9v115_client, 0x8400, 0x02, BYTE_LEN);
                if (rc < 0)
                {
                    printk("mt9v115_sensor_setting: Sensor start streaming failed !\n");
                    return rc;
                }
                printk("mt9v115_sensor_setting: Sensor start streaming success, bSubInitDone = %d .\n", bSubInitDone);
            }
            //FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00*}
        }
        break;
    default:
        rc = -EINVAL;
        break;
    }

    return rc;
}
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02*}
/*MM-UW-fix unbalance warning-00-*/
/*MM-UW-improve camera performance-00-*/

static int32_t mt9v115_video_config(int mode)
{
    int32_t rc = 0;
    int rt;

    printk("mt9v115_video_config---------------E\n");

    /* change sensor resolution if needed */
    // Check resolution 
    if (mt9v115_ctrl->prev_res == QTR_SIZE){
        rt = RES_PREVIEW;
    }
    else
        rt = RES_CAPTURE;
    
    if (mt9v115_sensor_setting(UPDATE_PERIODIC, rt) < 0)
        return rc;

    mt9v115_ctrl->curr_res = mt9v115_ctrl->prev_res;
    mt9v115_ctrl->sensormode = mode;

    printk("mt9v115_video_config---------------X\n");
    return rc;
}

static int32_t mt9v115_snapshot_config(int mode)
{
    int32_t rc = 0;
    //int rt;
    printk("mt9v115_snapshot_config---------------E\n");
    /*change sensor resolution if needed */
#if 0
    if (mt9v115_ctrl->curr_res != mt9v115_ctrl->pict_res) {
        if (mt9v115_ctrl->pict_res == QTR_SIZE)
            rt = RES_PREVIEW;
        else
            rt = RES_CAPTURE;
        if (mt9v115_sensor_setting(UPDATE_PERIODIC, rt) < 0)
            return rc;
    }
#endif
    mt9v115_ctrl->curr_res = mt9v115_ctrl->pict_res;
    mt9v115_ctrl->sensormode = mode;
    return rc;
}

static int32_t mt9v115_raw_snapshot_config(int mode)
{
    int32_t rc = 0;
    //int rt;

    /* change sensor resolution if needed */
#if 0
    if (mt9v115_ctrl->curr_res != mt9v115_ctrl->pict_res) {
        if (mt9v115_ctrl->pict_res == QTR_SIZE)
            rt = RES_PREVIEW;
        else
            rt = RES_CAPTURE;
        if (mt9v115_sensor_setting(UPDATE_PERIODIC, rt) < 0)
            return rc;
    }
#endif
    mt9v115_ctrl->curr_res = mt9v115_ctrl->pict_res;
    mt9v115_ctrl->sensormode = mode;
    return rc;
}

static int32_t mt9v115_set_sensor_mode(int mode,
        int res)
{
    int32_t rc = 0;

    switch (mode) {
    case SENSOR_PREVIEW_MODE:
        rc = mt9v115_video_config(mode);
        break;
    case SENSOR_SNAPSHOT_MODE:
        rc = mt9v115_snapshot_config(mode);
        break;
    case SENSOR_RAW_SNAPSHOT_MODE:
        rc = mt9v115_raw_snapshot_config(mode);
        break;

    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00*{
    case SENSOR_RESET_MODE:
        printk("mt9v115_set_sensor_mode: SENSOR_RESET_MODE---------------E\n");
        
        //01. Re-set flag variables.
        STARTUP = 0;
        bFrontCameraIsReset = true;//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*

        //02. Re-config main camera pin.
        rc = fih_set_gpio_output_value(mt9v115_info->sensor_pwd, "CAM_5M_STBYN", LOW);
        if (rc < 0) {
            printk("mt9v115_set_sensor_mode: Re-config main camera CAM_5M_STBYN pin for reset failed !\n");
            return rc;
        }   

        rc = fih_set_gpio_output_value(mt9v115_info->sensor_reset, "CAM_5M_RSTN", LOW);
        if (rc < 0) {
            printk("mt9v115_set_sensor_mode: Re-config main camera CAM_5M_RSTN pin for reset failed !\n");
            return rc;
        }   
        cam_msleep(5);// >0

        //03. Power off.
        rc = mt9v115_power_off();
        if (rc < 0) {
            printk("mt9v115_set_sensor_mode: mt9v115_power_off for reset failed !\n");
            return rc;
        }
        //Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00*{
        cam_msleep(200);//Wait power off done.
        //Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00*}

        //04. Power on.
        rc = mt9v115_power_on(mt9v115_info);
        if (rc < 0) {
            printk("mt9v115_set_sensor_mode: mt9v115_power_on for reset failed !\n");
            return rc;
        }

        //05. INIT main reg table.
        rc = mt9v115_sensor_setting(REG_INIT, RES_PREVIEW);
        if (rc < 0) {
            printk("mt9v115_set_sensor_mode: INIT main reg table for reset failed !\n");
            return rc;
        }

        //06. Stop streaming and config CSI .
        rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_stop_tbl[0], mt9v115_regs.reg_stop_tbl_size);
        if (rc < 0)
        {
            printk("mt9v115_set_sensor_mode: Stop streaming for reset failed !\n");
            return rc;
        }

        rc = mt9v115_sensor_setting(UPDATE_PERIODIC, RES_PREVIEW);
        if (rc < 0) {
            printk("mt9v115_set_sensor_mode: Config CSI for reset failed !\n");
            return rc;
        }

        //07. INIT sub reg table.
        rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_sub_init_tbl[0], mt9v115_regs.reg_sub_init_tbl_size);
        if (rc < 0)
        {
            printk("mt9v115_set_sensor_mode: INIT sub reg table for reset failed !\n");
            return rc;
        }
        bSubInitDone = true;
        printk("mt9v115_set_sensor_mode: bSubInitDone = %d .\n", bSubInitDone);
    
        //08. Start streaming.
        rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_start_tbl[0], mt9v115_regs.reg_start_tbl_size);
        if (rc < 0)
        {
            printk("mt9v115_set_sensor_mode: Start streaming for reset failed !\n");
            return rc;
        }
        
        mt9v115_ctrl->curr_res = mt9v115_ctrl->prev_res;
        mt9v115_ctrl->sensormode = 0;

        printk("mt9v115_set_sensor_mode: SENSOR_RESET_MODE---------------X\n");      
              break;
    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00*}

    default:
        rc = -EINVAL;
        break;
    }
    return rc;
}

#if 0
static int32_t mt9v115_power_down(void)
{
    gpio_direction_output(23, 0);
    gpio_direction_output(26, 0);

    return 0;
}
#endif

static int mt9v115_probe_init_done(const struct msm_camera_sensor_info *data)
{
    int rc = -EBADF;

    if (data->sensor_reset_enable) {
        gpio_direction_output(data->sensor_reset, 0);
        gpio_free(data->sensor_reset);
    }

    rc = mt9v115_power_off();
    if (rc < 0)
        goto error;
        
    printk("mt9v115_probe_init_done: Done. \n");
    return rc;
error:
    printk("mt9v115_probe_init_done: Failed ! \n");
    return rc;
}

static int mt9v115_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
    int32_t rc = 0;
    uint16_t  chip_id = 0;

    if (data->sensor_reset_enable) {
        rc = gpio_request(data->sensor_reset, "mt9v115");
        if (!rc) {
            gpio_direction_output(data->sensor_reset, 0);
            gpio_set_value_cansleep(data->sensor_reset, 1);
            /*MM-UW-reduce boot time---*/
            cam_msleep(20);
            /*MM-UW-reduce boot time---*/
        } else
            goto init_probe_done;
    }

    /* Power on for read sensor ID */
    rc = mt9v115_power_on(data);
    if (rc < 0)
        goto init_probe_fail;

    /* 3. Read sensor Chip ID: */
    rc = fih_i2c_read(mt9v115_client, MT9V115_CID_REG, &chip_id, WORD_LEN);//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-02*
    if (rc < 0)
        goto init_probe_fail;
    printk("mt9v115 chip_id = 0x%x \n", chip_id);

    /* 4. Compare Chip and Model ID: */
    if (chip_id != MT9V115_CID) {
        rc = -ENODEV;
        printk(KERN_INFO "Probe init fail !, Chip ID != %x .\n", MT9V115_CID);
        goto init_probe_fail;
    }
    
    goto init_probe_done;

init_probe_fail:
    if (data->sensor_reset_enable) {
        gpio_direction_output(data->sensor_reset, 0);
        gpio_free(data->sensor_reset);
    }
init_probe_done:
    printk(KERN_INFO " mt9v115_probe_init_sensor finishes\n");
    return rc;
}


int mt9v115_sensor_open_init(const struct msm_camera_sensor_info *data)
{
    int32_t rc = 0;

    printk("Calling mt9v115_sensor_open_init. \n");

    mt9v115_ctrl = kzalloc(sizeof(struct mt9v115_ctrl_t), GFP_KERNEL);
    if (!mt9v115_ctrl) {
        printk("mt9v115_sensor_open_init: kzalloc() failed !\n");
        rc = -ENOMEM;
        goto init_done;
    }
    mt9v115_ctrl->fps_divider = 1 * 0x00000400;
    mt9v115_ctrl->pict_fps_divider = 1 * 0x00000400;
    mt9v115_ctrl->prev_res = QTR_SIZE;
    mt9v115_ctrl->pict_res = FULL_SIZE;

    if (data != NULL)
        mt9v115_ctrl->sensordata = data;

    prev_frame_length_lines =640;
    prev_line_length_pck = 480;
    snap_frame_length_lines = 640;
    snap_line_length_pck = 480;

    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*{
    // Check main camera state before power on front camera.
    if (bMainCameraIsReset == true)
    {
        printk("mt9v115_sensor_open_init: Re-Set for MAIN_SENSOR_RESET\n");
        STARTUP = 0;
        bMainCameraIsReset = false;
    }
    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*}

    /* Power on and enable mclk */
    rc = mt9v115_power_on(data);
    if (rc < 0) {
        printk("mt9v115_sensor_open_init: mt9v115_power_on() failed !\n");
        goto init_fail;
    }    
    
    //FIH-SW-MM-MC-EnableHWStandby-00*{
    if(STARTUP == 0)
    {    
        rc = mt9v115_sensor_setting(REG_INIT, RES_PREVIEW);
        if (rc < 0) {
            printk("mt9v115_sensor_open_init: mt9v115_sensor_setting(REG_INIT, RES_PREVIEW) failed !\n");
            goto init_fail;
        }
    }
    //FIH-SW-MM-MC-EnableHWStandby-00*}

    mt9v115_ctrl->fps = 30 * Q8;

    printk("mt9v115_sensor_open_init: init_done\n");
    goto init_done;
    
init_fail:
    printk("mt9v115_sensor_open_init: init_fail\n");
    mt9v115_probe_init_done(data);
    
init_done:
    return rc;
}

static int mt9v115_init_client(struct i2c_client *client)
{
    /* Initialize the MSM_CAMI2C Chip */
    init_waitqueue_head(&mt9v115_wait_queue);
    return 0;
}

static const struct i2c_device_id mt9v115_i2c_id[] = {
    {"mt9v115", 0},
    { }
};

static int mt9v115_i2c_probe(struct i2c_client *client,
        const struct i2c_device_id *id)
{
    int rc = 0;
    CDBG("mt9v115_probe called!\n");

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        CDBG("i2c_check_functionality failed\n");
        goto probe_failure;
    }

    mt9v115_sensorw = kzalloc(sizeof(struct mt9v115_work_t), GFP_KERNEL);
    if (!mt9v115_sensorw) {
        CDBG("kzalloc failed.\n");
        rc = -ENOMEM;
        goto probe_failure;
    }

    i2c_set_clientdata(client, mt9v115_sensorw);
    mt9v115_init_client(client);
    mt9v115_client = client;

    CDBG("mt9v115_probe successed! rc = %d\n", rc);
    return 0;

probe_failure:
    CDBG("mt9v115_probe failed! rc = %d\n", rc);
    return rc;
}

static int __devexit mt9v115_remove(struct i2c_client *client)
{
    struct mt9v115_work_t *sensorw = i2c_get_clientdata(client);
    free_irq(client->irq, sensorw);
    mt9v115_client = NULL;
    kfree(sensorw);
    return 0;
}

static struct i2c_driver mt9v115_i2c_driver = {
    .id_table = mt9v115_i2c_id,
    .probe  = mt9v115_i2c_probe,
    .remove = __exit_p(mt9v115_i2c_remove),
    .driver = {
        .name = "mt9v115",
    },
};

int mt9v115_sensor_config(void __user *argp)
{
    struct sensor_cfg_data cdata;
    long   rc = 0;
    if (copy_from_user(&cdata,
                (void *)argp,
                sizeof(struct sensor_cfg_data)))
        return -EFAULT;
    mutex_lock(&mt9v115_mut);
    printk("mt9v115_sensor_config: cfgtype = %d\n", cdata.cfgtype);

    //FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+{
    printk("mt9v115_sensor_config: bSubInitDone = %d .\n", bSubInitDone);
    /* set sensor sub init table */
    if ((cdata.cfgtype != CFG_SET_MODE)&&(bSubInitDone != true))
    {
        rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_sub_init_tbl[0], mt9v115_regs.reg_sub_init_tbl_size);
        if (rc < 0)
        {
            printk("mt9v115_sensor_config: mt9v115_i2c_write_table(reg_sub_init_tbl) failed !\n");
            return rc;
        }
        bSubInitDone = true;
        printk("mt9v115_sensor_config: mt9v115_i2c_write_table(reg_sub_init_tbl) success, bSubInitDone = %d .\n", bSubInitDone);

        /* Sensor start streaming */
        rc = mt9v115_i2c_write_table(&mt9v115_regs.reg_start_tbl[0], mt9v115_regs.reg_start_tbl_size);//Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00*
        //rc = fih_i2c_write(mt9v115_client, 0x8400, 0x02, BYTE_LEN);
        if (rc < 0)
        {
            printk("mt9v115_sensor_config: Sensor start streaming failed !\n");
            return rc;
        }
        printk("mt9v115_sensor_config: Sensor start streaming success. \n");
    }
    //FIH-SW-MM-MC-OptimizeCameraForLaunchTime-00+}
    
    switch (cdata.cfgtype) {
    case CFG_GET_PICT_FPS:
        mt9v115_get_pict_fps(
            cdata.cfg.gfps.prevfps,
            &(cdata.cfg.gfps.pictfps));

        if (copy_to_user((void *)argp,
            &cdata,
            sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_GET_PREV_L_PF:
        cdata.cfg.prevl_pf =
            mt9v115_get_prev_lines_pf();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_GET_PREV_P_PL:
        cdata.cfg.prevp_pl =
            mt9v115_get_prev_pixels_pl();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_GET_PICT_L_PF:
        cdata.cfg.pictl_pf =
            mt9v115_get_pict_lines_pf();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_GET_PICT_P_PL:
        cdata.cfg.pictp_pl =
            mt9v115_get_pict_pixels_pl();
        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_GET_PICT_MAX_EXP_LC:
        cdata.cfg.pict_max_exp_lc =
            mt9v115_get_pict_max_exp_lc();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_SET_FPS:
    case CFG_SET_PICT_FPS:
        rc = mt9v115_set_fps(cdata.cfg.v_fps);
        break;
    case CFG_SET_EXP_GAIN:
        rc = mt9v115_write_exp_gain(cdata.cfg.exp_gain.gain,
                cdata.cfg.exp_gain.line);
        break;
    case CFG_SET_PICT_EXP_GAIN:
        rc = mt9v115_set_pict_exp_gain(cdata.cfg.exp_gain.gain,
                cdata.cfg.exp_gain.line);
        break;
    case CFG_SET_MODE:
        rc = mt9v115_set_sensor_mode(cdata.mode, cdata.rs);
        break;
    case CFG_PWR_DOWN:
        //rc = mt9v115_power_down();
        break;
    case CFG_GET_AF_MAX_STEPS:
        cdata.max_steps = MT9V115_TOTAL_STEPS_NEAR_TO_FAR;
        if (copy_to_user((void *)argp,
                    &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;

    //case CFG_SET_EFFECT:
        //rc = mt9v115_set_default_focus(cdata.cfg.effect);
        //break;
    default:
        rc = -EFAULT;
        break;
    }
    mutex_unlock(&mt9v115_mut);

    return rc;
}

static int mt9v115_sensor_release(void)
{
    int rc = -EBADF;
    printk ("mt9v115_sensor_release: E \n");    
    
    mutex_lock(&mt9v115_mut);
    //mt9v115_enter_standby();
    //cam_msleep(200);//Waitting for sensor into standby done.
    
    //mt9v115_power_down();

    rc = mt9v115_power_off();

    kfree(mt9v115_ctrl);
    mt9v115_ctrl = NULL;
    CSI_CONFIG = false;
    /*MM-UW-reduce boot time+++*/
    cam_msleep(100);
    /*MM-UW-reduce boot time---*/
    
    printk("mt9v115_release completed. \n");
    mutex_unlock(&mt9v115_mut);
    
    printk ("mt9v115_sensor_release: X \n");
    return rc;
}

static int mt9v115_sensor_probe(const struct msm_camera_sensor_info *info,
        struct msm_sensor_ctrl *s)
{
    int rc = 0;

    printk("mt9v115_sensor_probe: E \n");

    mt9v115_info = info;//Here to backup power and pin info for power on/off function.
    STARTUP = 0;//FIH-SW-MM-MC-EnableHWStandby-00+

    rc = i2c_add_driver(&mt9v115_i2c_driver);
    if (rc < 0 || mt9v115_client == NULL) {
        rc = -ENOTSUPP;
        pr_err("mt9v115: I2C add driver failed");
        goto probe_fail_1;
    }
    printk("mt9v115_sensor_probe: Add mt9v115 I2C driver success ~ \n");

    //msm_camio_clk_rate_set(MT9V115_MASTER_CLK_RATE);//24000000
    //cam_msleep(20);

    rc = mt9v115_probe_init_sensor(info);
    if (rc < 0)
        goto probe_fail_2;

    s->s_init = mt9v115_sensor_open_init;
    s->s_release = mt9v115_sensor_release;
    s->s_config  = mt9v115_sensor_config;
    s->s_camera_type = FRONT_CAMERA_2D;
    s->s_mount_angle = info->sensor_platform_info->mount_angle;

    mt9v115_probe_init_done(info);

    printk("mt9v115_sensor_probe: X \n");
    return rc;

probe_fail_2:
    i2c_del_driver(&mt9v115_i2c_driver);
probe_fail_1:
    printk("mt9v115_sensor_probe: X : SENSOR PROBE FAILS !\n");
    return rc;
}

static int __devinit mt9v115_probe(struct platform_device *pdev)
{
    printk("mt9v115_probe: Register mt9v115 sensor to msm_camera_drv. \n");
    pdev_mt9v115 = pdev;//Div2-SW6-MM-MC-EnhanceStabilityForFrontCamera-00+
    return msm_camera_drv_start(pdev, mt9v115_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
    .probe = mt9v115_probe,
    .driver = {
        .name = "msm_camera_mt9v115",
        .owner = THIS_MODULE,
    },
    .suspend = mt9v115_suspend,
    .resume = mt9v115_resume,
};

static int __init mt9v115_init(void)
{
    return platform_driver_register(&msm_camera_driver);
}

module_init(mt9v115_init);
MODULE_DESCRIPTION("Aptina VGA SOC sensor driver");
MODULE_LICENSE("GPL v2");
