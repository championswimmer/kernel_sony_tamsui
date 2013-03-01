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

#include <linux/debugfs.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <mach/vreg.h>
#include <mach/pmic.h>/* FIH-SW3-MM-UW-AF power-00+*/
#include <mach/camera.h>
#include <media/msm_camera.h>
#include "isx006.h"
/*MM-UW-support AF+++*/
#include <linux/regulator/consumer.h>
/*MM-UW-support AF---*/
#include <linux/kthread.h>//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+

/* HW standby: 1: Enable, 0: Disable */
#define ISX006_ENABLE_HW_STANDBY 1 //FIH-SW-MM-MC-EnableHWStandby-00+

/* 16bit address - 8 bit context register structure */
#define Q8    0x00000100
#define Q10    0x00000400

/* MCLK */
#define ISX006_MASTER_CLK_RATE 24000000

/* AF Total steps parameters */
#define ISX006_TOTAL_STEPS_NEAR_TO_FAR    32

#define ISX006_REG_PREV_FRAME_LEN_1    30
#define ISX006_REG_PREV_FRAME_LEN_2    31
#define ISX006_REG_PREV_LINE_LEN_1    32
#define ISX006_REG_PREV_LINE_LEN_2    33

#define ISX006_REG_SNAP_FRAME_LEN_1    14
#define ISX006_REG_SNAP_FRAME_LEN_2    15
#define ISX006_REG_SNAP_LINE_LEN_1    16
#define ISX006_REG_SNAP_LINE_LEN_2    17
/*MM-UW-support AF 02+*/
/*MM-UW-support AF 01+*/
/*MM-UW-support AF+++*/
/* FIH-SW3-MM-UW-performance tuning-00+*/
#define ISX006_OM_RETRY_COUNT 100
#define ISX006_CM_RETRY_COUNT 150
/* FIH-SW3-MM-UW-flash tuning-04+*/
#define ISX006_AE_RETRY_COUNT 30
/* FIH-SW3-MM-UW-flash tuning-04-*/
#define ISX006_AF_RETRY_COUNT 250
/* FIH-SW3-MM-UW-performance tuning-00+*/
/*MM-UW-support AF---*/
/*MM-UW-support AF 01+*/
/*MM-UW-support AF 02-*/
//MTD-SW3-MM-UW-camframe timeout-00+{    
static const struct msm_camera_sensor_info *isx006_info;
//MTD-SW3-MM-UW-camframe timeout-00+}

//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+{
enum Exit_Standby_Action {
	ACT_MCLK_ON,
	ACT_EXIT_STANDBY
};

struct platform_device *pdev_isx006 = NULL;
//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+}

/* FIH-SW3-MM-UW-write OTP setting-00+*/
static uint32_t OTP_0_value = 0xFFFFFFFF; //bit[0:31 ] 
static uint32_t OTP_1_value = 0xFFFFFFFF; //bit[32:63 ] 
static uint32_t OTP_2_value = 0xFFFFFFFF; //bit[64:95 ] 
static uint16_t AF_A_value = 0xFFFF; 
static uint16_t AF_B_value = 0xFFFF; 
static uint16_t AF_C_value = 0xFFFF; 
static uint16_t AF_D_value = 0xFFFF; 
static uint16_t AF_E_value = 0xFFFF; 
static uint16_t AF_F_value = 0xFFFF; 
static uint16_t AF_G_value = 0xFFFF; 
static uint16_t AF_H_value = 0xFFFF; 
static uint16_t C_NR = 0xFFFF; 
static uint16_t C_NB = 0xFFFF; 
static uint16_t C_PR = 0xFFFF; 
static uint16_t C_PB = 0xFFFF; 
static uint16_t Shading_index = 0xFFFF;

static uint8_t vendor_id = 0x00; 
/* FIH-SW3-MM-UW-flash tuning-04+*/
uint32_t AESCL_AUTO = 0xFFFF; //0x0288
uint32_t ERRSCL_AUTO = 0xFFFF; //0x0284
uint32_t AESCL_NOW = 0xFFFF; //0x028A
uint32_t ERRSCL_NOW = 0xFFFF; //0x0286
/* FIH-SW3-MM-UW-flash tuning-04-*/
/*MM-UW-fix high AF power-00+*/
static uint16_t current_af_mode = 0;
/*MM-UW-fix high AF power-00-*/
static bool torch_enable = false;
static bool flash_enable = false;
/* FIH-SW3-MM-UW-modify far AF-00+*/
/* FIH-SW3-MM-UW-modify touch AF-00+*/
/* FIH-SW3-MM-UW-fast AF-01+*/
static int8_t AF_type = 0;
static bool AF_skip = false;
static bool f_CAF = false;
/* FIH-SW3-MM-UW-fast AF-01-*/
/* FIH-SW3-MM-UW-modify touch AF-00-*/
/* FIH-SW3-MM-UW-modify far AF-00-*/
static int8_t is_flash_enable = 0; /*MTD-MM-SL-ModifyPicDetailInfo-01+*/

static uint16_t slave_add;
/* FIH-SW3-MM-UW-set AF range-00+*/
static uint16_t AF_full_range = 0;
/* FIH-SW3-MM-UW-set AF range-00-*/

#define ISX006_PARALLEL_SADDR 0x1A
/* FIH-SW3-MM-UW-write OTP setting-00-*/

struct isx006_work_t {
    struct work_struct work;
};

static struct isx006_work_t *isx006_sensorw;
//static struct isx006_work_t *isx006_af_sensorw;
//static struct i2c_client *isx006_af_client;
static struct i2c_client *isx006_client;
/*MM-UW-support AF 01+*/
static enum isx006_mode CameraMode;
/*MM-UW-support AF 01-*/
struct delayed_work work;
struct work_struct irq_work;

#define    ISX006_CID_REG    0x0000//Chip ID address
#define    ISX006_CID_v1        0x3009//Chip ID
#define    ISX006_CID_v2        0x3013//Chip ID

#define isx006_MSB_MASK            0xFF00
#define isx006_LSB_MASK            0x00FF

struct isx006_ctrl_t {
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

    enum isx006_resolution_t prev_res;
    enum isx006_resolution_t pict_res;
    enum isx006_resolution_t curr_res;
};

static bool CSI_CONFIG = false;
static bool STARTUP = false;
static struct isx006_ctrl_t *isx006_ctrl;
///*MTD-MM-SL-ModifyPicDetailInfo-01-*/ static bool LowLight = false; /* FIH-SW3-MM-UW-fix night capture fail-00+*/


static DECLARE_WAIT_QUEUE_HEAD(isx006_wait_queue);
static DECLARE_WAIT_QUEUE_HEAD(isx006_af_wait_queue);
DEFINE_MUTEX(isx006_mut);

static uint16_t prev_line_length_pck;
static uint16_t prev_frame_length_lines;
static uint16_t snap_line_length_pck;
static uint16_t snap_frame_length_lines;
/* FIH-SW3-MM-URI-Add WB-00+ */
#ifdef CONFIG_FIH_BRIGHTNESS
static int16_t isx006_brightness = 0;
#endif
#ifdef CONFIG_FIH_WB
static int16_t isx006_wb = 0;
#endif
#ifdef CONFIG_FIH_METRY
static int16_t isx006_meter = 0;
#endif
#ifdef CONFIG_FIH_SCENE
static int16_t isx006_scene = 0;
#endif
/* FIH-SW3-MM-URI-Add WB-00- */

//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+{
static struct task_struct *reg_init_thread = NULL;
static bool bRegInitDone = false;
//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+}

static long isx006_set_scene(int scene);//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+
bool isx006_get_AE_value(void); /*MTD-MM-SL-ModifyPicDetailInfo-01+*/
int isx006_power_off(void);

//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+{
static int isx006_i2c_rxdata(unsigned short saddr,
        unsigned char *rxdata, int length)
{
    uint16_t address;

    struct i2c_msg msgs[] = {
        {
            .addr   = saddr,
            .flags = 0,
            .len   = 2,
            .buf   = rxdata,
        },
        {
            .addr   = saddr,
            .flags = I2C_M_RD,
            .len   = length,
            .buf   = rxdata,
        },
    };
    address = (*rxdata << 8)+ *(rxdata+1);

    if (i2c_transfer(isx006_client->adapter, msgs, 2) < 0) {
        printk("isx006_i2c_rxdata faild 0x%x\n", saddr);
        return -EIO;
    }
    return 0;
}

static int isx006_i2c_rxdata_nonAck(unsigned short saddr,
        unsigned char *rxdata, int length)
{
    uint16_t address;
    int i = 0;
    struct i2c_msg msgs[] = {
        {
            .addr   = saddr,
            .flags = 0,
            .len   = 2,
            .buf   = rxdata,
        },
        {
            .addr   = saddr,
            .flags = I2C_M_RD,
            .len   = length,
            .buf   = rxdata,
        },
    };
    //printk("isx006_i2c_rxdata_nonAck: enter\n");
    
    address = (*rxdata << 8)+ *(rxdata+1);

    for(i = 0; i < 50; i++)
    {
        if (i2c_transfer(isx006_client->adapter, msgs, 2) >= 0) {
                //printk("isx006_i2c_rxdata_nonAck pass 0x%x\n", saddr);
                return 0;
        }
        cam_msleep(10);
    }
    printk("isx006_i2c_rxdata_nonAck timeout 0x%x\n", saddr);
    return -EIO;
}


/*MM-UW-improve camera close performance-00+*/
static int32_t isx006_i2c_read_parallel(unsigned short saddr,
    unsigned short raddr, unsigned short *rdata, enum fih_i2c_width width)
{
    int32_t rc = 0;
    unsigned char buf[2];

    if (!rdata)
        return -EIO;

    memset(buf, 0, sizeof(buf));

    switch (width) {
    case WORD_LEN: //W_Addr : W_Data
        buf[0] = (raddr & isx006_MSB_MASK) >> 8;
        buf[1] = (raddr & isx006_LSB_MASK);


        rc = isx006_i2c_rxdata(saddr, buf, 2);
        if (rc < 0) {
            printk("isx006_i2c_read_parallel(WORD_LEN) 0x%x failed!\n", raddr);
            return rc;
        }

        *rdata = buf[1] << 8 | buf[0];
        break;

    case BYTE_LEN: //W_Addr : B_Data
        buf[0] = (raddr & isx006_MSB_MASK) >> 8;
        buf[1] = (raddr & isx006_LSB_MASK);

        rc = isx006_i2c_rxdata(saddr, buf, 2);
        if (rc < 0) {
            printk("isx006_i2c_read_parallel(BYTE_LEN) 0x%x failed!\n", raddr);
            return rc;
        }

        *rdata = buf[0];
        break;
    
    default:
        break;
    }

    return rc;
}
/*MM-UW-improve camera close performance-00-*/

static int32_t isx006_i2c_read_parallel_nonAck(unsigned short saddr,
    unsigned short raddr, unsigned short *rdata, enum fih_i2c_width width)
{
    int32_t rc = 0;
    unsigned char buf[2];

    if (!rdata)
        return -EIO;

    memset(buf, 0, sizeof(buf));

    switch (width) {
    case WORD_LEN: //W_Addr : W_Data
        buf[0] = (raddr & isx006_MSB_MASK) >> 8;
        buf[1] = (raddr & isx006_LSB_MASK);


        rc = isx006_i2c_rxdata_nonAck(saddr, buf, 2);
        if (rc < 0) {
            printk("isx006_i2c_read_parallel(WORD_LEN) 0x%x failed!\n", raddr);
            return rc;
        }

        *rdata = buf[1] << 8 | buf[0];
        break;

    case BYTE_LEN: //W_Addr : B_Data
        buf[0] = (raddr & isx006_MSB_MASK) >> 8;
        buf[1] = (raddr & isx006_LSB_MASK);

        rc = isx006_i2c_rxdata_nonAck(saddr, buf, 2);
        if (rc < 0) {
            printk("isx006_i2c_read_parallel(BYTE_LEN) 0x%x failed!\n", raddr);
            return rc;
        }

        *rdata = buf[0];
        break;
    
    default:
        break;
    }

    return rc;
}


static int32_t isx006_i2c_txdata(unsigned short saddr,
                unsigned char *txdata, int length)
{
    struct i2c_msg msg[] = {
        {
         .addr = saddr ,
         .flags = 0,
         .len = length,
         .buf = txdata,
         },
    };

    if (i2c_transfer(isx006_client->adapter, msg, 1) < 0) {
        printk("isx006_i2c_txdata faild 0x%x\n", isx006_client->addr);
        return -EIO;
    }

    return 0;
}


static int32_t isx006_i2c_txdata_nonAck(unsigned short saddr,
                unsigned char *txdata, int length)
{
    int i = 0;
    struct i2c_msg msg[] = {
        {
         .addr = saddr ,
         .flags = 0,
         .len = length,
         .buf = txdata,
         },
    };
    //printk("isx006_i2c_txdata_nonAck: enter\n");

    for(i = 0; i < 50; i++)
    {
        if (i2c_transfer(isx006_client->adapter, msg, 1) >= 0) {
            //printk("isx006_i2c_txdata_nonAck pass 0x%x\n", isx006_client->addr);
            return 0;            
        }
        cam_msleep(10);
    }
    printk("isx006_i2c_txdata_nonAck timeout 0x%x\n", isx006_client->addr);
    return -EIO;
}

static int32_t isx006_i2c_write_parallel(unsigned short saddr,
    unsigned short waddr, unsigned short wdata, enum fih_i2c_width width)
{
    int32_t rc = -EIO;
    unsigned char buf[4];

    memset(buf, 0, sizeof(buf));
    switch (width) {
    case WORD_LEN: //W_Addr : W_Data
        buf[0] = (waddr & 0xFF00)>>8;
        buf[1] = (waddr & 0x00FF);
        buf[2] = (wdata & 0x00FF);
        buf[3] = (wdata & 0xFF00)>>8;
        rc = isx006_i2c_txdata(saddr, buf, 4);
        if (rc < 0)
            printk("isx006_i2c_write_parallel(WORD_LEN) failed, addr = 0x%x, val = 0x%x!\n", waddr, wdata);
        break;

    case BYTE_LEN: //W_Addr : B_Data
        buf[0] = (waddr & 0xFF00)>>8;
        buf[1] = (waddr & 0x00FF);
        buf[2] = (wdata & 0xFF);

        rc = isx006_i2c_txdata(saddr, buf, 3);
        if (rc < 0)
            printk("isx006_i2c_write_parallel(BYTE_LEN) failed, addr = 0x%x, val = 0x%x!\n", waddr, wdata);

    break;

    default:
        break;
    }

    return rc;
}

static int32_t isx006_i2c_write_parallel_nonAck(unsigned short saddr,
    unsigned short waddr, unsigned short wdata, enum fih_i2c_width width)
{
    int32_t rc = -EIO;
    unsigned char buf[4];

    memset(buf, 0, sizeof(buf));
    switch (width) {
    case WORD_LEN: //W_Addr : W_Data
        buf[0] = (waddr & 0xFF00)>>8;
        buf[1] = (waddr & 0x00FF);
        buf[2] = (wdata & 0x00FF);
        buf[3] = (wdata & 0xFF00)>>8;
        rc = isx006_i2c_txdata_nonAck(saddr, buf, 4);
        if (rc < 0)
            printk("isx006_i2c_write_parallel(WORD_LEN) failed, addr = 0x%x, val = 0x%x!\n", waddr, wdata);
        break;

    case BYTE_LEN: //W_Addr : B_Data
        buf[0] = (waddr & 0xFF00)>>8;
        buf[1] = (waddr & 0x00FF);
        buf[2] = (wdata & 0xFF);

        rc = isx006_i2c_txdata_nonAck(saddr, buf, 3);
        if (rc < 0)
            printk("isx006_i2c_write_parallel(BYTE_LEN) failed, addr = 0x%x, val = 0x%x!\n", waddr, wdata);

    break;

    default:
        break;
    }

    return rc;
}


static int32_t isx006_i2c_write(unsigned short saddr,
    unsigned short waddr, unsigned short wdata, enum fih_i2c_width width)
{
    int32_t rc = -EIO;
    unsigned char buf[4];

    memset(buf, 0, sizeof(buf));
    switch (width) {
    case WORD_LEN: //W_Addr : W_Data
        buf[0] = (waddr & 0xFF00)>>8;
        buf[1] = (waddr & 0x00FF);
        buf[2] = (wdata & 0xFF00)>>8;
        buf[3] = (wdata & 0x00FF);

        rc = isx006_i2c_txdata(saddr, buf, 4);
        if (rc < 0)
            printk("isx006_i2c_write(WORD_LEN) failed, addr = 0x%x, val = 0x%x!\n", waddr, wdata);
        break;

    case BYTE_LEN: //W_Addr : B_Data
        buf[0] = (waddr & 0xFF00)>>8;
        buf[1] = (waddr & 0x00FF);
        buf[2] = (wdata & 0xFF);
    
        rc = isx006_i2c_txdata(saddr, buf, 3);
        if (rc < 0)
            printk("isx006_i2c_write(BYTE_LEN) failed, addr = 0x%x, val = 0x%x!\n", waddr, wdata);
        break;

    default:
        break;
    }

    return rc;
}
//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+}

static int32_t isx006_i2c_read(unsigned short saddr,
    unsigned short raddr, unsigned short *rdata, enum fih_i2c_width width)
{
    int32_t rc = 0;
    unsigned char buf[2];

    if (!rdata)
        return -EIO;

    memset(buf, 0, sizeof(buf));

    switch (width) {
    case WORD_LEN:
        buf[0] = (raddr & isx006_MSB_MASK) >> 8;
        buf[1] = (raddr & isx006_LSB_MASK);

        rc = isx006_i2c_rxdata(saddr, buf, 2);
        if (rc < 0) {
            printk("isx006_i2c_read(WORD_LEN) 0x%x failed!\n", raddr);
            return rc;
        }

        *rdata = buf[0] << 8 | buf[1];
        break;

    case BYTE_LEN:
        buf[0] = (raddr & isx006_MSB_MASK)>>8;
        buf[1] = (raddr & isx006_LSB_MASK);

        rc = isx006_i2c_rxdata(saddr, buf, 2);
        if (rc < 0) {
            printk("isx006_i2c_read(BYTE_LEN) 0x%x failed!\n", raddr);
            return rc;
        }

        *rdata = buf[0];
        break;
    
    default:
        break;
    }

    return rc;
}

/* FIH-SW3-MM-UW-write OTP setting-00+*/
static int32_t isx006_i2c_read_parallel_32bit(unsigned short saddr,
    unsigned short raddr, uint32_t *rdata)
{
    int32_t rc = 0;
    unsigned char buf_64bits[4];
    buf_64bits[0] = 0xFF;
    buf_64bits[1] = 0xFF;
    buf_64bits[2] = 0xFF;
    buf_64bits[3] = 0xFF;

    if (!rdata)
        return -EIO;

    memset(buf_64bits, 0, sizeof(buf_64bits));

    buf_64bits[0] = (raddr & isx006_MSB_MASK) >> 8;
    buf_64bits[1] = (raddr & isx006_LSB_MASK);

    rc = isx006_i2c_rxdata(saddr, buf_64bits, 4);
    if (rc < 0) {
        printk("isx006_i2c_read_parallel_32bit 0x%x failed!\n", raddr);
        return rc;
    }  

    *rdata = buf_64bits[3] << 24 | buf_64bits[2] << 16 |buf_64bits[1] << 8 | buf_64bits[0];

    return rc;
}
/* FIH-SW3-MM-UW-write OTP setting-00-*/

    
static int32_t isx006_i2c_write_table_parallel(unsigned short saddr,
    struct isx006_i2c_reg_conf const *reg_conf_tbl,
    int num_of_items_in_table)
{
    int i;
    int32_t rc = -EIO;

    for (i = 0; i < num_of_items_in_table; i++) {
        rc = isx006_i2c_write_parallel(saddr,
        reg_conf_tbl->waddr, reg_conf_tbl->wdata,
        reg_conf_tbl->width);
        
        if (rc < 0)
        {
            printk("isx006_i2c_write_table_parallel: Write count %d, addr 0x%x, val 0x%x failed !\n", i, reg_conf_tbl->waddr, reg_conf_tbl->wdata);  
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

/* FIH-SW3-MM-UW-performance tuning-00+*/
static int isx006_check_om(unsigned short saddr, const char *tag)
{
    int i =0;
    int rc = 0;
    uint16_t irq_status = 0x0;
    uint16_t v_read;
    uint16_t v_temp; 

    printk("isx006_check_om(0x%x): %s \n", saddr, tag);

    /* Make sure operation mode is changed */
    for (i = 0; i < ISX006_OM_RETRY_COUNT; i++)
    {
        rc = isx006_i2c_read_parallel(saddr, 0x00F8, &irq_status, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_om: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x00F8);
            goto error;
        }
        
        if (irq_status & 0x01)
            break;
        cam_msleep(10);
    }

    if (i >= ISX006_OM_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_om: Operation mode not change !!!\n");
        goto error;
    }
    printk("isx006_check_om: Operation mode change\n");


    /* Clear interrupt status */
    for (i = 0; i < ISX006_OM_RETRY_COUNT; i++)
    {
        rc = isx006_i2c_read_parallel(saddr, 0x00FC, &v_read, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_om: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x00FC);
            goto error;
        }
        v_temp = v_read | 0x01;    

        rc = isx006_i2c_write_parallel(saddr, 0x00FC, v_temp, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_om: isx006_i2c_write_parallel failed, REG(0x%x) !\n", 0x00FC);
            goto error;
        }
        cam_msleep(10);

        //2.Check interrupt status is cleaned
        rc = isx006_i2c_read_parallel(saddr, 0x00F8, &irq_status, BYTE_LEN);
        if (rc < 0)
        {
            pr_err("isx006_check_om: saddr: Read REG(0x%x) failed !\n", 0x00F8);
            goto error;
        }
        else
        {
            // Check OM_CHANGED STS (bit0)
            if (!(irq_status & 0x01))
            {
                printk("isx006_check_om: saddr: OM_CHANGED STS is clear. \n");
                break;
            }
        }
        cam_msleep(10);    
        printk("isx006_check_om: Retry for clear interrupt status ~ \n");
    }

    if (i >= ISX006_OM_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_om: Interrupt status is not cleaned !\n");
        goto error;
    }

    printk("isx006_check_om: Success \n");
    return rc;

error:
    pr_err("isx006_check_om: Failed !\n");
    return rc;
}

//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+{
static int isx006_check_om_nonAck(unsigned short saddr, const char *tag)
{
    int i =0;
    int rc = 0;
    uint16_t irq_status = 0x0;
    uint16_t v_read;
    uint16_t v_temp; 

    printk("isx006_check_om_nonAck(0x%x): %s \n", saddr, tag);

    /* Make sure operation mode is changed */
    for (i = 0; i < ISX006_OM_RETRY_COUNT; i++)
    {
        rc = isx006_i2c_read_parallel_nonAck(saddr, 0x00F8, &irq_status, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_om_nonAck: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x00F8);
            goto error;
        }
        
        if (irq_status & 0x01)
            break;
        cam_msleep(10);
    }

    if (i >= ISX006_OM_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_om_nonAck: Operation mode not change !!!\n");
        goto error;
    }
    printk("isx006_check_om_nonAck: Operation mode change\n");


    /* Clear interrupt status */
    for (i = 0; i < ISX006_OM_RETRY_COUNT; i++)
    {
        rc = isx006_i2c_read_parallel_nonAck(saddr, 0x00FC, &v_read, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_om_nonAck: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x00FC);
            goto error;
        }
        v_temp = v_read | 0x01;    

        rc = isx006_i2c_write_parallel_nonAck(saddr, 0x00FC, v_temp, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_om_nonAck: isx006_i2c_write_parallel failed, REG(0x%x) !\n", 0x00FC);
            goto error;
        }
        cam_msleep(10);

        //2.Check interrupt status is cleaned
        rc = isx006_i2c_read_parallel_nonAck(saddr, 0x00F8, &irq_status, BYTE_LEN);
        if (rc < 0)
        {
            pr_err("isx006_check_om_nonAck: saddr: Read REG(0x%x) failed !\n", 0x00F8);
            goto error;
        }
        else
        {
            // Check OM_CHANGED STS (bit0)
            if (!(irq_status & 0x01))
            {
                printk("isx006_check_om_nonAck: saddr: OM_CHANGED STS is clear. \n");
                break;
            }
        }
        cam_msleep(10);    
        printk("isx006_check_om_nonAck: Retry for clear interrupt status ~ \n");
    }

    if (i >= ISX006_OM_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_om_nonAck: Interrupt status is not cleaned !\n");
        goto error;
    }

    printk("isx006_check_om_nonAck: Success \n");
    return rc;

error:
    pr_err("isx006_check_om_nonAck: Failed !\n");
    return rc;
}
//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+}

static int isx006_check_cm(unsigned short saddr, const char *tag)
{
    int i = 0;
    int rc = 0;
    uint16_t irq_status = 0x0;
    uint16_t byte_value = 0xFF;
    uint16_t v_temp = 0xFF;
    uint16_t v_read = 0xFF;

    printk("isx006_check_cm(0x%x): %s \n", saddr, tag);

    /* Make sure operation mode is changed */
    for (i = 0; i < ISX006_CM_RETRY_COUNT; i++)
    {
        rc = isx006_i2c_read_parallel(saddr, 0x00F8, &irq_status, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_cm: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x00F8);
            goto error;
        }
        if (irq_status & 0x02)
            break;
        cam_msleep(10);    
     }

    if (i >= ISX006_CM_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_cm: Camera mode changed fail !!!\n");
        goto error;
    }
    printk("isx006_check_cm: Camera mode changed\n");

    
    /* Clear interrupt status */
    for (i = 0; i < ISX006_CM_RETRY_COUNT; i++)
    {
        /*1. Clear interrupt status*/
        rc = isx006_i2c_read_parallel(saddr, 0x00FC, &v_read, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_cm: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x00FC);
            goto error;
        }
        v_temp = v_read | 0x02;
        
        rc = isx006_i2c_write_parallel(saddr, 0x00FC, v_temp, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_check_cm: isx006_i2c_write_parallel failed, REG(0x%x) !\n",0x00FC);
            goto error;
        }
        cam_msleep(5);

        /*2.Check interrupt status is cleaned*/
        rc = isx006_i2c_read_parallel(saddr, 0x00F8, &irq_status, BYTE_LEN);
        if (rc < 0)
        {
            pr_err("isx006_check_cm: saddr: Read REG(0x%x) failed !\n", 0x00F8);
            goto error;
        }
        else
        {
            // Check MO_CHANGED STS (bit1)
            if (!(irq_status & 0x02))
            {
                printk("isx006_check_cm: CM_CHANGED STS is clear. \n");
                break;
            }
        }
        cam_msleep(5);
        printk("isx006_check_cm: clear interrupt status --- retry time = %d !\n", i);
    }

    if (i >= ISX006_CM_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_cm: Interrupt status is not cleaned !\n");
        goto error;
    }

    // Show current mode.
    rc = isx006_i2c_read_parallel(saddr, 0x0004, &byte_value, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_check_cm: isx006_i2c_read_parallel(0x0004) failed !\n");
        return rc;
    }
    /*MM-UW-support AF 01+*/    
    CameraMode = (byte_value & 0x03);    
    printk("isx006_check_cm: REG_0x0004 = 0x%x, Camera Mode = %d\n", byte_value, CameraMode);    
    /*MM-UW-support AF 01-*/    

    printk("isx006_check_cm: Success \n");
    return rc;

error:
    
#if 1 // Show current mode.
    rc = isx006_i2c_read_parallel(saddr, 0x0004, &byte_value, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_check_cm: Try to get current mode failed !\n");
        return rc;
    }
    printk("isx006_check_cm: Failed, REG_0x0004 = 0x%x !\n", byte_value);
#else
    pr_err("isx006_check_cm: Failed !\n");
#endif
    return rc;
}
/*MM-UW-add auto flash 00+*/

/* FIH-SW3-MM-UW-fix night capture fail-00+*/
/* FIH-SW3-MM-UW-cancel AF-00+*/
/* FIH-SW3-MM-UW-check AF lock state-00+*/
static int isx006_check_AF(unsigned short saddr, const char *tag)
{
    int i =0;
    int rc = 0;
    uint16_t irq_status = 0x0;
    uint16_t v_read = 0x0;    
    uint16_t v_temp = 0x0;        

    /* 01.Polling the interrupt register--------------------------------------------------------*/
    rc = isx006_i2c_read_parallel(saddr, 0x00F8, &irq_status, BYTE_LEN);//ADDR_INTSTS0 = 0x00F8
    if (rc < 0) {
        pr_err("isx006_check_AF: saddr(0x%x): Read REG(0x%x) failed !\n",saddr, 0x00F8);
        goto error;
    }

    if (!(irq_status & 0x10))//INTSTS0[4](AF_LOCK_STS)
    {
        //printk("isx006_check_AF: AF searching..\n");
        if(isx006_scene == SCENE_NIGHT)
            cam_msleep(40); 
        else if(AF_type)
            cam_msleep(4);   
        else
            cam_msleep(10);    
        return -EIO;
    }

    /* 02.Clear the interrupt register-------------------------------------------------------- */
    printk("isx006_check_AF: Clear interrupt status !\n");
    //ADDR_INTCLR0  = 0x00FC, INTCLR0[4](AF_LOCK_CLR=0x1)
    rc = isx006_i2c_read_parallel(saddr, 0x00FC, &v_read, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_check_AF: saddr(0x%x): Read REG(0x%x) failed !\n",saddr, 0x00FC);
        goto error;
    }
   
    v_temp = v_read | 0x10;    
    rc = isx006_i2c_write_parallel(saddr, 0x00FC, v_temp, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_check_AF: saddr(0x%x): Write REG(0x%x) failed !\n",saddr, 0x00FC);
        goto error;
    }

    /* 03.Polling the interrupt register until the data is 0 ----------------------------------------*/

    rc = isx006_i2c_read_parallel(saddr, 0x00F8, &irq_status, BYTE_LEN);
    if (rc < 0)
    {
        pr_err("isx006_check_AF: saddr(0x%x): Read REG(0x%x) failed !\n",saddr, 0x00F8);
        goto error;
    }

    printk("isx006_check_AF: Read REG(0x%x) = 0x%x !\n", 0x00F8, irq_status);
    if (!(irq_status & 0x10))//INTSTS0[4](AF_LOCK_STS)=0x0
    {
        printk("isx006_check_AF: saddr(0x%x): INTSTS0[4](AF_LOCK_STS) is clear. \n",saddr);
        return 0;
    }
    else
    {
        pr_err("isx006_check_AF: clear interrupt status fail--- retry time = %d !\n", i);
        cam_msleep(10);
        return -EIO; 
    }

    if (i >= ISX006_AF_RETRY_COUNT)
    {
        rc = -ETIME;
        pr_err("isx006_check_AF: Interrupt status is not cleaned !\n");
        goto error;
    }
    
    return rc;

error:
    return rc;
}
/* FIH-SW3-MM-UW-check AF lock state-00-*/
/*MM-UW-add auto flash 00-*/
/* FIH-SW3-MM-UW-performance tuning-00-*/
/* FIH-SW3-MM-UW-fix night capture fail-00-*/

/* FIH-SW3-MM-UW-flash tuning-04+*/
/* FIH-SW3-MM-UW-flash tuning-03+*/
/*MTD-MM-SL-ModifyPicDetailInfo-01*{*/
/* FIH-SW3-MM-UW-flash tuning-00+*/
/* FIH-SW3-MM-UW-fix capture fail-00+*/
static int isx006_get_AF_state(unsigned short saddr, const char *tag)
{
    int i = 0;
    int rc = 0;
    int led_mode = 0;
    uint16_t v_read = 0x0;    
    uint16_t v_temp = 0x0;        
    uint16_t AF_result = 0xFF;
    uint16_t AF_state = 0xFF;
    bool recover_AE = false;

        printk("isx006_get_AF_state: enter\n");
   
        led_mode = msm_soc_get_led_mode();
        printk("isx006_get_AF_state: led_mode = %d !\n", led_mode);  

        rc = isx006_i2c_read_parallel(isx006_client->addr, 0x6D76, &AF_result, BYTE_LEN);
        printk("isx006_get_AF_state: 0x6D76 AF satate = %d\n", AF_result);

        if( led_mode == LED_MODE_RED_EYE || led_mode == LED_MODE_AUTO)
        {  
            if(torch_enable)
                 recover_AE = true;
        }

        if( led_mode == LED_MODE_ON || recover_AE == true)
        {
                /* 05.Turn off pre-flash------------------------------------------------------------*/
                printk("isx006_get_AF_state: flash off!\n");
                rc = msm_soc_torch_flash_off();
                if (rc < 0)
                    printk("isx006_get_AF_state: msm_soc_torch_flash_off() failed !\n");
                cam_msleep(50); 
        }

         /* 01.Check the AF result register -------------------------------------------------------*/
        rc = isx006_i2c_read_parallel(isx006_client->addr, 0x6D77, &AF_result, BYTE_LEN);//ADD_AF_RESULT = 0x6D77
        if (rc < 0) {
            pr_err("isx006_get_AF_state: isx006_i2c_read_parallel(0x0004) failed !\n");
            goto error;
        }
    
        if(AF_result == AF_OK){
            printk("isx006_get_AF_state: AF result is AF OK!!!!\n");
        }
        else if(AF_result == AF_NG){    
            printk("isx006_get_AF_state: AF result is AF NG\n");
            rc =  -EIO;;
        }
        else if(AF_result == AF_During){    
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x4885, &v_read, BYTE_LEN);
            v_temp = v_read | 0x01;    
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4885, v_temp, BYTE_LEN);

            for (i = 0; i < 30; i++)
            {
                rc = isx006_i2c_read_parallel(isx006_client->addr, 0x6D76, &AF_state, BYTE_LEN);
                if (rc < 0) {
                    pr_err("isx006_get_AF_state: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x6D76);
                    goto error;
                }
                if (AF_state == AF_SAF_Idle || AF_state == AF_Idle) //SAF_IDLE
                    break;
                cam_msleep(10);    
             } 
            printk("isx006_get_AF_state: AF result is during AF\n");
            rc = -EIO;
        }

        return rc;
    
    error:
        return rc;
}
/* FIH-SW3-MM-UW-cancel AF-00-*/
/* FIH-SW3-MM-UW-fix capture fail-00-*/
/* FIH-SW3-MM-UW-flash tuning-00-*/
/*MTD-MM-SL-ModifyPicDetailInfo-01*}*/
/* FIH-SW3-MM-UW-flash tuning-03-*/
/* FIH-SW3-MM-UW-flash tuning-04-*/

/* FIH-SW3-MM-UW-fix AF not work-00+*/
/*MM-UW-reduce knocking noise-00+*/
static int isx006_MF_position(unsigned short saddr, int position)
{
        int rc = -EBADF;
        uint16_t v_read = 0x00;
        int i;

        printk ("isx006_MF_position: Start.\n");
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, 0, WORD_LEN);//AF_AREA_LOW_TYPE1
        if (rc < 0)
            goto error;

        //0. Set MF position to move
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4852, position, WORD_LEN);
        if (rc < 0)
            goto error;

        //1. Trigger MF  
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4850, 0x01, BYTE_LEN);
        if (rc < 0)
            goto error;

        for (i = 0; i < ISX006_AF_RETRY_COUNT; i++)
        {
          isx006_i2c_read_parallel(isx006_client->addr, 0x6D7A, &v_read, WORD_LEN);
          if(v_read == position)
            break;
          cam_msleep(5);    
        }
        printk ("isx006_check_MF: loop = %d, v_read =%d \n", i, v_read);
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, AF_A_value, WORD_LEN);//AF_AREA_LOW_TYPE1
        if (rc < 0)
            goto error;

        printk ("isx006_MF_position: End.\n");  
        return rc;

error:
    return rc;
}
/*MM-UW-reduce knocking noise-00-*/
/* FIH-SW3-MM-UW-fix AF not work-00-*/

static void isx006_get_pict_fps(uint16_t fps, uint16_t *pfps)
{
    /* input fps is preview fps in Q8 format */
    uint32_t divider, d1, d2;

    d1 = (prev_frame_length_lines * 0x00000400) / snap_frame_length_lines;
    d2 = (prev_line_length_pck * 0x00000400) / snap_line_length_pck;
    divider = (d1 * d2) / 0x400;

    /*Verify PCLK settings and frame sizes.*/
    *pfps = (uint16_t) (fps * divider / 0x400);
}

static uint16_t isx006_get_prev_lines_pf(void)
{
    if (isx006_ctrl->prev_res == QTR_SIZE)
        return prev_frame_length_lines;
    else
        return snap_frame_length_lines;
}

static uint16_t isx006_get_prev_pixels_pl(void)
{
    if (isx006_ctrl->prev_res == QTR_SIZE)
        return prev_line_length_pck;
    else
        return snap_line_length_pck;
}

static uint16_t isx006_get_pict_lines_pf(void)
{
    if (isx006_ctrl->prev_res == QTR_SIZE)
        return prev_frame_length_lines;
    else
        return snap_frame_length_lines;
}

static uint16_t isx006_get_pict_pixels_pl(void)
{
    if (isx006_ctrl->prev_res == QTR_SIZE)
        return prev_line_length_pck;
    else
        return snap_line_length_pck;
}

static uint32_t isx006_get_pict_max_exp_lc(void)
{
    if (isx006_ctrl->prev_res == QTR_SIZE)
        return prev_frame_length_lines;
    else
        return snap_frame_length_lines;
}

/* FIH-SW3-MM-UW-flash tuning-04+*/
/*MTD-MM-SL-ModifyPicDetailInfo-01+{*/
bool isx006_get_AE_value(void)
{
        int32_t AE_value = 0;
        int32_t AE_target = 0x0000FD52 - 0x0000FFFF - 1;
        bool Low_Light = false;
        uint16_t read_value = 0;
        int rc = 0;

        printk("isx006_get_AE_value: enter\n");

        /*Get AESCL_AUTO--------------------------------------------------------------------*/
        if (slave_add == isx006_client->addr)
        {
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x0288, &read_value, WORD_LEN);   
        }else{
            rc = isx006_i2c_read(isx006_client->addr, 0x0288, &read_value, WORD_LEN);
        }  
        AESCL_AUTO = read_value;

        /*Get ERRSCL_AUTO--------------------------------------------------------------------*/ 

        if (slave_add == isx006_client->addr)
        {
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x0284, &read_value, WORD_LEN);   
        }else{
            rc = isx006_i2c_read(isx006_client->addr, 0x0284, &read_value, WORD_LEN);
        }  
        if(rc < 0) {
            printk("isx006_get_AE_value: read AE value failed !\n");
        }

        if( read_value >= 0x00008000 )
            ERRSCL_AUTO = (read_value - 0x0000FFFF -1);
        else
            ERRSCL_AUTO = (read_value & 0x0000FFFF);

        AE_value = ERRSCL_AUTO;

        if(AE_value <= AE_target)
        {
            Low_Light = true;
            printk("isx006_get_AE_value: low light condition !\n");
        }

        return Low_Light;
}
/*MTD-MM-SL-ModifyPicDetailInfo-01+}*/
/* FIH-SW3-MM-UW-flash tuning-04-*/

int isx006_polling_state_change(unsigned short saddr, enum isx006_device_status polling_status)
{
    int rc = 0;
    int count = 0;
    int max_polling = 50;
    uint16_t now_status = 0xFFFF;
    
    do 
    {
        count++;
        cam_msleep(20);
        rc = isx006_i2c_read_parallel(saddr, 0x00FE, &now_status, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_polling_state_change: Read Back DEVICESTS_REG(0x%x) failed !\n", 0x00FE);
            goto error;
        }
        if (now_status != polling_status)
        {
            rc = -EINVAL;
        }
        else
        {
            printk("isx006_polling_state_change(%d): now_status(0x%x), polling_status(0x%x).\n", count, now_status, polling_status);
            rc = 0;
        }
    } while( (polling_status != now_status) && (count < max_polling));

    if (rc < 0 || count >= max_polling)
    {
        rc = -EIO;
        pr_err("isx006_polling_state_change: Failed !\n");
        goto error;
    }

    switch (polling_status) {
    case STS_POWER_DOWN:
        printk("isx006_polling_state_change: Polling success, status = STS_POWER_DOWN.\n");
        break;
            
    case STS_PRE_SLEEP:
        printk("isx006_polling_state_change: Polling success, status = STS_PRE_SLEEP.\n");
        break;
            
    case STS_SLEEP:
        printk("isx006_polling_state_change: Polling success, status = STS_SLEEP.\n");
        break;
            
    case STS_ACTIVE:
        printk("isx006_polling_state_change: Polling success, status = STS_ACTIVE.\n");
        break;
            
    case STS_UNKNOWN:
    default:
        rc = -EINVAL;
        printk("isx006_polling_state_change: Polling failed, status = STS_UNKNOWN !\n");
        break;
    }

    return rc;
    
error:
    printk("isx006_polling_state_change fail: now_status(0x%x), polling_status(0x%x).\n", now_status, polling_status);
    return rc;
}

/* FIH-SW3-MM-UW-enhance stability-00+*/
/* FIH-SW3-MM-UW-in_out standby fail -00+*/
//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*{
/*MM-UW-improve camera close performance-00+*/
//FIH-SW-MM-MC-EnableHWStandby-00*{
int isx006_enter_standby(void)
{
    int rc = 0; 
    uint16_t status = 0xFFFF;
    
    rc = isx006_i2c_read_parallel(isx006_client->addr, 0x00FE, &status, BYTE_LEN);
    printk("isx006_enter_standby: camera om status = %d!\n", status);

    /* Set NSTANDBY from H to L */
    rc = fih_set_gpio_output_value(isx006_info->sensor_pwd, "CAM_5M_STBYN", LOW);
    if (rc < 0)
        goto error;
    
    //cam_msleep(136);//T1 duration(max)

    rc = isx006_check_om_nonAck(isx006_client->addr, "For change to Sleep mode");
        if (rc < 0) {
        pr_err("isx006_enter_standby: isx006_check_om_nonAck(For change to Sleep mode) failed !\n");
        goto error;
    }

    /* Here to check ststus is STS_SLEEP */
    rc = isx006_polling_state_change(isx006_client->addr, STS_SLEEP);
    if (!rc) {
        printk("isx006_enter_standby: isx006_polling_state_change(STS_SLEEP) success !\n");
        rc = fih_disable_mclk(isx006_info->mclk, ISX006_MASTER_CLK_RATE);
        if (rc < 0) {
            goto error;
        }
        cam_msleep(5);
    }

    printk("isx006_enter_standby: Success !\n");
    return rc;

error:
    printk("isx006_enter_standby: Failed !\n");
    return rc;
}
/* FIH-SW3-MM-UW-enhance stability-00-*/

int isx006_exit_standby(enum Exit_Standby_Action act)
{
    int rc = 0;
    uint16_t status = 0xFFFF;
    
    switch (act) {
    case ACT_MCLK_ON:
        {
            printk("isx006_exit_standby: case ACT_MCLK_ON \n");
            rc = fih_enable_mclk(isx006_info->mclk, ISX006_MASTER_CLK_RATE);
            if (rc < 0) {
                goto error;
            }
            cam_msleep(50); /*MTD-MM-SL-EnhanceStandby-00*/ //5

            //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-03+{
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x00FE, &status, BYTE_LEN);
            if (rc < 0)
                printk("isx006_exit_standby: Can not read camera om status after MCLK enable ..\n"); 
            else
                printk("isx006_exit_standby: [Success] Camera om status = %d ! (MCLK ON)\n", status);            
            //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-03+}
        }
        break;
            
    case ACT_EXIT_STANDBY:
        {
            printk("isx006_exit_standby: case ACT_EXIT_STANDBY \n");
            /* Set NSTANDBY from L to H */
            rc = fih_set_gpio_output_value(isx006_info->sensor_pwd, "CAM_5M_STBYN", HIGH);
            if (rc < 0)
                goto error;
            
            //cam_msleep(150); /*MTD-MM-SL-EnhanceStandby-00*/ //20

            rc = isx006_check_om_nonAck(isx006_client->addr, "For change to Active mode");
                if (rc < 0) {
                pr_err("isx006_exit_standby: isx006_check_om(For change to Active mode) failed !\n");
                goto error;
            }

            /* Here to check ststus is STS_ACTIVE */
            rc = isx006_polling_state_change(isx006_client->addr, STS_ACTIVE);
            if (rc < 0) {
                pr_err("isx006_exit_standby: isx006_polling_state_change(STS_ACTIVE) failed !\n");
                goto error;
            }
            
            rc = isx006_check_cm(isx006_client->addr, "For CM change to Monitor mode");
            if (rc < 0) {
                pr_err("isx006_exit_standby: isx006_check_cm(For CM change to Monitor mode) failed !\n");
                goto error;
            }
            //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-03+{
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x00FE, &status, BYTE_LEN);
            if (rc < 0)
                printk("isx006_exit_standby: Can not read camera om status after exit standby mode ..\n"); 
            else
                printk("isx006_exit_standby: [Success] Camera om status = %d ! (Exit standby mode)\n", status);            
            //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-03+}
        }
        break;
            
    default:
        {
            rc = -EINVAL;
            printk("isx006_exit_standby: ERR: Invalid item !\n");
            goto error;
        }
        break;
    }    
     
    return rc;
    
error:
    printk("isx006_exit_standby: Failed !\n");
    return rc;
}
//FIH-SW-MM-MC-EnableHWStandby-00*}
/*MM-UW-improve camera close performance-00-*/
/* FIH-SW3-MM-UW-in_out standby fail -00 -*/

/*MM-UW-improve camera performance-00+*/
/*MM-UW-EnableHWStandby-00+*/
int front_cam_enter_standby(void)
{
    int rc = 0;
    //int i = 0;
    uint16_t read_value;

    printk("front_cam_enter_standby: Enter \n");
    rc = isx006_i2c_read(0x3D, 0x0018, &read_value, WORD_LEN);
    if (rc < 0)
        goto error;
 
    read_value = read_value | 0x0001;
    rc = isx006_i2c_write(0x3D, 0x0018, read_value, WORD_LEN);
    if (rc < 0)
        goto error;

    /*for (i = 0; i < 100; i++)
    {
        rc = isx006_i2c_read(0x3D, 0x0018, &read_value, WORD_LEN);
        if (rc < 0) {
            pr_err("front_cam_enter_standby: Read REG(0x%x) failed !\n", 0x0018);
            goto error;
        }
        read_value = read_value >> 14;
        read_value = read_value & 0x0001;
        printk("front_cam_enter_standby: polling standy mode i = %d\n", i);
        if(read_value == 0x0001)
            break;
        
        cam_msleep(10);
    }*/
    cam_msleep(35);
    
    printk("front_cam_enter_standby: Success \n");
    return 0;

error:
    printk("front_cam_enter_standby: Failed !\n");
    return rc;

}
/*MM-UW-EnableHWStandby-00-*/
/*MM-UW-improve camera performance-00-*/
//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*}

int isx006_set_camera_mode(enum isx006_mode new_mode, const char *tag)
{
    int rc = 0;
    uint16_t v_read;
    uint16_t v_temp;

    /* Clear interrupt status */
    /* FIH-SW3-MM-UW-performance tuning-00+*/
    rc = isx006_i2c_read_parallel(isx006_client->addr, 0x00FC, &v_read, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_camera_mode: Read REG(0x%x) failed !\n", 0x00FC);
        goto error;
    }
    v_temp = v_read | 0x02;    

    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x00FC, v_temp, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_camera_mode: Write REG(0x%x) failed !\n", 0x00FC);
        goto error;
    }
    cam_msleep(10);   
    /* FIH-SW3-MM-UW-performance tuning-00-*/

    printk("isx006_set_camera_mode: pre set camera mode to %s\n", tag);
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0011, new_mode, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_camera_mode: isx006_i2c_write_parallel(0x0011) failed !\n");
        goto error;
    }
    
    printk("isx006_set_camera_mode(%s): Success \n", tag);
    return rc;
    
error:
    printk("isx006_set_camera_mode(%s): Failed !\n", tag);
    return rc;
}

/* FIH-SW3-MM-UW-read vendor id-00+*/
/* FIH-SW3-MM-UW-add touch AF-00+*/
/* FIH-SW3-MM-UW-write OTP setting-00+*/
int isx006_OTP_setting(void) 
{
    int rc = 0;
    uint32_t read_value;

    uint16_t I_NORMR = 0x10BD;    
    uint16_t I_NORMB = 0x0EE0;
    uint16_t I_AWB_PRER = 0x0146;
    uint16_t I_AWB_PREB = 0x0239;    
    uint16_t NORMR;    
    uint16_t NORMB;
    uint16_t AWB_PRER;
    uint16_t AWB_PREB;    
    
    isx006_i2c_read_parallel_32bit(slave_add, 0x0250, &read_value);    
    OTP_0_value = read_value;    
    isx006_i2c_read_parallel_32bit(slave_add, 0x0254, &read_value);    
    OTP_1_value = read_value;    
    isx006_i2c_read_parallel_32bit(slave_add, 0x0258, &read_value);    
    OTP_2_value = read_value;        

    printk("isx006_OTP_setting: 0x0250 = 0x%x\n", OTP_0_value);    
    printk("isx006_OTP_setting: 0x0254 = 0x%x\n", OTP_1_value);
    printk("isx006_OTP_setting: 0x0258 = 0x%x\n", OTP_2_value);  
    
    /* Vendor ID -----------------------------------------*/  
    vendor_id = (OTP_2_value >>24) & 0x00000001;
    printk("isx006_OTP_setting: vendor_id = %d\n", vendor_id);    

    /* AF position -----------------------------------------------*/    
    AF_A_value = (uint16_t) ((OTP_0_value >> 5  ) & 0x000003FF);    
    AF_B_value = (uint16_t) ((OTP_0_value >> 16) & 0x000003FF);        
    printk("isx006_OTP_setting:AF_A_value = %d\n", AF_A_value);
    printk("isx006_OTP_setting:AF_B_value = %d\n", AF_B_value);    

    /*MM-UW-reduce knocking noise-00+*/
    AF_F_value = 8; //coarse search
    AF_C_value = (AF_B_value - AF_A_value) / (AF_F_value - 2) + 1;
    printk("isx006_OTP_setting+: AF_C_value =%d \n", AF_C_value);
    
    isx006_i2c_write_parallel(isx006_client->addr, 0x495E, AF_B_value - AF_C_value, WORD_LEN);
    isx006_i2c_write_parallel(isx006_client->addr, 0x4960, AF_A_value , WORD_LEN);  
    isx006_i2c_write_parallel(isx006_client->addr, 0x4962, AF_A_value + AF_C_value, WORD_LEN); 
    /*MM-UW-reduce knocking noise-00-*/
    /* Pre-White Balance -----------------------------------------*/    
    C_NR = (uint16_t) (((OTP_1_value << 6 ) & 0x000000C0) | ((OTP_0_value >> 26  ) & 0x0000003F));    
    C_NB = (uint16_t) ((OTP_1_value >> 2 ) & 0x000000FF);
    C_PR = (uint16_t) ((OTP_1_value >> 10 ) & 0x000000FF);
    C_PB = (uint16_t) ((OTP_1_value >> 18 ) & 0x000000FF);
    printk("isx006_OTP_setting: C_NR = 0x%x\n", C_NR);    
    printk("isx006_OTP_setting: C_NB = 0x%x\n", C_NB);
    printk("isx006_OTP_setting: C_PR = 0x%x\n", C_PR);        
    printk("isx006_OTP_setting: C_PB = 0x%x\n", C_PB);

    NORMR = (uint16_t) (I_NORMR * (128 + C_NR) /256);    
    NORMB = (uint16_t) (I_NORMB * (128 + C_NB) /256);
    AWB_PRER = (uint16_t) (I_AWB_PRER * (128 + C_PR) /256);    
    AWB_PREB = (uint16_t) (I_AWB_PREB * (128 + C_PB) /256);    
    printk("isx006_OTP_setting: NORMR = 0x%x\n", NORMR);    
    printk("isx006_OTP_setting: NORMB = 0x%x\n", NORMB);
    printk("isx006_OTP_setting: AWB_PRER = 0x%x\n", AWB_PRER);        
    printk("isx006_OTP_setting: AWB_PREB = 0x%x\n", AWB_PREB);    

    isx006_i2c_write_parallel(slave_add, 0x4A04, NORMR, WORD_LEN);
    isx006_i2c_write_parallel(slave_add, 0x4A06, NORMB, WORD_LEN);
    isx006_i2c_write_parallel(slave_add, 0x4A08, AWB_PRER, WORD_LEN);
    isx006_i2c_write_parallel(slave_add, 0x4A0A, AWB_PREB, WORD_LEN);

    /* Lens Shading ----------------------------------------------*/
    Shading_index = (uint16_t) ((OTP_2_value >> 20 ) & 0x0000000F);		
    printk("isx006_OTP_setting:Shading_index = %d\n", Shading_index);	

    if(!vendor_id) //KMOT
    {
        printk("isx006_OTP_setting:write shading table \n");	
        switch (Shading_index) {
        case SHD_MIN:
        	isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_SHD_MIN_2nd,
                   isx006_regs.reg_SHD_MIN_2nd_size);
        	break;	 
     
        case SHD_TYP:	
        	isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_SHD_TYP_2nd,
                   isx006_regs.reg_SHD_TYP_2nd_size);
        	break;
     
        case SHD_MAX: 	
        	isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_SHD_MAX_2nd,
                   isx006_regs.reg_SHD_MAX_2nd_size);
        	break;
       }
    }

    return rc;    
}
/* FIH-SW3-MM-UW-add touch AF-00-*/
/* FIH-SW3-MM-UW-read vendor id-00-*/

int isx006_change_slave_address(void)
{
    int rc = 0;
    
    /*#define I2C_ADR_SEL_REG 0x0350                 */
    /*     0:   Not selected                        */
    /*       1:   Parallel interface (address: 0x1A)        */
    /*            2:   MIPI interface (address: 0x3C)    */     
    /* Change slave address for MIPI interface           */
    rc = isx006_i2c_write_parallel(slave_add, 0x0350, 0x02, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_change_slave_address: isx006_i2c_write_parallel(0x0350) failed !\n");
        goto error;
    }    
    rc = isx006_i2c_write_parallel(slave_add, 0x3E02, 0x04, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_change_slave_address: isx006_i2c_write_parallel(0x3E02) failed !\n");
        goto error;
    }
    printk("isx006_change_slave_address: Change slave address from 0x1A to 0x3C success.\n");   
    return rc;
    
error:
    printk("isx006_change_slave_address: Change slave address from 0x1A to 0x3C failed !\n");   
    return rc;
}
/* FIH-SW3-MM-UW-write OTP setting-00-*/

int isx006_start_streaming(void)
{
    int rc = 0;

    /* Set NSTANDBY from L to H */
    rc = fih_set_gpio_output_value(isx006_info->sensor_pwd, "CAM_5M_STBYN", HIGH);/* FIH-SW3-MM-SL-ModifyGPIODefine-01* */
    if (rc < 0) {
        printk("isx006_start_streaming: Pull high CAM_5M_STBYN pin failed !\n");
        goto error;
    }
    cam_msleep(10);//T4 duration(max)

    rc = isx006_check_om(isx006_client->addr, "For change to Active mode");
    if (rc < 0) {
        pr_err("isx006_start_streaming: isx006_check_om(For change to Active mode) failed !\n");
        goto error;
    }

    /* Here to check ststus is STS_ACTIVE */
    rc = isx006_polling_state_change(isx006_client->addr, STS_ACTIVE);
    if (rc < 0) {
        pr_err("isx006_start_streaming: isx006_polling_state_change(STS_ACTIVE) failed !\n");
        goto error;
    }

    rc = isx006_check_cm(isx006_client->addr, "For CM change to Monitor mode");
    if (rc < 0) {
        pr_err("isx006_start_streaming: isx006_check_cm(For CM change to Monitor mode) failed !\n");
        goto error;
    }
    
    printk("isx006_start_streaming: Start streaming success.\n");   
    return rc;
    
error:
    printk("isx006_start_streaming: Failed !\n"); 
    return rc;
}

/* FIH-SW3-MM-UW-write OTP setting-00+*/
int isx006_init_sensor(void)
{
    int rc = 0;

    rc = isx006_check_om(slave_add, "For change to PreSleep mode");
    if (rc < 0) {
        pr_err("isx006_init_sensor: isx006_check_om(For change to PreSleep mode) failed !\n");
        goto error;
    }

    /* Here to check ststus is STS_PRE_SLEEP */
    rc = isx006_polling_state_change(slave_add, STS_PRE_SLEEP);
    if (rc < 0) {
        pr_err("isx006_init_sensor: isx006_polling_state_change(STS_PRE_SLEEP) failed !\n");
        goto error;
    }

    /* <2>. Pre-Sleep mode */   
    rc = isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_init, isx006_regs.reg_init_size); 
    if (rc < 0) {
        pr_err("isx006_init_sensor: Write Period1 table failed !\n");
        goto error;
    }
    printk("isx006_init_sensor: Sensor init done.\n");
    cam_msleep(1);//0.2ms//T3 duration(max)
    
    rc = isx006_check_om(slave_add, "For change to Sleep mode");
    if (rc < 0) {
        pr_err("isx006_init_sensor: isx006_check_om(For change to Sleep mode) failed !\n");
        goto error;
    }

    /* Here to check ststus is STS_SLEEP */
    rc = isx006_polling_state_change(slave_add, STS_SLEEP);
    if (rc < 0) {
        pr_err("isx006_init_sensor: isx006_polling_state_change(STS_SLEEP) failed !\n");
        goto error;
    }

    if(!vendor_id) //KMOT
    {
        printk("isx006_init_sensor: Sensor Period2 for 2nd source.\n");
        rc = isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_preload2_2nd, isx006_regs.reg_preload2_2nd_size);
    }
    else
    {
        printk("isx006_init_sensor: Sensor Period2 for main source.\n");
        rc = isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_preload2, isx006_regs.reg_preload2_size);
    }
    if (rc < 0) {
        pr_err("isx006_init_sensor: Write Period2 table failed !\n");
        goto error;
    }
    printk("isx006_init_sensor: Sensor Period2 done.\n");
    cam_msleep(5);

    if(!vendor_id) //KMOT
    {
        printk("isx006_init_sensor: Sensor Period3 for 2nd source.\n");
        rc = isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_preload3_2nd, isx006_regs.reg_preload3_2nd_size);
    }
    else
    {
        rc = isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_preload3, isx006_regs.reg_preload3_size);
        printk("isx006_init_sensor: Sensor Period3 for main source.\n");
    }
    if (rc < 0) {
        pr_err("isx006_init_sensor: Write Period3 table failed !\n");
        goto error;
    }
    printk("isx006_init_sensor: Sensor Period3 done.\n");
    cam_msleep(5); 
    
    printk("isx006_init_sensor: Success.\n");   
    return rc;
    
error:
    printk("isx006_init_sensor: Failed !\n");
    return rc;
}
/* FIH-SW3-MM-UW-write OTP setting-00-*/

/* FIH-SW3-MM-UW-AF power-00+*/
/*MM-UW-support AF+++*/
int isx006_AF_power(bool enable){
    int rc = 0;

    if (enable)
    {
        rc = pmic_vreg_pull_down_switch(OFF_CMD , PM_VREG_PDOWN_BT_ID);
        if (rc < 0)
            goto error;
    
        rc = fih_regulator_enable(isx006_info->vreg_af_power, 3000000, "isx006_AF");
        if (rc < 0)
            goto error;
        cam_msleep(15); 
    }
    else
    {
        rc = fih_regulator_disable(isx006_info->vreg_af_power, "isx006_AF");
        if (rc < 0)
            goto error;
        
        rc = pmic_vreg_pull_down_switch(ON_CMD , PM_VREG_PDOWN_BT_ID);
        if (rc < 0)
            goto error;
        cam_msleep(5); 
    }
    printk("isx006_AF_power(%d): Success.\n", enable);
    return rc;
    
error:
    printk("isx006_AF_power(%d): Failed !\n", enable);
    return rc;

}
/*MM-UW-support AF---*/
/* FIH-SW3-MM-UW-AF power-00-*/

/* FIH-SW3-MM-UW-AF power-00+*/
/*MM-UW-fix unbalance warning-00+*/
/* FIH-SW3-MM-UW-performance tune-00+*/
//FIH-SW-MM-MC-EnableHWStandby-00*{
/* FIH-SW3-MM-SL-ModifyGPIODefine-01*{ */
int isx006_power_on(const struct msm_camera_sensor_info *data)
{
    int rc = 0;
    printk("isx006_power_on: Start.\n");   

    isx006_AF_power(1);/*MM-UW-support AF+*/

    if(STARTUP == 0)
    {
        printk("isx006_power_on: STARTUP = 0 \n");     

        /* I/O & Analog power up */    
        rc = fih_set_gpio_output_value(isx006_info->vreg_v1p2, "EN_VREG_CAM_VDD_V1P2", HIGH);
        if (rc < 0)
            goto error;

        rc = fih_set_gpio_output_value(isx006_info->vreg_v1p8, "EN_VREG_CAM_VDDIO_V1P8", HIGH);
        if (rc < 0)
            goto error;

        rc = fih_set_gpio_output_value(isx006_info->vreg_v2p8, "EN_VREG_CAM_VAA_V2P8", HIGH);
        if (rc < 0)
            goto error;

        cam_msleep(5);

        /* Clock supply */
        rc = fih_enable_mclk(isx006_info->mclk, ISX006_MASTER_CLK_RATE);
        if (rc < 0)
            goto error;

        cam_msleep(10);    

        /*front camera enter standby*/
        /*MM-UW-EnableHWStandby-00+*/
        rc = front_cam_enter_standby();  
        if (rc < 0)
            printk("isx006_power_on: front_cam_enter_standby() failed !\n");
        /*MM-UW-EnableHWStandby-00-*/

        /* Set NREST from L to H */ 
        rc = fih_set_gpio_output_value(isx006_info->sensor_reset, "CAM_5M_RSTN", HIGH);
        if (rc < 0)
            goto error;
        
        cam_msleep(10);
    }
    else
    {  
        printk("isx006_power_on: STARTUP = 1 \n");

        rc = isx006_exit_standby(ACT_MCLK_ON);//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*
        if (rc < 0)
            goto error;
    }
    printk("isx006_power_on: End. \n");  
    return rc;

error:
    pr_err("isx006_power_on: failed !, rc = %d.\n", rc);
    return rc;
}

int isx006_power_off(void)
{
    int rc = 0;
    printk("isx006_power_off: Start. \n");

    if(STARTUP == 0)
    {        
        printk("isx006_power_off: STARTUP = 0 \n"); 

        /* Set NSTANDBY from H to L */
        rc = fih_set_gpio_output_value(isx006_info->sensor_pwd, "CAM_5M_STBYN", LOW);
        if (rc < 0)
            goto error;

        /* Set NREST from H to L */ 
        rc = fih_set_gpio_output_value(isx006_info->sensor_reset, "CAM_5M_RSTN", LOW);
        if (rc < 0)
            goto error;

        cam_msleep(5);// >0

        rc = fih_disable_mclk(isx006_info->mclk, ISX006_MASTER_CLK_RATE);
        if (rc < 0)
            goto error;

        cam_msleep(5);// >0

        rc = fih_set_gpio_output_value(isx006_info->vreg_v2p8, "EN_VREG_CAM_VAA_V2P8", LOW);
        if (rc < 0)
            goto error;

        rc = fih_set_gpio_output_value(isx006_info->vreg_v1p8, "EN_VREG_CAM_VDDIO_V1P8", LOW);
        if (rc < 0)
            goto error;

        rc = fih_set_gpio_output_value(isx006_info->vreg_v1p2, "EN_VREG_CAM_VDD_V1P2", LOW);
        if (rc < 0)
            goto error;
        
    }
    else
    {
        printk("isx006_power_off: STARTUP = 1 \n");         
        rc = isx006_enter_standby();
        if (rc < 0)
            goto error;
    }
    isx006_AF_power(0);/*MM-UW-support AF+*/
    
    printk("isx006_power_off: End. \n");  
    return rc;

error:
    pr_err("isx006_power_off: failed !, rc = %d.\n", rc);
    return rc;
}
/* FIH-SW3-MM-SL-ModifyGPIODefine-01*} */
/* FIH-SW3-MM-UW-performance tune-00-*/
/*MM-UW-fix unbalance warning-00-*/
/* FIH-SW3-MM-UW-AF power-00-*/

/*MM-UW-improve camera close performance-00+*/
/*MM-UW-fix unbalance warning-00+*/
int isx006_suspend(struct platform_device *pdev, pm_message_t state)
{
    int rc = 0;
    
    printk("isx006_suspend \n");
    /*MM-UW-Standby with MCLK off-00+*/
    rc = fih_enable_mclk(isx006_info->mclk, ISX006_MASTER_CLK_RATE);
    if (rc < 0) {
        goto error;
    }
    cam_msleep(5);
    /*MM-UW-Standby with MCLK off-00-*/

    bMainCameraIsReset = false;//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*
    STARTUP  = 0;
    AF_full_range = 0;
    
    rc = isx006_power_off();
    if (rc < 0)
        goto error;
    
    return 0;
    
error:
    pr_err("isx006_suspend: failed !, rc = %d.\n", rc);
    return rc;
}
/*MM-UW-fix unbalance warning-00-*/
/*MM-UW-improve camera close performance-00-*/

int isx006_resume(struct platform_device *pdev)
{
     printk("isx006_resume \n");  
     return 0;
}
//FIH-SW-MM-MC-EnableHWStandby-00*}

/* FIH-SW3-MM-UW-flash tuning-04+*/
int isx006_PreFlash_setting(void)
{
    int rc = 0;

    /* Set LED & AE/AWB Control----------------------------*/
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0069, 0x0D, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_AF: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x0069);
        return-EIO;
    }
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x02C4, 0x0010, WORD_LEN);
    if (rc < 0) {
        pr_err("isx006_set_AF: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x02C4);
        return-EIO;
    }
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x027D, 0x05, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_AF: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x027D);
        return-EIO;
    }
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4066, 0x0F, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_snapshot_config: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x4066);
        return-EIO;
    }
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x402F, 0x0B, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_snapshot_config: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x402F);
        return-EIO;
    }
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x404C, 0x2C, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_snapshot_config: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x404C);
        return-EIO;
    }
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x400B, 0x3C, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_snapshot_config: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x400B);
        return-EIO;
    }
    
    return rc;
}
/* FIH-SW3-MM-UW-flash tuning-04-*/

/*MM-UW-reduce knocking noise-00+*/
/*MM-UW-add auto flash 00+*/
/* FIH-SW3-MM-UW-add reduce_red_eye-00+*/
/* FIH-SW3-MM-URI-Add WB-00- */
/* FIH-SW3-MM-SL-PatchForCameraFeature-01*} */
//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
int isx006_set_monitor_af_mode(enum isx006_moni_af_mode new_mode, const char *tag)
{
    int rc = 0;
    uint16_t v_read = 0x0;    
    uint16_t v_temp = 0x0;       

    //0. Clear interrupt status
    rc = isx006_i2c_read_parallel(isx006_client->addr, 0x00FC, &v_read, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_check_AF: Read REG(0x%x) failed !\n", 0x00FC);
        goto error;
    }
    v_temp = v_read | 0x10;
    
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x00FC, v_temp, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_check_AF: Write REG(0x%x) failed !\n", 0x00FC);
        goto error;
    }
    
    //1. Set monitor AF mode
    printk("isx006_set_monitor_af_mode: pre set MONI AF mode to %s\n", tag);
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x002E, new_mode, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_monitor_af_mode: isx006_i2c_write_parallel(0x002E) failed !\n");
        goto error;
    }

    //2. MONI_REFRESH
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0012, 0x01, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_monitor_af_mode: isx006_i2c_write_parallel(0x0012) failed for refresh !\n");
        goto error;
    }

error:
    return rc;
}
/*MM-UW-reduce knocking noise-00-*/

/* FIH-SW3-MM-UW-modify touch AF-00+*/
/* FIH-SW3-MM-UW-fast AF-00+*/
/* FIH-SW3-MM-UW-add touch AF-00+*/
static long isx006_set_touch_focus(uint16_t x, uint16_t y, uint16_t dx, uint16_t dy, uint8_t num_roi, uint16_t preview_ratio) 
{
    int rc = 0;
    uint16_t window_size_x = 800;    
    uint16_t window_size_y = 600;    
    uint16_t reset_window_size_x = 1000;    
    uint16_t reset_window_size_y = 800;    
    uint16_t focus_limit_size_x = 2592 - 33 - window_size_x;    
    uint16_t focus_limit_size_y = 1944 - 5 - window_size_y;    

    printk("isx006_set_touch_focus: af_rect{x,y,dx,dy,num_roi} before= {%d,%d,%d,%d,%d} -----------\n", x, y, dx, dy, num_roi);

    //-------------/re-set to center focus area for single foucs mode-----------------------------------
    if((x == 1000) & (y == 1000)){       //re-set to conter focus area for single foucs mode
        printk("isx006_set_touch_focus: re-set to conter focus area for single foucs mode \n");
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C4C, (2592 /2) - (reset_window_size_x / 2), WORD_LEN);
        if (rc < 0) {
            pr_err("isx006_set_touch_focus: isx006_i2c_write_parallel(0x4C4C) failed !\n");
            goto error;
        }
        
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C4E, (1944 /2) - (reset_window_size_y / 2), WORD_LEN);
        if (rc < 0) {
            pr_err("isx006_set_touch_focus: isx006_i2c_write_parallel(0x4C4E) failed !\n");
            goto error;
        }

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C50, reset_window_size_x, WORD_LEN);//AF_OPD4_HDELAY
        if (rc < 0) {
            pr_err("isx006_set_touch_focus: isx006_i2c_write_parallel(0x4C50) failed !\n");
            goto error;
        }

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C52, reset_window_size_y, WORD_LEN);//AF_OPD4_VDELAY
        if (rc < 0) {
            pr_err("isx006_set_touch_focus: isx006_i2c_write_parallel(0x4C52) failed !\n");
            goto error;
        }

        return rc;
    }
    //-----------------------------------------------------------------------------------------

    if( preview_ratio == 4000/3){
        x = x  * 2592 /2000 + 8 + 41 - (100);
        y = y  * 1944 /2000 + 4 - (100);
    }else
    {
        x = x  * 2592 /2000 + 8 + 41 - (100);
        y = y  * 1080 /2000 + 432 + 4 - (100); //1080 = 1944 - 432 * 2
    }
    printk("isx006_set_touch_focus: af_rect{x,y,dx,dy,num_roi} = {%d,%d,%d,%d,%d} \n", x, y, dx, dy, num_roi);

    // Check {x, y} position.
    if (num_roi)// num_roi no equal 0 if support touch focus.
    {
        /* There is a restriction for setting AF window. AF window can not be set right side (33 pixel) and under (5 pixel) of 3M image (2592x1944). 
        Therefore, horizontal position has to be set to the data which adds 49 to actual position of image. Vertical position has to be set to the data 
        which adds 4 to actual position of image. Minimum horizontal size of AF window is 2 pixel and vertical size is 8 pixel. */
        if (x >= focus_limit_size_x)
        {
            printk("isx006_set_touch_focus: x position too right = {%d} \n", x);
            x = focus_limit_size_x;
        }

        if (y >= focus_limit_size_y)
        {
            printk("isx006_set_touch_focus: y position too low = {%d} \n", y);
            y = focus_limit_size_y;
        }
    }       

    printk("isx006_set_touch_focus: af_rect{x,y} = {%d,%d} \n", x, y);
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C4C, x, WORD_LEN);//AF_OPD4_HDELAY
    if (rc < 0) {
        pr_err("isx006_set_touch_focus: Write reg AF_OPD4_HDELAY failed !\n");
        goto error;
    }

    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C4E, y, WORD_LEN);//AF_OPD4_VDELAY
    if (rc < 0) {
        pr_err("isx006_set_touch_focus: Write reg AF_OPD4_VDELAY failed !\n");
        goto error;
    }

    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C50, window_size_x, WORD_LEN);//AF_OPD4_HDELAY
    if (rc < 0) {
        pr_err("isx006_set_touch_focus: Write reg AF_OPD4_VDELAY failed !\n");
        goto error;
    }

    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4C52, window_size_y, WORD_LEN);//AF_OPD4_VDELAY
    if (rc < 0) {
        pr_err("isx006_set_touch_focus: Write reg AF_OPD4_VDELAY failed !\n");
        goto error;
    }
    
    //1. Set monitor AF mode
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x002E, MONI_AF_OFF, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_monitor_af_mode: isx006_i2c_write_parallel(0x002E) failed !\n");
        goto error;
    }

    //2. MONI_REFRESH
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0012, 0x01, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_monitor_af_mode: isx006_i2c_write_parallel(0x0012) failed for refresh !\n");
        goto error;
    }
    cam_msleep(50);

    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x002E, MONI_AF_SAF, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_monitor_af_mode: isx006_i2c_write_parallel(0x002E) failed !\n");
        goto error;
    }

    //2. MONI_REFRESH
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0012, 0x01, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_monitor_af_mode: isx006_i2c_write_parallel(0x0012) failed for refresh !\n");
        goto error;
    }

    AF_skip = true;

error:
    return rc;
}
/* FIH-SW3-MM-UW-add touch AF-00-*/
/* FIH-SW3-MM-UW-fast AF-00-*/
//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}
/* FIH-SW3-MM-UW-modify touch AF-00-*/

/* FIH-SW3-MM-UW-read vendor id-00+*/
/* FIH-SW3-MM-UW-fix Macro AF fail-00+*/
/* FIH-SW3-MM-UW-flash tuning-06+*/
/* FIH-SW3-MM-UW-fix AF noise-00+*/
/* FIH-SW3-MM-UW-set AF range-00+*/ 
/* FIH-SW3-MM-UW-write OTP setting-00+*/
int isx006_set_AF_Range(int af_mode) 
{
    int rc = 0;
    printk("isx006_set_AF_Range: AF_mode =%d \n", af_mode);

    /*MM-UW-fix DP device green preview-00+*/
    /*MM-UW-set AF range-00+*/
    if(slave_add == ISX006_PARALLEL_SADDR)
        return rc;
    /*MM-UW-set AF range-00-*/
    /*MM-UW-fix DP device green preview-00-*/
    
    switch (af_mode) {
    case AF_MODE_AUTO:
    case AF_MODE_NORMAL:        
    case AF_MODE_CAF:    
        if(AF_full_range)
            return rc;      
        printk("isx006_set_AF_Range: AF_mode - Full range\n");
        AF_F_value = 8; //coarse search
        AF_G_value = 1023; //fullscale forDAC
        AF_H_value = 32/AF_F_value ; //fullscale forDAC
        AF_C_value = (AF_B_value - AF_A_value) / (AF_F_value - 2) + 1;
        /*printk("isx006_set_AF_Range: AF_A_value =%d \n", AF_A_value);
        printk("isx006_set_AF_Range: AF_B_value =%d \n", AF_B_value);
        printk("isx006_set_AF_Range: AF_C_value =%d \n", AF_C_value);*/
   
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486C, AF_C_value, WORD_LEN);
        if (rc < 0)
            goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4870, AF_C_value, WORD_LEN);
        if (rc < 0)
            goto error;

        AF_D_value = (AF_C_value / AF_H_value);
        /*printk("isx006_set_AF_Range: AF_D_value =%d \n", AF_D_value);*/    

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486E, AF_D_value, WORD_LEN);
        if (rc < 0)
            goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4872, AF_D_value, WORD_LEN);
        if (rc < 0)
            goto error;
        
        AF_E_value = AF_A_value + (AF_C_value * 8);
        /*printk("isx006_set_AF_Range: AF_E_value =%d \n", AF_E_value);*/

        /* full */
        if(vendor_id) //SEMCO
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, AF_A_value + 30, WORD_LEN);//AF_AREA_LOW_TYPE1
        else
        {
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, AF_A_value, WORD_LEN);//AF_AREA_LOW_TYPE1
        }
        if (rc < 0)
            goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4878, AF_B_value + (AF_C_value * 2), WORD_LEN);//AF_AREA_HIGH_TYPE1
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4844, AF_D_value * 4, WORD_LEN); 
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486A, AF_A_value, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4822, AF_D_value / 4, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4824, AF_D_value*3 /4 , WORD_LEN); 
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4838, AF_D_value * 2, WORD_LEN);
        if (rc < 0)
           goto error;
        
        AF_full_range = 1;
        
        break;        

    case AF_MODE_MACRO:
        printk("isx006_set_AF_Range: AF_mode - Marco range\n");
        AF_F_value = 16; //coarse search
        AF_G_value = 1023; //fullscale forDAC
        AF_H_value = 32/AF_F_value ; //fullscale forDAC
        AF_C_value = (AF_B_value - AF_A_value) / (AF_F_value - 2) + 1;
        /*printk("isx006_set_AF_Range: AF_A_value =%d \n", AF_A_value);
        printk("isx006_set_AF_Range: AF_B_value =%d \n", AF_B_value);
        printk("isx006_set_AF_Range: AF_C_value =%d \n", AF_C_value);*/

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486C, AF_C_value, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4870, AF_C_value, WORD_LEN);
        if (rc < 0)
           goto error;

        AF_D_value = (AF_C_value / AF_H_value);
        /*printk("isx006_set_AF_Range: AF_D_value =%d \n", AF_D_value);*/
    
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486E, AF_D_value, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4872, AF_D_value, WORD_LEN);
        if (rc < 0)
           goto error;

        AF_E_value = AF_A_value + (AF_C_value * 8);
        /*printk("isx006_set_AF_Range: AF_E_value =%d \n", AF_E_value);*/

        /* Macro */
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x487A, AF_A_value + (AF_C_value * 5), WORD_LEN);//AF_AREA_LOW_TYPE2
        //rc = isx006_i2c_write_parallel(isx006_client->addr, 0x487A, AF_B_value - (AF_C_value * 2), WORD_LEN);//AF_AREA_LOW_TYPE2    
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x487C, AF_B_value + (AF_C_value * 2), WORD_LEN);//AF_AREA_HIGH_TYPE2
        //rc = isx006_i2c_write_parallel(isx006_client->addr, 0x487A, AF_B_value, WORD_LEN);//AF_AREA_LOW_TYPE2    
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4844, AF_C_value * 2, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486A, AF_A_value, WORD_LEN);    
        if (rc < 0)
           goto error;
        AF_full_range = 0;
        
        break;

    case AF_MODE_INFINITY:
        printk("isx006_set_AF_Range: AF_mode - Infinity range\n");
        AF_F_value = 16; //coarse search
        AF_G_value = 1023; //fullscale forDAC
        AF_H_value = 32/AF_F_value ; //fullscale forDAC
        AF_C_value = (AF_B_value - AF_A_value) / (AF_F_value - 2) + 1;
        /*printk("isx006_set_AF_Range: AF_A_value =%d \n", AF_A_value);
        printk("isx006_set_AF_Range: AF_B_value =%d \n", AF_B_value);
        printk("isx006_set_AF_Range: AF_C_value =%d \n", AF_C_value);*/

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486C, AF_C_value, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4870, AF_C_value, WORD_LEN);
        if (rc < 0)
           goto error;

        AF_D_value = (AF_C_value / AF_H_value);
        /*printk("isx006_set_AF_Range: AF_D_value =%d \n", AF_D_value);*/

    
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486E, AF_D_value, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4872, AF_D_value, WORD_LEN);
        if (rc < 0)
           goto error;

        AF_E_value = AF_A_value + (AF_C_value * 8);
        /*printk("isx006_set_AF_Range: AF_E_value =%d \n", AF_E_value);*/

        /* INFINITY */
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x487E, AF_A_value, WORD_LEN); //AF_AREA_LOW_TYPE3
        if (rc < 0)
           goto error;
        
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4880, AF_A_value + (AF_C_value * 5), WORD_LEN); //AF_AREA_HIGH_TYPE3
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4844, AF_C_value * 2, WORD_LEN);
        if (rc < 0)
           goto error;

        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x486A, AF_A_value, WORD_LEN);    
        if (rc < 0)
           goto error;
        AF_full_range = 0;
        
        break;

    default:
        printk("isx006_set_AF_Range: ERR: Mode = %d, This is invalid !\n", af_mode);
        return -EINVAL;
    }

    if(isx006_scene == SCENE_AUTO)
    {
        switch (af_mode) {
        case AF_MODE_AUTO:    
        case AF_MODE_CAF:  
        case AF_MODE_NORMAL:    
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x01D3, 0x00, BYTE_LEN);
            if (rc < 0)
               goto error;
            break;

        case AF_MODE_MACRO:
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x01D3, 0x04, BYTE_LEN);
            if (rc < 0)
               goto error;
            break;
            
        case AF_MODE_INFINITY:
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x01D3, 0x08, BYTE_LEN);
            if (rc < 0)
               goto error;
            break;

        default:
            printk("isx006_set_AF_Range: ERR: Mode = %d, This is invalid !\n", af_mode);
            return -EINVAL;
        }
    }
    printk("isx006_set_AF_Range: ----------X \n");
    return rc;

error:
    return rc;
}
/* FIH-SW3-MM-UW-write OTP setting-00-*/
/* FIH-SW3-MM-UW-set AF range-00-*/ 
/* FIH-SW3-MM-UW-fix AF noise-00-*/
/* FIH-SW3-MM-UW-flash tuning-06-*/
/* FIH-SW3-MM-UW-fix Macro AF fail-00-*/
/* FIH-SW3-MM-UW-read vendor id-00-*/

/* FIH-SW3-MM-UW-read vendor id-00-01+*/
/* FIH-SW3-MM-UW-modify touch AF-00+*/
/* FIH-SW3-MM-UW-fix Macro AF fail-00+*/
/* FIH-SW3-MM-UW-flash tuning-07+*/
/* FIH-SW3-MM-UW-fast AF-01+*/
/* FIH-SW3-MM-UW-fast AF-00+*/
/* FIH-SW3-MM-UW-flash tuning-04+*/
/*MTD-MM-SL-ModifyPicDetailInfo-01+{*/
/* FIH-SW3-MM-UW-re-focus-00+*/
/* FIH-SW3-MM-UW-flash tuning-00+*/
/* FIH-SW3-MM-UW-fix AF not work-00+*/
/* FIH-SW3-MM-UW-fix capture fail-00+*/
/* FIH-SW3-MM-UW-fix night capture fail-00+*/
/* FIH-SW3-MM-UW-cancel AF-00+*/
/*MM-UW-fix high AF power-00+*/
/*MM-UW-fix auto flash fail in DP 00+*/
//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00*{
/*MM-UW-add auto flash 02+*/
/*MM-UW-support AF+++*/
/* FIH-SW3-MM-UW-set AF range-00+*/ 
static long isx006_set_AF(int af_mode) 
{
    int rc = 0;
    int led_mode = 0;
    bool Low_Light = false;
    uint16_t AF_state = 0xFF;
    uint16_t v_read = 0x0; 
    int i;

    if(af_mode != AF_MODE_POLLING)
        printk("isx006_set_AF(%d): ----------E\n", af_mode);

    switch (af_mode) {
    case AF_MODE_NORMAL:
    case AF_MODE_AUTO:
        torch_enable = false;
        
        /*get current environment AE valuel----------------------------*/
        Low_Light = isx006_get_AE_value();
        
        /*get current flash model-------------------------------------*/
        led_mode = msm_soc_get_led_mode();
        printk("isx006_set_AF: led_mode = %d !\n", led_mode);  

        /*judge pre-flash or not--------------------------------------*/
        if( led_mode == LED_MODE_RED_EYE || led_mode == LED_MODE_AUTO)
        {  
            if(Low_Light)
                torch_enable = true;
        } 

         /*pre-flash-------------------------------------------------*/
        if( led_mode == LED_MODE_ON) 
        {   
                rc = msm_soc_torch_trigger();
                if (rc < 0) 
                    printk("isx006_set_AF: msm_soc_torch_trigger() failed !\n");
        }
        else if( torch_enable)
        {
                printk("isx006_set_AF: flash enable!\n");
                rc = msm_soc_torch_trigger();
                if (rc < 0) 
                    printk("isx006_set_AF: msm_soc_torch_trigger() failed !\n");
                
                /* Set LED & AE/AWB Control----------------------------*/
                rc = isx006_PreFlash_setting();
                if (rc < 0) 
                    printk("isx006_set_AF: isx006_PreFlash_setting failed !\n");

        }
        if(AF_full_range)
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, AF_A_value, WORD_LEN);//AF_AREA_LOW_TYPE1
            
        /*check CAF state*/
        rc = isx006_i2c_read_parallel(isx006_client->addr, 0x6D76, &AF_state, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_set_AF: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x6D76);
            goto error;
        }
        
        if (AF_state == 15 || AF_state == 12) //CAF_LOCK
        {
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4887, 0x01, BYTE_LEN); 
            AF_type = 1; //fine search
        }
        else
        {
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4887, 0x02, BYTE_LEN); 
            AF_type = 0; //full search
        }

        isx006_i2c_read_parallel(isx006_client->addr, 0x002E, &v_read, BYTE_LEN);
        if(AF_skip)
        {
            printk("isx006_set_AF: did touch AF before, skip AF here\n");
        }
        else if(v_read == 0)
        {
            printk("isx006_set_AF: restart AF \n");
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0015, 0x01, BYTE_LEN);
            if(rc < 0)
                goto error;
        }else
       {
            rc = isx006_set_monitor_af_mode(MONI_AF_SAF, "MONI_AF_SAF");

            if(rc < 0)
                goto error;
       }

        break;

    case AF_MODE_INFINITY:
    case AF_MODE_MACRO:
        rc = isx006_set_AF_Range(af_mode);        
        if(rc < 0)
            goto error;
        break;

    case AF_MODE_CAF:    
        if(current_af_mode == AF_MODE_GET_STATE)
        {
            f_CAF = true;
        }
        else
        {   
            if(vendor_id) //SEMCO
                rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, AF_A_value + 30, WORD_LEN);//AF_AREA_LOW_TYPE1
            rc = isx006_set_monitor_af_mode(MONI_AF_CAF, "MONI_AF_CAF");
            if(rc < 0)
                goto error;
        }
        break;

    case AF_MODE_OFF:
        /*MM-UW-reduce knocking noise-00+*/
        rc = isx006_set_monitor_af_mode(MONI_AF_MF, "MONI_AF_MF");
        if(rc < 0)
            goto error;

        rc = isx006_MF_position(isx006_client->addr, 0);
        if (rc < 0)
            printk ("isx006_set_AF: isx006_check_MF fail.\n");
        /*MM-UW-reduce knocking noise-00-*/
        break;

    case AF_MODE_POLLING:
        rc = isx006_check_AF(isx006_client->addr, "check AF polling status");
        if(rc < 0)
            goto error;
        break;

    case AF_MODE_GET_STATE:
        rc = isx006_get_AF_state(isx006_client->addr, "check AF result");
        if(rc < 0)
        {
            if(!AF_type)//full search
            {
                goto error;
            }
            else
            {
                AF_type = 0;
                printk("isx006_set_AF: fine search fail !!\n");
                rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4887, 0x02, BYTE_LEN); 
                rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0015, 0x01, BYTE_LEN);
                for(i = 0; i < 150; i++)
                {
                    rc = isx006_check_AF(isx006_client->addr, "check AF polling status");
                }
                rc = isx006_get_AF_state(isx006_client->addr, "check AF result");
            }
        }
        AF_skip = false;
        break;

    default:
        rc = -EINVAL;
        printk("isx006_set_AF: ERR: Mode = %d, This is invalid !\n", af_mode);
        break;
    }
    current_af_mode = af_mode;

    printk("isx006_set_AF: ----------X \n");
    
error:
    return rc;
}
/* FIH-SW3-MM-UW-set AF range-00-*/ 
/*MM-UW-support AF---*/
/*MM-UW-add auto flash 02-*/
//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00*}
/*MM-UW-fix auto flash fail in DP 00-*/
/*MM-UW-fix high AF power-00-*/
/* FIH-SW3-MM-UW-fix capture fail-00-*/
/* FIH-SW3-MM-UW-re-focus-00-*/
/* FIH-SW3-MM-UW-fast AF-00-*/
/* FIH-SW3-MM-UW-fast AF-01-*/
/* FIH-SW3-MM-UW-fix Macro AF fail-00-*/
/* FIH-SW3-MM-UW-modify touch AF-00-*/

/* FIH-SW3-MM-UW-add reduce_red_eye-00-*/
/*MM-UW-add auto flash 00-*/
/* FIH-SW3-MM-UW-cancel AF-00-*/
/* FIH-SW3-MM-UW-fix night capture fail-00-*/
/* FIH-SW3-MM-UW-fix AF not work-00-*/
/* FIH-SW3-MM-UW-flash tuning-00-*/
/*MTD-MM-SL-ModifyPicDetailInfo-01*}*/
/* FIH-SW3-MM-UW-flash tuning-07-*/
/* FIH-SW3-MM-UW-read vendor id-01-*/

/* FIH-SW3-MM-SL-SetFPSForRecordMMS-00*{ */
/* FIH-SW3-MM-URI-Set FPS-00+ */
static int32_t isx006_set_fps(uint16_t fps)
{
    int32_t rc = 0;
    
    printk ("isx006_set_fps ------- value =%d\n", fps); 
    if(fps <=15){    
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0383, 0x03, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_set_fps: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x0383);
            goto error;
        }
    }
    else{
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0383, 0x02, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_set_fps: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x0383);
            goto error;
        }    
    }

    /* MTD-MM-SL-FixCTS-00+{ */
    //Re-fresh register, that fps could be set successfully  
    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0012, 0x01, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_fps: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x0012);
        goto error;
    }
    /* MTD-MM-SL-FixCTS-00+} */

error:
    return rc;
}
/* FIH-SW3-MM-URI-Set FPS-00- */
/* FIH-SW3-MM-SL-SetFPSForRecordMMS-00*} */

/* FIH-SW3-MM-SL-PatchForCameraFeature-02*{ */
/* FIH-SW3-MM-SL-PatchForCameraFeature-01*{ */
/* FIH-SW3-MM-URI-Add WB-00+ */
#ifdef CONFIG_FIH_BRIGHTNESS
static long isx006_set_brightness(int brightness) 
{
    long rc = 0;
    unsigned short brightness_val = 0;

    printk ("isx006_set_brightness:%d\n", brightness);
    
    switch (brightness) {
    case 6:
        brightness_val = 0x06;
        printk ("isx006_set_brightness = 2");
        break;
        
    case 5:
        brightness_val = 0x05;
        printk ("isx006_set_brightness = 1.66");
        break;
        
    case 4:
        brightness_val = 0x04;
        printk ("isx006_set_brightness = 1.33");
        break;
        
    case 3:
        brightness_val = 0x03;
        printk ("isx006_set_brightness = 1");
        break;
        
    case 2:
        brightness_val = 0x02;
        printk ("isx006_set_brightness = 0.66");
        break;
        
      case 1:
        brightness_val = 0x01; 
        printk ("isx006_set_brightness = 0.33");
        break;

    case 0:
        brightness_val = 0x00;
        printk ("isx006_set_brightness = 0");
        break;
        
    case -1:
        brightness_val = 0xff;
        printk ("isx006_set_brightness = -0.33");
        break;
        
    case -2:
        brightness_val = 0xfe;
        printk ("isx006_set_brightness = -0.66");
        break;
        
    case -3:
        brightness_val = 0xfd;
        printk ("isx006_set_brightness = -1");
        break;
        
    case -4:
        brightness_val = 0xfc;
        printk ("isx006_set_brightness = -1.33");
        break;
        
    case -5:
        brightness_val = 0xfb;
        printk ("isx006_set_brightness = -1.66");
        break;
        
    case -6:
        brightness_val = 0xfa;
        printk ("isx006_set_brightness = -2");
        break;
        
    default:
        printk ("isx006_set_brightness, wrong value setting\n");
        return -EINVAL;
    }

    rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0080, brightness_val, BYTE_LEN);
    if (rc < 0) {
        pr_err("isx006_set_brightness: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x0080);
        goto error;
    }
    
    isx006_brightness = brightness;
    
error:
    return rc;
}
#endif

/* FIH-SW3-MM-SL-PatchForCameraFeature-02*} */
#ifdef CONFIG_FIH_WB
static long isx006_set_wb(int wb) 
{
    long rc = 0;
    
    printk ("isx006_set_wb:%d\n", wb);
    
    switch (wb) {
    case WB_AUTO:
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0102, 0x20, BYTE_LEN);
        printk ("isx006_set_wb = WB_AUTO\n");
        break;
        
    case WB_INCANDESCENT:
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0102, 0x08, BYTE_LEN);        
        printk ("isx006_set_wb = WB_INCANDESCENT\n");
        break;
        
    case WB_FLUORESCENT:
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0102, 0x07, BYTE_LEN);
        printk ("isx006_set_wb = WB_FLUORESCENT\n");
        break;
        
    case WB_DAYLIGHT:
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0102, 0x14, BYTE_LEN);
        printk ("isx006_set_wb = WB_DAYLIGHT\n");
        break;
        
    case WB_CLOUDY_DAYLIGHT:
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0102, 0x16, BYTE_LEN);        
        printk ("isx006_set_wb = WB_CLOUDY_DAYLIGHT\n");
        break;

    default:
        printk ("isx006_set_wb, wrong value setting\n");
        rc =  -EINVAL;
        break;
    }

    if (rc < 0) {
        pr_err("isx006_set_wb: saddr(0x%x): Write REG(0x%x) failed !\n",isx006_client->addr, 0x0102);
        goto error;
    }
    isx006_wb = wb;
    
error:
    return rc;
}

#endif

/*MM-UW-set metering 00+*/
#ifdef CONFIG_FIH_METRY
static long isx006_set_AE_meter(int meter) 
{
    long rc = 0;
    uint16_t v_read = 0xFF;
    uint16_t v_temp = 0xFF;
    
    rc = isx006_i2c_read_parallel(isx006_client->addr, 0x0104, &v_read, BYTE_LEN);
    v_temp = v_read & 0xFC;    
    printk ("isx006_set_AE_meter:%d\n", meter);    
    
    switch (meter) {
    case AE_AUTO: 
    case AE_CENTER: 
        v_temp = v_temp |0x01;    
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0104, v_temp, BYTE_LEN);
        printk ("isx006_set_AE_meter: Center\n");
        break;
    case AE_MULTI:
        v_temp = v_temp |0x00;   
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0104, v_temp, BYTE_LEN);            
        printk ("isx006_set_AE_meter: Multi\n");
        break;
    case AE_SPOT: 
        v_temp = v_temp |0x02;   
        rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0104, v_temp, BYTE_LEN);
        printk ("isx006_set_AE_meter: Spot\n");
        break;

    default: {
        printk ("isx006_set_AE_meter, wrong value setting\n");

        return -EINVAL;
        }
    }
    isx006_meter = meter;
    return rc;
}
#endif
/*MM-UW-set metering 00-*/

/* FIH-SW3-MM-UW-fix night capture fail-00+*/
/* FIH-SW3-MM-UW-fix focus ramge-00+*/
/* FIH-SW3-MM-UW-set AF range-00+*/ 
#ifdef CONFIG_FIH_SCENE
static long isx006_set_scene(int scene) 
{
    long rc = 0;

    isx006_scene = scene;

    switch (scene) {
    case SCENE_AUTO:
        printk ("isx006_set_scene: SCENE_AUTO\n");
        rc = isx006_set_AF_Range(AF_MODE_AUTO);
        if(rc < 0)
            goto error;

        rc = isx006_i2c_write_table_parallel(isx006_client->addr, isx006_regs.reg_auto_scene,
                           isx006_regs.reg_auto_scene_size);
        if(rc < 0)
            goto error;
        
        break;
        
    case SCENE_SNOW: 
    case SCENE_BEACH:
        printk ("isx006_set_scene SCENE_BEACH/SCENE_SNOW\n");
        rc = isx006_set_AF_Range(AF_MODE_AUTO);
        if(rc < 0)
            goto error;

        rc = isx006_i2c_write_table_parallel(isx006_client->addr, isx006_regs.reg_bench_snow,
                           isx006_regs.reg_auto_scene_size);
        if(rc < 0)
            goto error;

        break;
        
    case SCENE_NIGHT:
        printk ("isx006_set_scene: SCENE_NIGHT\n");
        rc = isx006_set_AF_Range(AF_MODE_INFINITY);
        if(rc < 0)
            goto error;

        rc = isx006_i2c_write_table_parallel(isx006_client->addr, isx006_regs.reg_night,
                    isx006_regs.reg_night_size);
        if(rc < 0)
            goto error;
        
        cam_msleep(333);//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*
        break;
        
    case SCENE_SPORT:
        printk ("isx006_set_scene: SCENE_SPORT\n");
        rc = isx006_set_AF_Range(AF_MODE_AUTO);
        if(rc < 0)
            goto error;

        rc = isx006_i2c_write_table_parallel(isx006_client->addr, isx006_regs.reg_sport,
                           isx006_regs.reg_sport_size);
        if(rc < 0)
            goto error;
        
        break;
        
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
    case SCENE_LANDSCAPE:
        printk ("isx006_set_scene: SCENE_LANDSCAPE\n");
        rc = isx006_set_AF_Range(AF_MODE_INFINITY);
        if(rc < 0)
            goto error;
        rc = isx006_i2c_write_table_parallel(isx006_client->addr, isx006_regs.reg_landscape,
                           isx006_regs.reg_landscape_size);
        if(rc < 0)
            goto error;
        
        break;

    case SCENE_DOCUMENT:
        printk ("isx006_set_scene: SCENE_DOCUMENT\n");
        rc = isx006_set_AF_Range(AF_MODE_MACRO);
        if(rc < 0)
            goto error;

        rc = isx006_i2c_write_table_parallel(isx006_client->addr, isx006_regs.reg_document,
                           isx006_regs.reg_document_size);
        if(rc < 0)
            goto error;
        
        break;
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}
            
    default:
        printk ("isx006_set_scene: wrong value setting\n");
        return -EINVAL;
    }
    return rc;

error:
    printk ("isx006_set_scene: Failed !\n");
    return rc;
}
#endif
/* FIH-SW3-MM-UW-set AF range-00-*/ 
/* FIH-SW3-MM-URI-Add WB-00- */
/* FIH-SW3-MM-SL-PatchForCameraFeature-01*} */
/* FIH-SW3-MM-UW-fix focus ramge-00-*/
/* FIH-SW3-MM-UW-fix night capture fail-00-*/

static int32_t isx006_write_exp_gain(uint16_t gain, uint32_t line)
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

    return rc;
}

static int32_t isx006_set_pict_exp_gain(uint16_t gain, uint32_t line)
{
    int32_t rc = 0;

    rc = isx006_write_exp_gain(gain, line);
    return rc;
}

/* FIH-SW3-MM-UW-performance tuning-00+*/
//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+{
/* FIH-SW3-MM-UW-set AF range-00+*/ 
static int isx006_reg_init_task(void *arg)
{
    int32_t rc = 0;
    printk("isx006_reg_init_task: Thread create --->\n");
    
    printk("isx006_reg_init_task: Start REG_INIT. \n");
    /* set sensor init table*/
    rc = isx006_init_sensor();
    if (rc < 0) {
        pr_err("isx006_reg_init_task: REG_INIT failed !\n");
        goto error;
    }

    /* Change slave address from 0x1A to 0x3C */
    if (slave_add != isx006_client->addr)
    {   
        printk("isx006_reg_init_task: Change slave address from 0x1A to 0x3C. \n");
        rc = isx006_change_slave_address();
        if (rc < 0) {
            pr_err("isx006_reg_init_task: isx006_change_slave_address() failed !\n");
            goto error;
        }   
    }

    printk("isx006_reg_init_task: Start streaming. \n");
    /* Sensor start streaming */
    rc = isx006_start_streaming();
    if (rc < 0) {
        pr_err("isx006_reg_init_task: Start streaming failed !\n");
        goto error;
    }

    rc = isx006_set_AF_Range(AF_MODE_CAF);        
    if(rc < 0)
        goto error;

    //Waitting for invalid frames.
    cam_msleep(10);//cam_msleep(250);//T5: Max 200ms.
    printk("isx006_reg_init_task: msleep(10) for drop invalid frames.\n");
    bRegInitDone = true;
    
    printk("isx006_reg_init_task: Thread finish <---\n");
    return rc;
    
error:
    printk("isx006_reg_init_task: Thread finish <--- <Failed> !\n");
    return rc;
}
/* FIH-SW3-MM-UW-set AF range-00-*/ 
//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+}

/* FIH-SW3-MM-UW-flash tuning-06+*/
/* FIH-SW3-MM-UW-flash tuning-02+*/
/* FIH-SW3-MM-UW-flash tuning-01+*/
/* FIH-SW3-MM-UW-flash tuning-00+*/
/* FIH-SW3-MM-UW-fix capture fail-00+*/
/* FIH-SW3-MM-UW-fix night capture fail-00+*/
//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00*{
static int32_t isx006_sensor_setting(int update_type, int rt)
{
    int32_t rc = 0;
    
    struct msm_camera_csi_params isx006_csi_params;

    switch (update_type) {
    case REG_INIT:
        if (rt == RES_PREVIEW || rt == RES_CAPTURE) 
        {
            printk("isx006_sensor_setting: case REG_INIT \n");
            CameraMode = 0;/*MM-UW-support AF 01+*/
            CSI_CONFIG = false;

            bRegInitDone = false;
            reg_init_thread = kthread_create(isx006_reg_init_task, NULL, "isx006_thread");
            if (IS_ERR(reg_init_thread)) {
                rc = PTR_ERR(reg_init_thread);
                reg_init_thread = NULL;
                printk("isx006_sensor_setting: Create reg init thread failed !\n");
            }
            STARTUP = ISX006_ENABLE_HW_STANDBY;//FIH-SW-MM-MC-EnableHWStandby-00+
        }
        break;
        
    case UPDATE_PERIODIC:

       if ((rt == RES_PREVIEW) && (CSI_CONFIG == true)) 
        {
            printk("isx006_sensor_setting: case UPDATE_PERIODIC <RES_PREVIEW + CSI(1)>\n");

            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0069, 0x00, BYTE_LEN);
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x02C4, 0x0000, WORD_LEN);
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x027D, 0x00, BYTE_LEN);
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4066, 0x0A, BYTE_LEN);
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x402F, 0x0F, BYTE_LEN);
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x404C, 0x20, BYTE_LEN);
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x400B, 0x1A, BYTE_LEN);
            if (rc < 0) {
                pr_err("isx006_set_AF: Restore normal settings fail !\n");
            }  
            
            /* Change mode from Capture to monitor----------------------------*/
            rc = isx006_set_camera_mode(MONITOR_MODE, "MONITOR_MODE");
            if (rc < 0) {
                pr_err("isx006_sensor_setting: isx006_set_camera_mode(MONITOR_MODE) failed !\n");
                return rc;
            }
            rc = isx006_check_cm(isx006_client->addr, "For CM change to Monitor mode");
            if (rc < 0) {
                pr_err("isx006_sensor_setting: isx006_check_cm(For CM change to Monitor mode) failed !\n");
                return rc;
            }
            //cam_msleep(50);//Waitting for invalid frames.

        }
        
        if ((rt == RES_PREVIEW) && (CSI_CONFIG == false)) 
        {
            printk("isx006_sensor_setting: case UPDATE_PERIODIC <RES_PREVIEW + CSI(0)>\n");

            /* stop streaming */
            // --- ByPass for bring up ---

            //cam_msleep(50);//Waitting for streaming stop.

            if (CSI_CONFIG == false) {
                printk("isx006_sensor_setting: CSI_CONFIG  = 0, Pre CSI config.\n");
                msm_camio_vfe_clk_rate_set(192000000);
                isx006_csi_params.lane_cnt = 2;
                isx006_csi_params.data_format = CSI_8BIT;
                isx006_csi_params.lane_assign = 0xe4;
                isx006_csi_params.dpcm_scheme = 0;
                isx006_csi_params.settle_cnt = 0x14;
                rc = msm_camio_csi_config(&isx006_csi_params);

                cam_msleep(50);//cam_msleep(200)//Waitting for csi config done.
                CSI_CONFIG = true;
            }

            /* Sensor start streaming */
            if (reg_init_thread != NULL)
            {
                printk("isx006_sensor_setting: Trigger for reg init and start streaming.\n");
                wake_up_process(reg_init_thread);//Trigger for reg init and start streaming.
            }
            else//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+{
            {
                rc = isx006_exit_standby(ACT_EXIT_STANDBY);
                if (rc < 0)
                    return rc;
            }//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+}
        }

        if (rt == RES_CAPTURE)
        {
            printk("isx006_sensor_setting: case UPDATE_PERIODIC <RES_CAPTURE>\n");

            if(isx006_scene == SCENE_NIGHT)
                cam_msleep(300);//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*
            else
                cam_msleep(50);  
            
            /* Change mode from Monitor to capture*/
            rc = isx006_set_camera_mode(CAPTURE_MODE, "CAPTURE_MODE");
            if (rc < 0) {
                pr_err("isx006_sensor_setting: isx006_set_camera_mode(CAPTURE_MODE) failed !\n");
                return rc;
            }

            rc = isx006_check_cm(isx006_client->addr, "For CM change to Capture mode");
            if (rc < 0) {
                pr_err("isx006_sensor_setting: isx006_check_cm(For CM change to Capture mode) failed !\n");
                return rc;
            }
            //cam_msleep(100);//cam_msleep(50);//Waitting for invalid frames.
            //Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+{
            if(isx006_scene == SCENE_NIGHT)
                cam_msleep(300);
            else
                cam_msleep(50); 
            //Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+}
        }
        break;
    default:
        rc = -EINVAL;
        break;
    }

    return rc;
}
//FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00*}
/* FIH-SW3-MM-UW-performance tuning-00-*/
/* FIH-SW3-MM-UW-fix night capture fail-00-*/
/* FIH-SW3-MM-UW-fix capture fail-00-*/
/* FIH-SW3-MM-UW-flash tuning-00-*/
/* FIH-SW3-MM-UW-flash tuning-01-*/
/* FIH-SW3-MM-UW-flash tuning-02-*/
/* FIH-SW3-MM-UW-flash tuning-06-*/

static int32_t isx006_video_config(int mode)
{

    int32_t rc = 0;
    int rt;
    printk("isx006_video_config---------------E\n");
    /* change sensor resolution if needed */
    if (isx006_ctrl->prev_res == QTR_SIZE){
        rt = RES_PREVIEW;
    }
    else
        rt = RES_CAPTURE;

    if(f_CAF)
    {    
        if(vendor_id) //SEMCO
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x4876, AF_A_value + 30, WORD_LEN);//AF_AREA_LOW_TYPE1
        rc = isx006_set_monitor_af_mode(MONI_AF_CAF, "MONI_AF_CAF");
        if(rc < 0)
             printk("isx006_video_config: switch AF mode to CAF fail !!\n");
    }
    rc = isx006_sensor_setting(UPDATE_PERIODIC, rt);
    if(rc < 0)
        goto error;

    f_CAF = false;

    isx006_ctrl->curr_res = isx006_ctrl->prev_res;
    isx006_ctrl->sensormode = mode;
    printk("isx006_video_config---------------X\n");
    return rc;
    
error:
    printk("isx006_video_config: ---------------X <Failed> !\n");
    return rc;
}

/* FIH-SW3-MM-UW-fix Macro AF fail-00+*/
/* FIH-SW3-MM-UW-flash tuning-07+*/
/* FIH-SW3-MM-UW-flash tuning-06+*/
/* FIH-SW3-MM-UW-flash tuning-04+*/
/* FIH-SW3-MM-UW-flash tuning-02+*/
/*MTD-MM-SL-ModifyPicDetailInfo-01*{*/
/* FIH-SW3-MM-UW-flash tuning-00+*/
/*MM-UW-fix auto flash fail in DP 00+*/
/*MM-UW-add auto flash 03+*/
/*MM-UW-add auto flash 02+*/
/*MM-UW-add auto flash 00+*/
/* FIH-SW3-MM-UW-add reduce_red_eye-00+*/
static int32_t isx006_snapshot_config(int mode)
{
    int32_t rc = 0;
    int rt;
    int led_mode = 0;
    uint16_t v_read = 0x0;            
    int32_t Diff = 0;
    uint16_t Diff_index = 0;
    int i = 0;
    uint16_t read_value = 0;

    printk("isx006_snapshot_config---------------E\n");
    
    /*get current flash mode*/
    led_mode = msm_soc_get_led_mode();
    
    /*judge pre-flash or not--------------------------------------*/
    if(led_mode == LED_MODE_ON)
    {
        printk("isx006_snapshot_config--fill flash\n");
        if(isx006_get_AE_value())
        {
            printk("isx006_snapshot_config--fill flash & low light\n");
            flash_enable = true;
            /* Set LED & AE/AWB Control-----------------*/
            rc = isx006_PreFlash_setting();
            if (rc < 0) 
                printk("isx006_snapshot_config: isx006_PreFlash_setting failed !\n");
        }
    }
    else if( led_mode == LED_MODE_RED_EYE || led_mode == LED_MODE_AUTO )
    {
        if(torch_enable)
        {
            printk("isx006_snapshot_config--torch & flash enable\n");
            flash_enable = true;
        }
        else
        {
            printk("isx006_snapshot_config--flash enable\n");
            if(isx006_get_AE_value())
            {
                printk("isx006_snapshot_config--flash enable & low light\n");
                flash_enable = true;
                /* Set LED & AE/AWB Control-----------------*/
                rc = isx006_PreFlash_setting();
                if (rc < 0) 
                    printk("isx006_snapshot_config: isx006_PreFlash_setting failed !\n");
            }
        }
    }

    /*calulate exposure gain for flash------------------------------*/
    if(flash_enable)
    {
        rc = msm_soc_torch_trigger(); 
        cam_msleep(200);

        /* 02.Check HALF_MOVE_STS ----------------*/

        /* Make sure operation mode is changed */
        printk("isx006_snapshot_config: check HALF_MOVE_STS\n");
        for (i = 0; i < ISX006_AE_RETRY_COUNT; i++)
        {
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x6C00, &v_read, BYTE_LEN);
            if (rc < 0) {
                pr_err("isx006_snapshot_config: isx006_i2c_read_parallel failed, REG(0x%x) !\n", 0x6C00);
                goto error;
            }
            if (v_read == 0)
                break;
            cam_msleep(10);    
        }
        
        if (i >= ISX006_AE_RETRY_COUNT)
        {
            pr_err("isx006_snapshot_config: check HALF_MOVE_STS fail !\n");
        }

        /*Get AESCL_NOW--------------------------*/
        if (slave_add == isx006_client->addr)
        {
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x028A, &read_value, WORD_LEN);   
        }else{
            rc = isx006_i2c_read(isx006_client->addr, 0x028A, &read_value, WORD_LEN);
        }  
        AESCL_NOW = read_value;
            

        /*Get ERRSCL_NOW-------------------------*/
        if (slave_add == isx006_client->addr)
        {
            rc = isx006_i2c_read_parallel(isx006_client->addr, 0x0286, &read_value, WORD_LEN);   
        }else{
            rc = isx006_i2c_read(isx006_client->addr, 0x0286, &read_value, WORD_LEN);
        }  
        if(rc < 0) {
            printk("isx006_get_AE_value: read AE value failed !\n");
        }

        if( read_value >= 0x00008000 )
            ERRSCL_NOW = (read_value - 0x0000FFFF -1);
        else
            ERRSCL_NOW = (read_value & 0x0000FFFF);
        
        /*----------------------------------------*/

        printk("isx006_snapshot_config: AESCL_AUTO = %d, ERRSCL_AUTO = %d\n", AESCL_AUTO, ERRSCL_AUTO);
        printk("isx006_snapshot_config: AESCL_NOW = %d, ERRSCL_NOW = %d\n", AESCL_NOW, ERRSCL_NOW);

        Diff = (AESCL_NOW + ERRSCL_NOW) -(AESCL_AUTO + ERRSCL_AUTO);
        //printk("isx006_snapshot_config+: Diff = %d \n", Diff);
        /* ----------------------------------------*/
        if(Diff < 0)
            Diff_index = 0;
        else if((Diff - (Diff/10) * 10) < 5)
            Diff_index = (Diff/10);
        else
            Diff_index = (Diff/10) + 1;
        
        printk("isx006_snapshot_config: Diff_index = %d \n", Diff_index);

        if(Diff_index >= offset_size -1)
        {
            Diff_index = offset_size - 1;
        }
        
        if(led_mode == LED_MODE_ON)
        {
            if(isx006_get_AE_value())
                rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0282, (x_8[Diff_index] - ERRSCL_NOW) + (0x0000FFFF + 1), WORD_LEN);
        }
        else
       {
            rc = isx006_i2c_write_parallel(isx006_client->addr, 0x0282, (x_8[Diff_index] - ERRSCL_NOW) + (0x0000FFFF + 1), WORD_LEN);
        }
            
    }
    
    /*change sensor resolution if needed */
    if (isx006_ctrl->curr_res != isx006_ctrl->pict_res) {
        if (isx006_ctrl->pict_res == QTR_SIZE)
            rt = RES_PREVIEW;
        else
            rt = RES_CAPTURE;
        
        rc = isx006_sensor_setting(UPDATE_PERIODIC, rt);
        if(rc < 0)
            goto error;
    }

    isx006_ctrl->curr_res = isx006_ctrl->pict_res;
    isx006_ctrl->sensormode = mode;

    //SW2D2-MM-MC-Camera-BringUpLm3561ForFlashLed-00+{
    //Add condition type for flash trigger
    if(led_mode == LED_MODE_RED_EYE)
    {
        printk("isx006_snapshot_config: led_mode = LED_MODE_RED_EYE\n");
        if(flash_enable){
            rc = msm_soc_flash_trigger();
            if (rc < 0)
                printk("isx006_snapshot_config: msm_soc_flash_trigger 1 failed !\n");
            cam_msleep(300);

            rc = msm_soc_flash_trigger_off();
            if (rc < 0)
                printk("isx006_snapshot_config: msm_soc_flash_trigger_off failed !\n");

            cam_msleep(100);

            rc = msm_soc_flash_trigger();
            if (rc < 0)
                printk("isx006_snapshot_config: msm_soc_flash_trigger 2 failed !\n");
        }
    }
    else if(led_mode == LED_MODE_AUTO)
    {
        printk("isx006_snapshot_config: led_mode = LED_MODE_AUTO\n");
        if(flash_enable){
            rc = msm_soc_flash_trigger();
            if (rc < 0)
                printk("isx006_snapshot_config: msm_soc_flash_trigger failed !\n");
        }
    }
    else if(led_mode == LED_MODE_ON)
    {    
        printk("isx006_snapshot_config: led_mode = LED_MODE_ON\n");
        rc = msm_soc_flash_trigger();
        if (rc < 0)
            printk("isx006_snapshot_config: msm_soc_flash_trigger failed!\n");
    }
    else
    {
        printk("isx006_snapshot_config: led_mode == LED_MODE_OFF\n");
    }
    //SW2D2-MM-MC-Camera-BringUpLm3561ForFlashLed-00+}

    flash_enable = false;
    torch_enable = false;
    printk("isx006_snapshot_config---------------X\n");
    return rc;
    
error:
    printk("isx006_snapshot_config: ---------------X <Failed> !\n");
    return rc;
}
/* FIH-SW3-MM-UW-add reduce_red_eye-00-*/
/*MM-UW-add auto flash 00-*/
/*MM-UW-add auto flash 02-*/
/*MM-UW-add auto flash 03-*/
/*MM-UW-fix auto flash fail in DP 00-*/
/* FIH-SW3-MM-UW-flash tuning-00-*/
/*MTD-MM-SL-ModifyPicDetailInfo-01*}*/
/* FIH-SW3-MM-UW-flash tuning-02-*/
/* FIH-SW3-MM-UW-flash tuning-04-*/
/* FIH-SW3-MM-UW-flash tuning-06-*/
/* FIH-SW3-MM-UW-flash tuning-07-*/
/* FIH-SW3-MM-UW-fix Macro AF fail-00-*/

static int32_t isx006_raw_snapshot_config(int mode)
{
    int32_t rc = 0;
    int rt;

    /* change sensor resolution if needed */
    if (isx006_ctrl->curr_res != isx006_ctrl->pict_res) {
        if (isx006_ctrl->pict_res == QTR_SIZE)
            rt = RES_PREVIEW;
        else
            rt = RES_CAPTURE;
        if (isx006_sensor_setting(UPDATE_PERIODIC, rt) < 0)
            return rc;
    }

    isx006_ctrl->curr_res = isx006_ctrl->pict_res;
    isx006_ctrl->sensormode = mode;
    return rc;
}

static int32_t isx006_set_sensor_mode(int mode,
        int res)
{
    int32_t rc = 0;

    switch (mode) {
    case SENSOR_PREVIEW_MODE:
        rc = isx006_video_config(mode);
        break;
    case SENSOR_SNAPSHOT_MODE:
        rc = isx006_snapshot_config(mode);
        break;
    case SENSOR_RAW_SNAPSHOT_MODE:
        rc = isx006_raw_snapshot_config(mode);
        break;
    //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-00*{
    case SENSOR_RESET_MODE:
        printk("isx006_set_sensor_mode: SENSOR_RESET_MODE---------------E\n");
        //01. Re-set flag variables.
        STARTUP = 0;
        //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+{
        bMainCameraIsReset = true;//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*

        //02. Re-config front camera pin.
        rc = fih_set_gpio_output_value(isx006_info->sensor_f_pwd, "CAM_VGA_STBY" , LOW);//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+
        if (rc < 0) {
            printk("isx006_set_sensor_mode: Re-config front camera CAM_VGA_STBY pin for reset failed !\n");
            return rc;
        }        
        //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+}


        //03. Power off.
        rc = isx006_power_off();
        if (rc < 0) {
            printk("isx006_set_sensor_mode: isx006_power_off for reset failed !\n");
            return rc;
        }
        //Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00*{
        cam_msleep(200);//Wait power off done.
        
        //Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+*}

        //04. Power on.
        rc = isx006_power_on(isx006_info);
        if (rc < 0) {
            printk("isx006_set_sensor_mode: isx006_power_on for reset failed !\n");
            return rc;
        }

        //05. Create thread for init reg.
        rc = isx006_sensor_setting(REG_INIT, RES_PREVIEW);
        if (rc < 0) {
            printk("isx006_set_sensor_mode: Create task thread for reset failed !\n");
            return rc;
        }

        //06. Config CSI and wake up task thread.
        rc = isx006_sensor_setting(UPDATE_PERIODIC, RES_PREVIEW);
        if (rc < 0) {
            printk("isx006_set_sensor_mode: Config CSI and wake up task thread for reset failed !\n");
            return rc;
        }

        //FIH-SW-MM-MC-ModifiedSensorResetSquence-00+{
        /* Waitting REG init thread finish init task */
        if ((reg_init_thread != NULL) && (bRegInitDone != true))
        {
            int i = 0;
            for (i = 0; i < 100; i++)
            {
                if (bRegInitDone == true)
                    break;
                cam_msleep(20);
            }
            
            if (bRegInitDone != true)
                printk("isx006_set_sensor_mode: Waiting for REG init done failed, retry count = %d ! \n", i);
            else
                printk("isx006_set_sensor_mode: Waiting for REG init done success, retry count = %d. \n", i);
        }
        reg_init_thread = NULL;
        //FIH-SW-MM-MC-ModifiedSensorResetSquence-00+}    

        isx006_ctrl->curr_res = isx006_ctrl->prev_res;
        isx006_ctrl->sensormode = 0;        
        printk("isx006_set_sensor_mode: SENSOR_RESET_MODE---------------X\n");      
        break;
    //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-00*}
    
    default:
        rc = -EINVAL;
        break;
    }
    return rc;
}

static int isx006_probe_init_done(const struct msm_camera_sensor_info *data)
{
    /*MM-UW-reduce boot time+++*/
    int rc = 0;    
    /*int rc = -EBADF;

    if (data->sensor_reset_enable) {
        gpio_direction_output(data->sensor_reset, 0);
        gpio_free(data->sensor_reset);
    }*/
    /*MM-UW-reduce boot time---*/

    rc = isx006_power_off();
    if (rc < 0)
        goto error;
        
    printk("isx006_probe_init_done: Done. \n");
    return rc;
error:
    printk("isx006_probe_init_done: Failed ! \n");
    return rc;
}

/* FIH-SW3-MM-UW-write OTP setting-00+*/
static int isx006_probe_init_sensor(const struct msm_camera_sensor_info *data)
{
    int32_t rc = 0;
    uint16_t chipid = 0xFFFF;

    printk("%s: %d\n", __func__, __LINE__);

    /* Power on for read sensor ID */
    rc = isx006_power_on(data);
    if (rc < 0) {
        printk("isx006_probe_init_sensor: isx006_power_on() failed !\n");
        goto init_probe_fail;
    }

    /* Check module is right or fault */
    /*-------------------------------------------------------------------------*/    
    rc = isx006_i2c_read(isx006_client->addr, ISX006_CID_REG, &chipid, WORD_LEN);
    if (rc < 0)
    { 
        slave_add = ISX006_PARALLEL_SADDR;
        printk("isx006_probe_init_sensor: This is a fault module !\n");    
        isx006_check_om(slave_add, "For change to PreSleep mode");

        rc = isx006_polling_state_change(slave_add, STS_PRE_SLEEP);
        if (rc < 0) {
            pr_err("isx006_probe_init_sensor: isx006_polling_state_change(STS_PRE_SLEEP) failed !\n");
            goto  init_probe_fail;
        }
        rc = isx006_i2c_read_parallel(slave_add, ISX006_CID_REG, &chipid, WORD_LEN);
    }
    else
    {
        /* Init sensor */
        /* Here to check ststus is STS_PRE_SLEEP */
        slave_add = isx006_client->addr;    
        isx006_check_om(slave_add, "For change to PreSleep mode");

        rc = isx006_polling_state_change(slave_add, STS_PRE_SLEEP);
        if (rc < 0) {
            pr_err("isx006_probe_init_sensor: isx006_polling_state_change(STS_PRE_SLEEP) failed !\n");
            goto  init_probe_fail;
        }
        rc = isx006_i2c_read(slave_add, ISX006_CID_REG, &chipid, WORD_LEN);
    }

    if (rc < 0)
        goto init_probe_fail;
    printk("isx006_probe_init_sensor: Sensor Chip ID = 0x%x\n",chipid);        
    /*-------------------------------------------------------------------------*/        

    /* Read sensor Chip ID: */
    if (((chipid != ISX006_CID_v1)&&(chipid != ISX006_CID_v2)))
    {
        rc = -ENODEV;
        printk ("isx006_probe_init_sensor: chip id not match--------------X\n");
        goto init_probe_fail;
    }
    else
    {
        printk ("isx006_probe_init_sensor: -------------chip id matched\n");
    }

    goto init_probe_done;
init_probe_fail:
    printk("isx006_probe_init_sensor: Failed !\n");
    if (data->sensor_reset_enable) {
        gpio_direction_output(data->sensor_reset, 0);
        gpio_free(data->sensor_reset);
    }
init_probe_done:
    printk(" isx006_probe_init_sensor: Finish\n");
    return rc;
}
/* FIH-SW3-MM-UW-write OTP setting-00-*/

/* FIH-SW3-MM-UW-read vendor id-01+*/
/* FIH-SW3-MM-UW-read vendor id-00+*/
int isx006_sensor_open_init(const struct msm_camera_sensor_info *data)
{
    int32_t rc = 0;
    uint16_t chipid = 0xFFFF;//FIH-SW-MM-MC-ImplementSensorReSetForIsx006-02+

    printk("Calling isx006_sensor_open_init\n");

    isx006_ctrl = kzalloc(sizeof(struct isx006_ctrl_t), GFP_KERNEL);
    if (!isx006_ctrl) {
        printk("isx006_sensor_open_init: kzalloc() failed!\n");
        rc = -ENOMEM;
        goto init_done;
    }
    isx006_ctrl->fps_divider = 1 * 0x00000400;
    isx006_ctrl->pict_fps_divider = 1 * 0x00000400;
    isx006_ctrl->prev_res = QTR_SIZE;
    isx006_ctrl->pict_res = FULL_SIZE;

    //if (data)//FIH-SW3-MM-URI-Fix Code Defect-00-
        isx006_ctrl->sensordata = data;

    /* FIH-SW3-MM-SL-AddForSoMCPanorama-00*{ */
    prev_frame_length_lines =1280; //640
    prev_line_length_pck = 960; //480
    /* FIH-SW3-MM-SL-AddForSoMCPanorama-00*} */
    snap_frame_length_lines = 2592;
    snap_line_length_pck = 1944;

    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*{
    // Check front camera state before power on main camera.
    if (bFrontCameraIsReset == true)
    {
        printk("isx006_sensor_open_init: Re-Set for FRONT_SENSOR_RESET\n");
        STARTUP = 0;
        bFrontCameraIsReset = false;
    }
    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*}

    /* Power on and enable mclk */
    rc = isx006_power_on(data);
    if (rc < 0) {
        printk("isx006_sensor_open_init: isx006_power_on() failed !\n");
        goto init_fail;
    }

    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+{
    //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-02+{
    //Read chip ID to check that I2C bus is normal.
    if (STARTUP == 0)
        rc = isx006_i2c_read_parallel(slave_add, ISX006_CID_REG, &chipid, WORD_LEN);
    else
        rc = isx006_i2c_read_parallel(isx006_client->addr, ISX006_CID_REG, &chipid, WORD_LEN);
    //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+}
    if (rc < 0)
    {
        printk ("isx006_sensor_open_init: I2C bus is abnormal. SENSOR_RESET_MODE ----> E\n");
        //01. Re-set flag variables.
        STARTUP = 0;
        //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+{
        bMainCameraIsReset = true;//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-01*

        //02 Re-config front camera pin.
        rc = fih_set_gpio_output_value(isx006_info->sensor_f_pwd, "CAM_VGA_STBY" , LOW);
        if (rc < 0) {
            printk("isx006_sensor_open_init: Re-config front camera CAM_VGA_STBY pin for reset failed !\n");
            return rc;
        }  
        //FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+}

        //03. Power off.
        rc = isx006_power_off();
        if (rc < 0) {
            printk("isx006_sensor_open_init: isx006_power_off for reset failed !\n");
            return rc;
        }
        cam_msleep(50);//Wait power off done.

        //04. Power on.
        rc = isx006_power_on(isx006_info);
        if (rc < 0) {
            printk("isx006_sensor_open_init: isx006_power_on for reset failed !\n");
            return rc;
        }
        printk ("isx006_sensor_open_init: I2C bus is abnormal. SENSOR_RESET_MODE ----> X\n");
    }
    else
        printk ("isx006_sensor_open_init: chipid = 0x%x.\n", chipid);
    //FIH-SW-MM-MC-ImplementSensorReSetForIsx006-02+}

    if(STARTUP == 0)
    {
        rc = isx006_i2c_write_parallel(slave_add, 0x3206, 0x00, BYTE_LEN);
        if (rc < 0) {
            pr_err("isx006_reg_init_task: change to Little I2C mode fail!\n");
        }
    
        /* OTP read/save value */  
        printk("isx006_reg_init_task: Start OTP read/save value. \n");
        if(slave_add == isx006_client->addr)
        {
            rc = isx006_OTP_setting();
            if (rc < 0) {
                pr_err("isx006_reg_init_task: OTP read/save value failed !\n");
            }
        }
    
        printk("isx006_sensor_open_init: init settings\n");
        if (isx006_ctrl->prev_res == QTR_SIZE){
            rc = isx006_sensor_setting(REG_INIT, RES_PREVIEW);
        }
        else{
            printk("isx006_sensor_open_init: capture settings\n");
            rc = isx006_sensor_setting(REG_INIT, RES_CAPTURE);
        }
    }
    isx006_ctrl->fps = 30 * Q8;

    if(!vendor_id) //KMOT
        rc = isx006_i2c_write_table_parallel(slave_add, isx006_regs.reg_preload3_reload, isx006_regs.reg_preload3_reload_size);

    
    if (rc < 0)
        goto init_fail;
    else
        goto init_done;
    
init_fail:
    printk("isx006_sensor_open_init: init_fail\n");
    isx006_probe_init_done(data);
    
init_done:
    printk("isx006_sensor_open_init: init_done\n");
    return rc;
}
/* FIH-SW3-MM-UW-read vendor id-00-*/
/* FIH-SW3-MM-UW-read vendor id-01-*/

static int isx006_init_client(struct i2c_client *client)
{
    /* Initialize the MSM_CAMI2C Chip */
    init_waitqueue_head(&isx006_wait_queue);
    return 0;
}

static const struct i2c_device_id isx006_i2c_id[] = {
    {"isx006", 0},
    { }
};

static int isx006_i2c_probe(struct i2c_client *client,
        const struct i2c_device_id *id)
{
    int rc = 0;
    printk("isx006_i2c_probe: called!\n");

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        printk("isx006_i2c_probe: i2c_check_functionality failed\n");
        goto probe_failure;
    }

    isx006_sensorw = kzalloc(sizeof(struct isx006_work_t), GFP_KERNEL);
    if (!isx006_sensorw) {
        printk("isx006_i2c_probe: kzalloc failed.\n");
        rc = -ENOMEM;
        goto probe_failure;
    }

    i2c_set_clientdata(client, isx006_sensorw);
    isx006_init_client(client);
    isx006_client = client;

    printk("isx006_i2c_probe: successed! rc = %d\n", rc);
    return 0;

probe_failure:
    printk("isx006_i2c_probe: failed! rc = %d\n", rc);
    return rc;
}

static int __devexit isx006_remove(struct i2c_client *client)
{
    struct isx006_work_t *sensorw = i2c_get_clientdata(client);
    free_irq(client->irq, sensorw);
    isx006_client = NULL;
    kfree(sensorw);
    return 0;
}

static struct i2c_driver isx006_i2c_driver = {
    .id_table = isx006_i2c_id,
    .probe  = isx006_i2c_probe,
    .remove = __exit_p(isx006_i2c_remove),
    .driver = {
        .name = "isx006",
    },
};

int isx006_sensor_config(void __user *argp)
{
    struct sensor_cfg_data cdata;
    long   rc = 0;
    if (copy_from_user(&cdata,
                (void *)argp,
                sizeof(struct sensor_cfg_data)))
        return -EFAULT;
    mutex_lock(&isx006_mut);

    if(cdata.cfgtype != CFG_SET_AUTO_FOCUS)
        printk("isx006_sensor_config: cfgtype = %d\n", cdata.cfgtype);

    //FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+{
    /* Waitting REG init thread finish init task */
    if (cdata.cfgtype != CFG_SET_MODE)
    {
        if ((reg_init_thread != NULL) && (bRegInitDone != true))
        {
            int i = 0;
            for (i = 0; i < 200; i++)
            {
                cam_msleep(10);
                
                if (bRegInitDone == true)
                    break;
            }
            
            if (bRegInitDone != true)
                printk("isx006_sensor_config: Waiting for REG init done failed, retry count = %d! \n", i);
            else
                printk("isx006_sensor_config: Waiting for REG init done success, retry count = %d. \n", i);
        }
        reg_init_thread = NULL;
    }
    //FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+}    
    
    switch (cdata.cfgtype) {
    case CFG_GET_PICT_FPS:
        isx006_get_pict_fps(
            cdata.cfg.gfps.prevfps,
            &(cdata.cfg.gfps.pictfps));

        if (copy_to_user((void *)argp,
            &cdata,
            sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
        
    case CFG_GET_PREV_L_PF:
        cdata.cfg.prevl_pf =
            isx006_get_prev_lines_pf();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
        
    case CFG_GET_PREV_P_PL:
        cdata.cfg.prevp_pl =
            isx006_get_prev_pixels_pl();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
        
    case CFG_GET_PICT_L_PF:
        cdata.cfg.pictl_pf =
            isx006_get_pict_lines_pf();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
    case CFG_GET_PICT_P_PL:
        cdata.cfg.pictp_pl =
            isx006_get_pict_pixels_pl();
        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
        
    case CFG_GET_PICT_MAX_EXP_LC:
        cdata.cfg.pict_max_exp_lc =
            isx006_get_pict_max_exp_lc();

        if (copy_to_user((void *)argp,
                &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
        
    /* FIH-SW3-MM-URI-Set FPS-00+ */    
    case CFG_SET_FPS:
    case CFG_SET_PICT_FPS:
        rc = isx006_set_fps(cdata.cfg.v_fps);
        break;
    /* FIH-SW3-MM-URI-Set FPS-00- */ 
    
    case CFG_SET_EXP_GAIN:
        rc = isx006_write_exp_gain(cdata.cfg.exp_gain.gain,
                cdata.cfg.exp_gain.line);
        break;
        
    case CFG_SET_PICT_EXP_GAIN:
        rc = isx006_set_pict_exp_gain(cdata.cfg.exp_gain.gain,
                cdata.cfg.exp_gain.line);
        break;
        
    case CFG_SET_MODE:
        rc = isx006_set_sensor_mode(cdata.mode, cdata.rs);
        break;
        
    case CFG_PWR_DOWN:
        //rc = isx006_power_down();
        break;
        
    case CFG_GET_AF_MAX_STEPS:
        cdata.max_steps = ISX006_TOTAL_STEPS_NEAR_TO_FAR;
        if (copy_to_user((void *)argp,
                    &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
        break;
        
    /* FIH-SW3-MM-URI-Add WB-00+ */
#ifdef CONFIG_FIH_BRIGHTNESS
    case CFG_SET_BRIGHTNESS: 
        rc = isx006_set_brightness(cdata.cfg.brightness);
        break;
#endif

#ifdef CONFIG_FIH_WB    
    case CFG_SET_WB:
        rc = isx006_set_wb(cdata.cfg.wb);
        break;
#endif

#ifdef CONFIG_FIH_METRY
    case CFG_SET_AE_METER: 
        rc = isx006_set_AE_meter(cdata.cfg.meter);
        break;
#endif

#ifdef CONFIG_FIH_SCENE
    case CFG_SET_SCENE:
        rc = isx006_set_scene(cdata.cfg.scene);
        break;
#endif

    /* FIH-SW3-MM-URI-Add WB-00- */
    /*MM-UW-support AF+++*/
    case CFG_SET_AUTO_FOCUS:
        rc = isx006_set_AF(cdata.cfg.af_mode);//FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00*
        break;
    /*MM-UW-support AF---*/
    
    /* FIH-SW3-MM-UW-add touch AF-00+*/
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+{
    case CFG_SET_TOUCH_FOCUS:
        rc = isx006_set_touch_focus(cdata.cfg.af_rect.x,
                                    cdata.cfg.af_rect.y,
                                    cdata.cfg.af_rect.dx,
                                    cdata.cfg.af_rect.dy,
                                    cdata.cfg.af_rect.num_roi,
                                    cdata.cfg.af_rect.preview_ratio);
        break;
    //FIH-SW-MM-MC-ImplementTouchFocusAndCAF-00+}
    /* FIH-SW3-MM-UW-add touch AF-00-*/
	/*MTD-MM-SL-ModifyPicDetailInfo-01+{*/
	case CFG_GET_FLASH_STATE:
        if(torch_enable){
           printk("isx006_snapshot_config--torch & flash enable\n");
           is_flash_enable = 1;
		}else{
           if(isx006_get_AE_value())
              is_flash_enable = 1;
        }
		cdata.cfg.flash_state = is_flash_enable;
		printk("isx006_sensor_config: cdata.cfg.flash_state = %d\n", cdata.cfg.flash_state);

		if (copy_to_user((void *)argp,
                    &cdata,
                sizeof(struct sensor_cfg_data)))
            rc = -EFAULT;
		
  		is_flash_enable = 0;
		break;
    /*MTD-MM-SL-ModifyPicDetailInfo-01+}*/
	
    default:
        rc = -EFAULT;
        break;
    }
    mutex_unlock(&isx006_mut);

    return rc;
}

/* FIH-SW3-MM-UW-fix cts testFocusDistances fail-00+*/
/* FIH-SW3-MM-UW-enhance stability-00+*/
/* FIH-SW3-MM-UW-fix AF not work-00+*/
/* FIH-SW3-MM-UW-AF power-00+*/
/* FIH-SW3-MM-UW-performance tune-00+*/
static int isx006_sensor_release(void)
{
    int rc = -EBADF;
    printk ("isx006_sensor_release: Start.\n"); 
    mutex_lock(&isx006_mut);

    /*MM-UW-reduce knocking noise-00+*/
    rc = isx006_set_monitor_af_mode(MONI_AF_OFF, "MONI_AF_OFF");
    if(rc < 0)
        printk ("isx006_sensor_release: Set MONI_AF_OFF fail.\n"); 
    /*MM-UW-reduce knocking noise-00-*/
    
    //FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+{
    /* Waitting REG init thread finish init task */
    if ((reg_init_thread != NULL) && (bRegInitDone != true))
    {
        int i = 0;
        for (i = 0; i < 200; i++)
        {
            printk("isx006_sensor_release: Waiting for REG init done, retry count = %d. \n", i);
            cam_msleep(10);
            
            if (bRegInitDone == true)
                break;
        }
        
        if (bRegInitDone != true)
            printk("isx006_sensor_release: Waiting for REG init done failed !\n");
        else
            printk("isx006_sensor_release: Waiting for REG init done success.\n");
    }
    reg_init_thread = NULL;
    //FIH-SW-MM-MC-ReduceMainCameraLaunchTime-00+}

    rc = isx006_power_off();
    if(rc < 0)
    {
        printk("isx006_sensor_release: enter standby fail.\n");
        STARTUP = 0;
        bMainCameraIsReset = true;
        rc = isx006_power_off();
        if(rc < 0)
        {
            printk("isx006_sensor_release: Re-PowerOff fail.\n");
        }
    }
 
    kfree(isx006_ctrl);
    isx006_ctrl = NULL;
    CSI_CONFIG = false;
    AF_skip = false;
 
    printk("isx006_sensor_release: Completed.\n");
    mutex_unlock(&isx006_mut);

    return rc;
}
/* FIH-SW3-MM-UW-performance tune-00-*/
/* FIH-SW3-MM-UW-AF power-00-*/
/* FIH-SW3-MM-UW-fix AF not work-00-*/
/* FIH-SW3-MM-UW-enhance stability-00-*/
/* FIH-SW3-MM-UW-fix cts testFocusDistances fail-00-*/

static int isx006_sensor_probe(const struct msm_camera_sensor_info *info,
        struct msm_sensor_ctrl *s)
{
    int rc = 0;
    STARTUP = 0;
    printk("isx006_sensor_probe: E \n");

    isx006_info = info;//MTD-SW3-MM-UW-camframe timeout-00+

    rc = i2c_add_driver(&isx006_i2c_driver);
    if (rc < 0 || isx006_client == NULL) {
        rc = -ENOTSUPP;
        printk("isx006_sensor_probe: I2C add driver failed !");
        goto probe_fail_1;
    }
   
    rc = isx006_probe_init_sensor(info);
    if (rc < 0)
        goto probe_fail_2;

    s->s_init = isx006_sensor_open_init;
    s->s_release = isx006_sensor_release;
    s->s_config  = isx006_sensor_config;
    s->s_camera_type = BACK_CAMERA_2D;
    s->s_mount_angle = info->sensor_platform_info->mount_angle;

    isx006_probe_init_done(info);
    
    printk("isx006_sensor_probe: X \n");
    return rc;

probe_fail_2:
    i2c_del_driver(&isx006_i2c_driver);
probe_fail_1:
    printk("isx006_sensor_probe: SENSOR PROBE FAILS!\n");
    return rc;
}

static int __devinit isx006_probe(struct platform_device *pdev)
{
    printk("isx006_probe: +++++++++++++++\n");
    pdev_isx006 = pdev;//Div2-SW6-MM-MC-EnhanceStabilityForMainCamera-00+
    
    return msm_camera_drv_start(pdev, isx006_sensor_probe);
}

static struct platform_driver msm_camera_driver = {
    .probe = isx006_probe,
    .driver = {
        .name = "msm_camera_isx006",
        .owner = THIS_MODULE,
    },
    .suspend = isx006_suspend,
    .resume = isx006_resume,    
};

static int __init isx006_init(void)
{
    return platform_driver_register(&msm_camera_driver);
}

module_init(isx006_init);
MODULE_DESCRIPTION("Samsung 5 MP Bayer sensor driver");
MODULE_LICENSE("GPL v2");
