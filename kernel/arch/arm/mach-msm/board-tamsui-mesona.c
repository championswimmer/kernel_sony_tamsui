/*
 * Copyright (C) 2011 FIH Co., Ltd.  All rights reserved.
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
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
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio_event.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/board.h>
#include <mach/msm_iomap.h>
#include <mach/msm_hsusb.h>
#include <mach/rpc_hsusb.h>
#include <mach/rpc_pmapp.h>
#include <mach/usbdiag.h>
#include <mach/msm_memtypes.h>
#include <mach/msm_serial_hs.h>
#include <linux/usb/android.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <mach/vreg.h>
#include <mach/pmic.h>
#include <mach/socinfo.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <asm/mach/mmc.h>
#include <linux/i2c.h>
#include <linux/i2c/sx150x.h>
#include <linux/gpio.h>
#include <linux/android_pmem.h>
#include <linux/bootmem.h>
#include <linux/mfd/marimba.h>
#include <mach/vreg.h>
#include <linux/power_supply.h>
#include <linux/regulator/consumer.h>
#include <mach/rpc_pmapp.h>

#include <mach/msm_battery.h>
#include <linux/smsc911x.h>
#include <linux/atmel_maxtouch.h>
#include "devices.h"
#include "timer.h"
#include "board-msm7x27a-regulator.h"
#include "devices-msm7x2xa.h"
#include "pm.h"
#include <linux/fih_power_key.h>
#include <mach/socinfo.h>
#include "pm-boot.h"
/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*[ */
#ifdef CONFIG_FIH_SW3_BATTERY
#include <linux/i2c/fih_bq27520.h>
#endif
/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*] */

#include <linux/fih_hw_info.h> //MTD-BSP-REXER-SMEM-00
extern void fih_info_init(void);

// MTD-BSP-Y.S-Enable drivers
#include <linux/gpio_keys.h>
#include <linux/fih_leds.h>
#include <linux/fih_vibrator.h>
// MTD-BSP-Y.S-Enable drivers

/* FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-00++{ */
#ifdef CONFIG_FIH_TOUCHSCREEN_CYTTSP_I2C_TMA340
#include <linux/cyttsp_i2c_tma340.h>
#endif 
/* FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-00++} */
/* FIH-SW1-PERIPHERAL-FG-MSENSOR-00+[ */
#ifdef CONFIG_FIH_MSENSOR_AKM8975
#include <linux/akm8975.h>
#endif
/* FIH-SW1-PERIPHERAL-FG-MSENSOR-00+] */
/* FIH-SW1-PERIPHERAL-FG-GSENSOR-00+[ */
#ifdef CONFIG_FIH_GSENSOR_BMA250
#include <linux/bma250.h>
#endif
/* FIH-SW1-PERIPHERAL-FG-GSENSOR-00+] */
/* FIH-SW1-PERIPHERAL-FG-PSENSOR-00+[ */
#ifdef CONFIG_FIH_PSENSOR_QPDSS702
#include <linux/qpdss702.h>
#endif
/* FIH-SW1-PERIPHERAL-FG-PSENSOR-00+] */
#define PMEM_KERNEL_EBI1_SIZE	0x3A000
#define MSM_PMEM_AUDIO_SIZE	0x5B000
#define BAHAMA_SLAVE_ID_FM_ADDR         0x2A
#define BAHAMA_SLAVE_ID_QMEMBIST_ADDR   0x7B
#define BAHAMA_SLAVE_ID_FM_REG 0x02
#define FM_GPIO	83

/* FIH-SW3-KERNEL-TH-write_panic_2_file-01+[ */ 
#include <linux/fih_sw_info.h>
/* FIH-SW3-KERNEL-TH-write_panic_2_file-01+] */

#include <mach/fih_headset.h> /* FIH-SW2-MM-AY-MES_headset_00 */

enum {
	GPIO_EXPANDER_IRQ_BASE	= NR_MSM_IRQS + NR_GPIO_IRQS,
	GPIO_EXPANDER_GPIO_BASE	= NR_MSM_GPIOS,
	/* SURF expander */
	GPIO_CORE_EXPANDER_BASE	= GPIO_EXPANDER_GPIO_BASE,
	GPIO_BT_SYS_REST_EN	= GPIO_CORE_EXPANDER_BASE,
	GPIO_WLAN_EXT_POR_N,
	GPIO_DISPLAY_PWR_EN,
	GPIO_BACKLIGHT_EN,
	GPIO_PRESSURE_XCLR,
	GPIO_VREG_S3_EXP,
	GPIO_UBM2M_PWRDWN,
	GPIO_ETM_MODE_CS_N,
	GPIO_HOST_VBUS_EN,
	GPIO_SPI_MOSI,
	GPIO_SPI_MISO,
	GPIO_SPI_CLK,
	GPIO_SPI_CS0_N,
	GPIO_CORE_EXPANDER_IO13,
	GPIO_CORE_EXPANDER_IO14,
	GPIO_CORE_EXPANDER_IO15,
	/* Camera expander */
	GPIO_CAM_EXPANDER_BASE	= GPIO_CORE_EXPANDER_BASE + 16,
	GPIO_CAM_GP_STROBE_READY	= GPIO_CAM_EXPANDER_BASE,
	GPIO_CAM_GP_AFBUSY,
	GPIO_CAM_GP_CAM_PWDN,
	GPIO_CAM_GP_CAM1MP_XCLR,
	GPIO_CAM_GP_CAMIF_RESET_N,
	GPIO_CAM_GP_STROBE_CE,
	GPIO_CAM_GP_LED_EN1,
	GPIO_CAM_GP_LED_EN2,
};

#if defined(CONFIG_GPIO_SX150X)
enum {
	SX150X_CORE,
	SX150X_CAM,
};

static struct sx150x_platform_data sx150x_data[] __initdata = {
	[SX150X_CORE]	= {
		.gpio_base		= GPIO_CORE_EXPANDER_BASE,
		.oscio_is_gpo		= false,
		.io_pullup_ena		= 0,
		.io_pulldn_ena		= 0x02,
		.io_open_drain_ena	= 0xfef8,
		.irq_summary		= -1,
	},
	[SX150X_CAM]	= {
		.gpio_base		= GPIO_CAM_EXPANDER_BASE,
		.oscio_is_gpo		= false,
		.io_pullup_ena		= 0,
		.io_pulldn_ena		= 0,
		.io_open_drain_ena	= 0x23,
		.irq_summary		= -1,
	},
};
#endif

//MTD-CONN-CD-MES_WIFI_PORTING-00+[
#define GPIO_WL_REG_ON     82
#define  WL_HOST_WAKE         83
#define  WL_HOST_WAKE_FIX  112       

int wifi_power(int on)
{
    printk(KERN_DEBUG "%s: POWER %s\n", __FUNCTION__, on?"ON":"OFF");

    if (on) {
        gpio_set_value(GPIO_WL_REG_ON, 0);
        mdelay(20);
        gpio_set_value(GPIO_WL_REG_ON, 1);
        mdelay(20);

    } else {
        //bcm4330_power_status = 0;
        gpio_set_value(GPIO_WL_REG_ON, 0);
        mdelay(20);

    }
    printk(KERN_DEBUG "%s: GPIO_WL_REG_ON (%s)\n", __FUNCTION__, gpio_get_value(GPIO_WL_REG_ON)?"HIGH":"LOW");

    return 0;
}
EXPORT_SYMBOL(wifi_power);

int bcm4330_wifi_resume(void)
{
        gpio_set_value(GPIO_WL_REG_ON, 1);
        mdelay(20);
        printk(KERN_DEBUG "%s: PULL UP GPIO_WL_REG_ON\r\n", __func__);

        return 0;
}
EXPORT_SYMBOL(bcm4330_wifi_resume);

int bcm4330_wifi_suspend(void)
{
        printk(KERN_DEBUG "%s: PULL DOWN GPIO_WL_REG_ON\r\n", __func__);
        gpio_set_value(GPIO_WL_REG_ON, 0);
        mdelay(20);

        return 0;
}
EXPORT_SYMBOL(bcm4330_wifi_suspend);
//MTD-CONN-CD-MES_WIFI_PORTING-00+]

#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)

	/* FM Platform power and shutdown routines */
#define FPGA_MSM_CNTRL_REG2 0x90008010

static void config_pcm_i2s_mode(int mode)
{
	void __iomem *cfg_ptr;
	u8 reg2;

	cfg_ptr = ioremap_nocache(FPGA_MSM_CNTRL_REG2, sizeof(char));

	if (!cfg_ptr)
		return;
	if (mode) {
		/*enable the pcm mode in FPGA*/
		reg2 = readb_relaxed(cfg_ptr);
		if (reg2 == 0) {
			reg2 = 1;
			writeb_relaxed(reg2, cfg_ptr);
		}
	} else {
		/*enable i2s mode in FPGA*/
		reg2 = readb_relaxed(cfg_ptr);
		if (reg2 == 1) {
			reg2 = 0;
			writeb_relaxed(reg2, cfg_ptr);
		}
	}
	iounmap(cfg_ptr);
}

static unsigned fm_i2s_config_power_on[] = {
	/*FM_I2S_SD*/
	GPIO_CFG(68, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*FM_I2S_WS*/
	GPIO_CFG(70, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*FM_I2S_SCK*/
	GPIO_CFG(71, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
};

static unsigned fm_i2s_config_power_off[] = {
	/*FM_I2S_SD*/
	GPIO_CFG(68, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*FM_I2S_WS*/
	GPIO_CFG(70, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*FM_I2S_SCK*/
	GPIO_CFG(71, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
};

static unsigned bt_config_power_on[] = {
	/*RFR*/
	GPIO_CFG(43, 2, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*CTS*/
	GPIO_CFG(44, 2, GPIO_CFG_INPUT,  GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*RX*/
	GPIO_CFG(45, 2, GPIO_CFG_INPUT,  GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*TX*/
	GPIO_CFG(46, 2, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
};
static unsigned bt_config_pcm_on[] = {
	/*PCM_DOUT*/
	GPIO_CFG(68, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*PCM_DIN*/
	GPIO_CFG(69, 1, GPIO_CFG_INPUT,  GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*PCM_SYNC*/
	GPIO_CFG(70, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*PCM_CLK*/
	GPIO_CFG(71, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
};
static unsigned bt_config_power_off[] = {
	/*RFR*/
	GPIO_CFG(43, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*CTS*/
	GPIO_CFG(44, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*RX*/
	GPIO_CFG(45, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*TX*/
	GPIO_CFG(46, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
};
static unsigned bt_config_pcm_off[] = {
	/*PCM_DOUT*/
	GPIO_CFG(68, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*PCM_DIN*/
	GPIO_CFG(69, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*PCM_SYNC*/
	GPIO_CFG(70, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	/*PCM_CLK*/
	GPIO_CFG(71, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
};

static int config_i2s(int mode)
{
	int pin, rc = 0;

	if (mode == FM_I2S_ON) {
		if (machine_is_msm7x27a_surf() || machine_is_msm7625a_surf())
			config_pcm_i2s_mode(0);
		pr_err("%s mode = FM_I2S_ON", __func__);
		for (pin = 0; pin < ARRAY_SIZE(fm_i2s_config_power_on);
			pin++) {
				rc = gpio_tlmm_config(
					fm_i2s_config_power_on[pin],
					GPIO_CFG_ENABLE
					);
				if (rc < 0)
					return rc;
			}
	} else if (mode == FM_I2S_OFF) {
		pr_err("%s mode = FM_I2S_OFF", __func__);
		for (pin = 0; pin < ARRAY_SIZE(fm_i2s_config_power_off);
			pin++) {
				rc = gpio_tlmm_config(
					fm_i2s_config_power_off[pin],
					GPIO_CFG_ENABLE
					);
				if (rc < 0)
					return rc;
			}
	}
	return rc;
}
static int config_pcm(int mode)
{
	int pin, rc = 0;

	if (mode == BT_PCM_ON) {
		if (machine_is_msm7x27a_surf() || machine_is_msm7625a_surf())
			config_pcm_i2s_mode(1);
		pr_err("%s mode =BT_PCM_ON", __func__);
		for (pin = 0; pin < ARRAY_SIZE(bt_config_pcm_on);
			pin++) {
				rc = gpio_tlmm_config(bt_config_pcm_on[pin],
					GPIO_CFG_ENABLE);
				if (rc < 0)
					return rc;
			}
	} else if (mode == BT_PCM_OFF) {
		pr_err("%s mode =BT_PCM_OFF", __func__);
		for (pin = 0; pin < ARRAY_SIZE(bt_config_pcm_off);
			pin++) {
				rc = gpio_tlmm_config(bt_config_pcm_off[pin],
					GPIO_CFG_ENABLE);
				if (rc < 0)
					return rc;
			}

	}

	return rc;
}

static int msm_bahama_setup_pcm_i2s(int mode)
{
	int fm_state = 0, bt_state = 0;
	int rc = 0;
	struct marimba config = { .mod_id =  SLAVE_ID_BAHAMA};

	fm_state = marimba_get_fm_status(&config);
	bt_state = marimba_get_bt_status(&config);

	switch (mode) {
	case BT_PCM_ON:
	case BT_PCM_OFF:
		if (!fm_state)
			rc = config_pcm(mode);
		break;
	case FM_I2S_ON:
		rc = config_i2s(mode);
		break;
	case FM_I2S_OFF:
		if (bt_state)
			rc = config_pcm(BT_PCM_ON);
		else
			rc = config_i2s(mode);
		break;
	default:
		rc = -EIO;
		pr_err("%s:Unsupported mode", __func__);
	}
	return rc;
}

static int bt_set_gpio(int on)
{
	int rc = 0;
	struct marimba config = { .mod_id =  SLAVE_ID_BAHAMA};

	if (on) {
		rc = gpio_direction_output(GPIO_BT_SYS_REST_EN, 1);
		msleep(100);
	} else {
		if (!marimba_get_fm_status(&config) &&
				!marimba_get_bt_status(&config)) {
			gpio_set_value_cansleep(GPIO_BT_SYS_REST_EN, 0);
			rc = gpio_direction_input(GPIO_BT_SYS_REST_EN);
			msleep(100);
		}
	}
	if (rc)
		pr_err("%s: BT sys_reset_en GPIO : Error", __func__);

	return rc;
}
static struct regulator *fm_regulator;
static int fm_radio_setup(struct marimba_fm_platform_data *pdata)
{
	int rc = 0;
	const char *id = "FMPW";
	uint32_t irqcfg;
	struct marimba config = { .mod_id =  SLAVE_ID_BAHAMA};
	u8 value;

	/* Voting for 1.8V Regulator */
	fm_regulator = regulator_get(NULL, "msme1");
	if (IS_ERR(fm_regulator)) {
		rc = PTR_ERR(fm_regulator);
		pr_err("%s: could not get regulator: %d\n", __func__, rc);
		goto out;
	}

	/* Set the voltage level to 1.8V */
	rc = regulator_set_voltage(fm_regulator, 1800000, 1800000);
	if (rc < 0) {
		pr_err("%s: could not set voltage: %d\n", __func__, rc);
		goto reg_free;
	}

	/* Enabling the 1.8V regulator */
	rc = regulator_enable(fm_regulator);
	if (rc) {
		pr_err("%s: could not enable regulator: %d\n", __func__, rc);
		goto reg_free;
	}

	/* Voting for 19.2MHz clock */
	rc = pmapp_clock_vote(id, PMAPP_CLOCK_ID_D1,
			PMAPP_CLOCK_VOTE_ON);
	if (rc < 0) {
		pr_err("%s: clock vote failed with :(%d)\n",
			 __func__, rc);
		goto reg_disable;
	}

	rc = bt_set_gpio(1);
	if (rc) {
		pr_err("%s: bt_set_gpio = %d", __func__, rc);
		goto gpio_deconfig;
	}
	/*re-write FM Slave Id, after reset*/
	value = BAHAMA_SLAVE_ID_FM_ADDR;
	rc = marimba_write_bit_mask(&config,
			BAHAMA_SLAVE_ID_FM_REG, &value, 1, 0xFF);
	if (rc < 0) {
		pr_err("%s: FM Slave ID rewrite Failed = %d", __func__, rc);
		goto gpio_deconfig;
	}
	/* Configuring the FM GPIO */
	irqcfg = GPIO_CFG(FM_GPIO, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
			GPIO_CFG_2MA);

	rc = gpio_tlmm_config(irqcfg, GPIO_CFG_ENABLE);
	if (rc) {
		pr_err("%s: gpio_tlmm_config(%#x)=%d\n",
			 __func__, irqcfg, rc);
		goto gpio_deconfig;
	}

	return 0;

gpio_deconfig:
	pmapp_clock_vote(id, PMAPP_CLOCK_ID_D1,
		PMAPP_CLOCK_VOTE_OFF);
	bt_set_gpio(0);
reg_disable:
	regulator_disable(fm_regulator);
reg_free:
	regulator_put(fm_regulator);
	fm_regulator = NULL;
out:
	return rc;
};

static void fm_radio_shutdown(struct marimba_fm_platform_data *pdata)
{
	int rc;
	const char *id = "FMPW";

	/* Releasing the GPIO line used by FM */
	uint32_t irqcfg = GPIO_CFG(FM_GPIO, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
		GPIO_CFG_2MA);

	rc = gpio_tlmm_config(irqcfg, GPIO_CFG_ENABLE);
	if (rc)
		pr_err("%s: gpio_tlmm_config(%#x)=%d\n",
			 __func__, irqcfg, rc);

	/* Releasing the 1.8V Regulator */
	if (!IS_ERR_OR_NULL(fm_regulator)) {
		rc = regulator_disable(fm_regulator);
		if (rc)
			pr_err("%s: could not disable regulator: %d\n",
					__func__, rc);
		regulator_put(fm_regulator);
		fm_regulator = NULL;
	}

	/* Voting off the clock */
	rc = pmapp_clock_vote(id, PMAPP_CLOCK_ID_D1,
		PMAPP_CLOCK_VOTE_OFF);
	if (rc < 0)
		pr_err("%s: voting off failed with :(%d)\n",
			__func__, rc);
	rc = bt_set_gpio(0);
	if (rc)
		pr_err("%s: bt_set_gpio = %d", __func__, rc);
}

static struct marimba_fm_platform_data marimba_fm_pdata = {
	.fm_setup = fm_radio_setup,
	.fm_shutdown = fm_radio_shutdown,
	.irq = MSM_GPIO_TO_INT(FM_GPIO),
	.vreg_s2 = NULL,
	.vreg_xo_out = NULL,
	/* Configuring the FM SoC as I2S Master */
	.is_fm_soc_i2s_master = true,
	.config_i2s_gpio = msm_bahama_setup_pcm_i2s,
};

#endif //defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
//MTD-Conn-DL-ICS2010_Porting-00+[

#if defined(CONFIG_BROADCOM_BCM4330_BTFM)
#define GPIO_BT_REG_ON     31
#define GPIO_BT_RST_N      32

#define BT_HOST_WAKE       33
#define HOST_WAKEUP_BT     114

#define GPIO_BTUART_RFR    43
#define GPIO_BTUART_CTS    44
#define GPIO_BTUART_RX     45
#define GPIO_BTUART_TX     46
#define GPIO_PCM_DIN       69
#define GPIO_PCM_DOUT      68
#define GPIO_PCM_SYNC      70
#define GPIO_PCM_BCLK      71

static struct platform_device bcm4330_bt_power_device = {
    .name = "bcm4330_bt_power",
    .id     = -1
};

static struct msm_gpio bt_config_power_on[] = {
    { GPIO_CFG(GPIO_BTUART_RFR, 2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN,  GPIO_CFG_2MA), "UART1DM_RFR" },
    { GPIO_CFG(GPIO_BTUART_CTS, 2, GPIO_CFG_INPUT,  GPIO_CFG_NO_PULL,  GPIO_CFG_2MA), "UART1DM_CTS" },
    { GPIO_CFG(GPIO_BTUART_RX,  2, GPIO_CFG_INPUT,  GPIO_CFG_NO_PULL,  GPIO_CFG_2MA), "UART1DM_RX" },
    { GPIO_CFG(GPIO_BTUART_TX,  2, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL,  GPIO_CFG_2MA), "UART1DM_TX" }
};

static struct msm_gpio bt_config_power_off[] = {
 
    { GPIO_CFG(GPIO_BTUART_RFR, 0, GPIO_CFG_INPUT,  GPIO_CFG_PULL_DOWN,  GPIO_CFG_2MA), "UART1DM_RFR" },
    { GPIO_CFG(GPIO_BTUART_CTS, 0, GPIO_CFG_INPUT,  GPIO_CFG_PULL_DOWN,  GPIO_CFG_2MA), "UART1DM_CTS" },
    { GPIO_CFG(GPIO_BTUART_RX,  0, GPIO_CFG_INPUT,  GPIO_CFG_PULL_DOWN,  GPIO_CFG_2MA), "UART1DM_RX" },
    { GPIO_CFG(GPIO_BTUART_TX,  0, GPIO_CFG_INPUT,  GPIO_CFG_PULL_DOWN,  GPIO_CFG_2MA), "UART1DM_TX" }
};
static int bluetooth_power(int on)
{
    int rc;

    printk("KERN_DEBUG %s: POWER %s\n", __FUNCTION__, on?"ON":"OFF");

    if (on)
    {
        rc = msm_gpios_enable(bt_config_power_on, ARRAY_SIZE(bt_config_power_on));
        if (rc < 0)
        {
            printk(KERN_DEBUG "%s: Power ON bluetooth failed.\n", __FUNCTION__);
            return rc;
        }

        mdelay(20);
        gpio_set_value(GPIO_BT_RST_N, 0);
        mdelay(20);
        gpio_set_value(GPIO_BT_RST_N, 1);     
        mdelay(20);

        gpio_set_value(BT_HOST_WAKE, 1);
        mdelay(20);

        gpio_set_value(GPIO_BT_REG_ON, 1);
        mdelay(100);       

        printk(KERN_DEBUG "%s: GPIO_BT_RST (%s)\n", __FUNCTION__, gpio_get_value(GPIO_BT_RST_N)?"HIGH":"LOW");
        printk(KERN_DEBUG "%s: GPIO_BT_REG_ON (%s)\n", __FUNCTION__, gpio_get_value(GPIO_BT_REG_ON)?"HIGH":"LOW");
        printk(KERN_DEBUG "%s: BT_HOST_WAKE !(%s)\n", __FUNCTION__, gpio_get_value(BT_HOST_WAKE)?"HIGH":"LOW");
    }
    else
    {
        rc = msm_gpios_enable(bt_config_power_off, ARRAY_SIZE(bt_config_power_off));
        if (rc < 0)
        {
            printk(KERN_DEBUG "%s: Power OFF bluetooth failed.\n", __FUNCTION__);
            return rc;
        }

        mdelay(20);
        gpio_set_value(BT_HOST_WAKE, 0);
        mdelay(20);
        gpio_set_value(GPIO_BT_RST_N, 0);
        mdelay(20);
        gpio_set_value(GPIO_BT_REG_ON, 0);
        mdelay(100);

        printk(KERN_DEBUG "%s: GPIO_BT_RST (%s)\n", __FUNCTION__, gpio_get_value(GPIO_BT_RST_N)?"HIGH":"LOW");
        printk(KERN_DEBUG "%s: GPIO_BT_REG_ON (%s)\n", __FUNCTION__, gpio_get_value(GPIO_BT_REG_ON)?"HIGH":"LOW");
        printk(KERN_DEBUG "%s: BT_HOST_WAKE !(%s)\n", __FUNCTION__, gpio_get_value(BT_HOST_WAKE)?"HIGH":"LOW");
    }

    return 0;
}

static void __init bcm4330_bt_power_init(void)
{
    gpio_set_value(GPIO_BT_REG_ON, 0);
    gpio_set_value(GPIO_BT_RST_N, 0);

    bcm4330_bt_power_device.dev.platform_data = &bluetooth_power;
}
//MTD-Conn-JC-BT_FTM-00+]
#endif
#if defined(CONFIG_BROADCOM_BCM4330_BTFM) && defined(CONFIG_BROADCOM_BCM4330_BTFM_SLEEP)
//MTD-Conn-JC-BTSleep-00+[
static struct resource bluesleep_resources[] = {
    {
        .name = "gpio_host_wake",
        .start = HOST_WAKEUP_BT,
        .end = HOST_WAKEUP_BT,
        .flags = IORESOURCE_IO,
    },
    {
        .name = "gpio_ext_wake",
        .start = BT_HOST_WAKE,
        .end = BT_HOST_WAKE,
        .flags = IORESOURCE_IO,
    },
    {
        .name = "host_wake",
        .start = MSM_GPIO_TO_INT(HOST_WAKEUP_BT),
        .end = MSM_GPIO_TO_INT(HOST_WAKEUP_BT),
        .flags = IORESOURCE_IO,
    },
};

static struct platform_device bluesleep_device = {
    .name = "bluesleep",
    .id = -1,
    .num_resources = ARRAY_SIZE(bluesleep_resources),
    .resource = bluesleep_resources,
};
//MTD-Conn-JC-BTSleep-00+]
#endif //defined(CONFIG_BROADCOM_BCM4330_BTFM) && defined(CONFIG_BROADCOM_BCM4330_BTFM_SLEEP)

#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)

static struct platform_device msm_wlan_ar6000_pm_device = {
	.name           = "wlan_ar6000_pm_dev",
	.id             = -1,
};
#endif

/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*[ */
#ifdef CONFIG_FIH_SW3_BATTERY
static struct bq27520_platform_data bq27520_pdata = {
	.name		= "fuel-gauge",
	.vreg_name	= "8058_s3",
	.vreg_value	= 1800000,
	.soc_int	= 36,
	//.bi_tout	= GPIO_CAP_GAUGE_BI_TOUT,
	//.chip_en	= GPIO_BATT_GAUGE_EN,
	.enable_dlog	= 0, /* if enable coulomb counter logger */
	.bat_low    = 27,
	.ovp_flag   = 123,
};

static struct i2c_board_info msm_bq27520_board_info[] = {
    {
        I2C_BOARD_INFO("bq27520", 0xAA >> 1),
        .platform_data = &bq27520_pdata,
    },
#ifdef CONFIG_FIH_SW3_BQ275X0_ROMMODE
    {
        I2C_BOARD_INFO("bq275x0-RomMode", 0x16 >> 1),        
    },
#endif
};
#endif
/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*] */

#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
static struct platform_device msm_bt_power_device = {
	.name = "bt_power",
};
struct bahama_config_register {
		u8 reg;
		u8 value;
		u8 mask;
};
struct bt_vreg_info {
	const char *name;
	unsigned int pmapp_id;
	unsigned int min_level;
	unsigned int max_level;
	unsigned int is_pin_controlled;
	struct regulator *reg;
};
static struct bt_vreg_info bt_vregs[] = {
	{"msme1", 2, 1800000, 1800000, 0, NULL},
	{"bt", 21, 2900000, 3050000, 1, NULL}
};

static int bahama_bt(int on)
{
	int rc = 0;
	int i;

	struct marimba config = { .mod_id =  SLAVE_ID_BAHAMA};

	struct bahama_variant_register {
		const size_t size;
		const struct bahama_config_register *set;
	};

	const struct bahama_config_register *p;

	u8 version;

	const struct bahama_config_register v10_bt_on[] = {
		{ 0xE9, 0x00, 0xFF },
		{ 0xF4, 0x80, 0xFF },
		{ 0xE4, 0x00, 0xFF },
		{ 0xE5, 0x00, 0x0F },
#ifdef CONFIG_WLAN
		{ 0xE6, 0x38, 0x7F },
		{ 0xE7, 0x06, 0xFF },
#endif
		{ 0xE9, 0x21, 0xFF },
		{ 0x01, 0x0C, 0x1F },
		{ 0x01, 0x08, 0x1F },
	};

	const struct bahama_config_register v20_bt_on_fm_off[] = {
		{ 0x11, 0x0C, 0xFF },
		{ 0x13, 0x01, 0xFF },
		{ 0xF4, 0x80, 0xFF },
		{ 0xF0, 0x00, 0xFF },
		{ 0xE9, 0x00, 0xFF },
#ifdef CONFIG_WLAN
		{ 0x81, 0x00, 0x7F },
		{ 0x82, 0x00, 0xFF },
		{ 0xE6, 0x38, 0x7F },
		{ 0xE7, 0x06, 0xFF },
#endif
		{ 0x8E, 0x15, 0xFF },
		{ 0x8F, 0x15, 0xFF },
		{ 0x90, 0x15, 0xFF },

		{ 0xE9, 0x21, 0xFF },
	};

	const struct bahama_config_register v20_bt_on_fm_on[] = {
		{ 0x11, 0x0C, 0xFF },
		{ 0x13, 0x01, 0xFF },
		{ 0xF4, 0x86, 0xFF },
		{ 0xF0, 0x06, 0xFF },
		{ 0xE9, 0x00, 0xFF },
#ifdef CONFIG_WLAN
		{ 0x81, 0x00, 0x7F },
		{ 0x82, 0x00, 0xFF },
		{ 0xE6, 0x38, 0x7F },
		{ 0xE7, 0x06, 0xFF },
#endif
		{ 0xE9, 0x21, 0xFF },
	};

	const struct bahama_config_register v10_bt_off[] = {
		{ 0xE9, 0x00, 0xFF },
	};

	const struct bahama_config_register v20_bt_off_fm_off[] = {
		{ 0xF4, 0x84, 0xFF },
		{ 0xF0, 0x04, 0xFF },
		{ 0xE9, 0x00, 0xFF }
	};

	const struct bahama_config_register v20_bt_off_fm_on[] = {
		{ 0xF4, 0x86, 0xFF },
		{ 0xF0, 0x06, 0xFF },
		{ 0xE9, 0x00, 0xFF }
	};
	const struct bahama_variant_register bt_bahama[2][3] = {
	{
		{ ARRAY_SIZE(v10_bt_off), v10_bt_off },
		{ ARRAY_SIZE(v20_bt_off_fm_off), v20_bt_off_fm_off },
		{ ARRAY_SIZE(v20_bt_off_fm_on), v20_bt_off_fm_on }
	},
	{
		{ ARRAY_SIZE(v10_bt_on), v10_bt_on },
		{ ARRAY_SIZE(v20_bt_on_fm_off), v20_bt_on_fm_off },
		{ ARRAY_SIZE(v20_bt_on_fm_on), v20_bt_on_fm_on }
	}
	};

	u8 offset = 0; /* index into bahama configs */
	on = on ? 1 : 0;
	version = marimba_read_bahama_ver(&config);
	if ((int)version < 0 || version == BAHAMA_VER_UNSUPPORTED) {
		dev_err(&msm_bt_power_device.dev, "%s: Bahama \
				version read Error, version = %d \n",
				__func__, version);
		return -EIO;
	}

	if (version == BAHAMA_VER_2_0) {
		if (marimba_get_fm_status(&config))
			offset = 0x01;
	}

	p = bt_bahama[on][version + offset].set;

	dev_info(&msm_bt_power_device.dev,
		"%s: found version %d\n", __func__, version);

	for (i = 0; i < bt_bahama[on][version + offset].size; i++) {
		u8 value = (p+i)->value;
		rc = marimba_write_bit_mask(&config,
			(p+i)->reg,
			&value,
			sizeof((p+i)->value),
			(p+i)->mask);
		if (rc < 0) {
			dev_err(&msm_bt_power_device.dev,
				"%s: reg %x write failed: %d\n",
				__func__, (p+i)->reg, rc);
			return rc;
		}
		dev_dbg(&msm_bt_power_device.dev,
			"%s: reg 0x%02x write value 0x%02x mask 0x%02x\n",
				__func__, (p+i)->reg,
				value, (p+i)->mask);
		value = 0;
		rc = marimba_read_bit_mask(&config,
				(p+i)->reg, &value,
				sizeof((p+i)->value), (p+i)->mask);
		if (rc < 0)
			dev_err(&msm_bt_power_device.dev, "%s marimba_read_bit_mask- error",
					__func__);
		dev_dbg(&msm_bt_power_device.dev,
			"%s: reg 0x%02x read value 0x%02x mask 0x%02x\n",
				__func__, (p+i)->reg,
				value, (p+i)->mask);
	}
	/* Update BT Status */
	if (on)
		marimba_set_bt_status(&config, true);
	else
		marimba_set_bt_status(&config, false);
	return rc;
}
static int bluetooth_switch_regulators(int on)
{
	int i, rc = 0;
	const char *id = "BTPW";

	for (i = 0; i < ARRAY_SIZE(bt_vregs); i++) {
		if (IS_ERR_OR_NULL(bt_vregs[i].reg)) {
			rc = bt_vregs[i].reg ?
				PTR_ERR(bt_vregs[i].reg) :
				-ENODEV;
			dev_err(&msm_bt_power_device.dev,
				"%s: invalid regulator handle for %s: %d\n",
					__func__, bt_vregs[i].name, rc);
			goto reg_disable;
		}

		rc = on ? regulator_set_voltage(bt_vregs[i].reg,
				bt_vregs[i].min_level,
					bt_vregs[i].max_level) : 0;
		if (rc) {
			dev_err(&msm_bt_power_device.dev,
				"%s: could not set voltage for %s: %d\n",
					__func__, bt_vregs[i].name, rc);
			goto reg_disable;
		}

		rc = on ? regulator_enable(bt_vregs[i].reg) : 0;
		if (rc) {
			dev_err(&msm_bt_power_device.dev,
				"%s: could not %sable regulator %s: %d\n",
					__func__, "en", bt_vregs[i].name, rc);
			goto reg_disable;
		}

		if (bt_vregs[i].is_pin_controlled) {
			rc = pmapp_vreg_lpm_pincntrl_vote(id,
					bt_vregs[i].pmapp_id,
					PMAPP_CLOCK_ID_D1,
					on ? PMAPP_CLOCK_VOTE_ON :
						PMAPP_CLOCK_VOTE_OFF);
			if (rc) {
				dev_err(&msm_bt_power_device.dev,
					"%s: pin control failed for %s: %d\n",
					__func__, bt_vregs[i].name, rc);
				goto pin_cnt_fail;
			}
		}
		rc = on ? 0 : regulator_disable(bt_vregs[i].reg);

		if (rc) {
			dev_err(&msm_bt_power_device.dev,
				"%s: could not %sable regulator %s: %d\n",
				__func__, "dis", bt_vregs[i].name, rc);
			goto reg_disable;
		}
	}

	return rc;
pin_cnt_fail:
	if (on)
		regulator_disable(bt_vregs[i].reg);
reg_disable:
	while (i) {
		if (on) {
			i--;
			regulator_disable(bt_vregs[i].reg);
			regulator_put(bt_vregs[i].reg);
		}
	}
	return rc;
}

static struct regulator *reg_s3;
static unsigned int msm_bahama_setup_power(void)
{
	int rc = 0;

	reg_s3 = regulator_get(NULL, "msme1");
	if (IS_ERR(reg_s3)) {
		rc = PTR_ERR(reg_s3);
		pr_err("%s: could not get regulator: %d\n", __func__, rc);
		goto out;
	}

	rc = regulator_set_voltage(reg_s3, 1800000, 1800000);
	if (rc) {
		pr_err("%s: could not set voltage: %d\n", __func__, rc);
		goto reg_fail;
	}

	rc = regulator_enable(reg_s3);
	if (rc < 0) {
		pr_err("%s: could not enable regulator: %d\n", __func__, rc);
		goto reg_fail;
	}

	/*setup Bahama_sys_reset_n*/
	rc = gpio_request(GPIO_BT_SYS_REST_EN, "bahama sys_rst_n");
	if (rc) {
		pr_err("%s: gpio_request %d = %d\n", __func__,
			GPIO_BT_SYS_REST_EN, rc);
		goto reg_disable;
	}

	rc = bt_set_gpio(1);
	if (rc) {
		pr_err("%s: bt_set_gpio %d = %d\n", __func__,
			GPIO_BT_SYS_REST_EN, rc);
		goto gpio_fail;
	}

	return rc;

gpio_fail:
	gpio_free(GPIO_BT_SYS_REST_EN);
reg_disable:
	regulator_disable(reg_s3);
reg_fail:
	regulator_put(reg_s3);
out:
	reg_s3 = NULL;
	return rc;
}

static unsigned int msm_bahama_shutdown_power(int value)
{
	int rc = 0;

	if (IS_ERR_OR_NULL(reg_s3)) {
		rc = reg_s3 ? PTR_ERR(reg_s3) : -ENODEV;
		goto out;
	}

	rc = regulator_disable(reg_s3);
	if (rc) {
		pr_err("%s: could not disable regulator: %d\n", __func__, rc);
		goto out;
	}

	if (value == BAHAMA_ID) {
		rc = bt_set_gpio(0);
		if (rc) {
			pr_err("%s: bt_set_gpio = %d\n",
					__func__, rc);
		}
		gpio_free(GPIO_BT_SYS_REST_EN);
	}

	regulator_put(reg_s3);
	reg_s3 = NULL;

	return 0;

out:
	return rc;
}

static unsigned int msm_bahama_core_config(int type)
{
	int rc = 0;

	if (type == BAHAMA_ID) {
		int i;
		struct marimba config = { .mod_id =  SLAVE_ID_BAHAMA};
		const struct bahama_config_register v20_init[] = {
			/* reg, value, mask */
			{ 0xF4, 0x84, 0xFF }, /* AREG */
			{ 0xF0, 0x04, 0xFF } /* DREG */
		};
		if (marimba_read_bahama_ver(&config) == BAHAMA_VER_2_0) {
			for (i = 0; i < ARRAY_SIZE(v20_init); i++) {
				u8 value = v20_init[i].value;
				rc = marimba_write_bit_mask(&config,
					v20_init[i].reg,
					&value,
					sizeof(v20_init[i].value),
					v20_init[i].mask);
				if (rc < 0) {
					pr_err("%s: reg %d write failed: %d\n",
						__func__, v20_init[i].reg, rc);
					return rc;
				}
				pr_debug("%s: reg 0x%02x value 0x%02x"
					" mask 0x%02x\n",
					__func__, v20_init[i].reg,
					v20_init[i].value, v20_init[i].mask);
			}
		}
	}
	rc = bt_set_gpio(0);
	if (rc) {
		pr_err("%s: bt_set_gpio = %d\n",
		       __func__, rc);
	}
	pr_debug("core type: %d\n", type);
	return rc;
}

static int bluetooth_power(int on)
{
	int pin, rc = 0;
	const char *id = "BTPW";
	int cid = 0;

	cid = adie_get_detected_connectivity_type();
	if (cid != BAHAMA_ID) {
		pr_err("%s: unexpected adie connectivity type: %d\n",
					__func__, cid);
		return -ENODEV;
	}
	if (on) {
		/*setup power for BT SOC*/
		rc = bt_set_gpio(on);
		if (rc) {
			pr_err("%s: bt_set_gpio = %d\n",
					__func__, rc);
			goto exit;
		}
		rc = bluetooth_switch_regulators(on);
		if (rc < 0) {
			pr_err("%s: bluetooth_switch_regulators rc = %d",
					__func__, rc);
			goto exit;
		}
		/*setup BT GPIO lines*/
		for (pin = 0; pin < ARRAY_SIZE(bt_config_power_on);
			pin++) {
			rc = gpio_tlmm_config(bt_config_power_on[pin],
					GPIO_CFG_ENABLE);
			if (rc < 0) {
				pr_err("%s: gpio_tlmm_config(%#x)=%d\n",
						__func__,
						bt_config_power_on[pin],
						rc);
				goto fail_power;
			}
		}
		/*Setup BT clocks*/
		rc = pmapp_clock_vote(id, PMAPP_CLOCK_ID_D1,
			PMAPP_CLOCK_VOTE_ON);
		if (rc < 0) {
			pr_err("Failed to vote for TCXO_D1 ON\n");
			goto fail_clock;
		}
		msleep(20);

		/*I2C config for Bahama*/
		rc = bahama_bt(1);
		if (rc < 0) {
			pr_err("%s: bahama_bt rc = %d", __func__, rc);
			goto fail_i2c;
		}
		msleep(20);

		/*setup BT PCM lines*/
		rc = msm_bahama_setup_pcm_i2s(BT_PCM_ON);
		if (rc < 0) {
			pr_err("%s: msm_bahama_setup_pcm_i2s , rc =%d\n",
				__func__, rc);
				goto fail_power;
			}
		rc = pmapp_clock_vote(id, PMAPP_CLOCK_ID_D1,
				  PMAPP_CLOCK_VOTE_PIN_CTRL);
		if (rc < 0)
			pr_err("%s:Pin Control Failed, rc = %d",
					__func__, rc);

	} else {
		rc = bahama_bt(0);
		if (rc < 0)
			pr_err("%s: bahama_bt rc = %d", __func__, rc);

		rc = bt_set_gpio(on);
		if (rc) {
			pr_err("%s: bt_set_gpio = %d\n",
					__func__, rc);
		}
fail_i2c:
		rc = pmapp_clock_vote(id, PMAPP_CLOCK_ID_D1,
				  PMAPP_CLOCK_VOTE_OFF);
		if (rc < 0)
			pr_err("%s: Failed to vote Off D1\n", __func__);
fail_clock:
		for (pin = 0; pin < ARRAY_SIZE(bt_config_power_off);
			pin++) {
				rc = gpio_tlmm_config(bt_config_power_off[pin],
					GPIO_CFG_ENABLE);
				if (rc < 0) {
					pr_err("%s: gpio_tlmm_config(%#x)=%d\n",
					__func__, bt_config_power_off[pin], rc);
				}
			}
		rc = msm_bahama_setup_pcm_i2s(BT_PCM_OFF);
		if (rc < 0) {
			pr_err("%s: msm_bahama_setup_pcm_i2s, rc =%d\n",
					__func__, rc);
				}
fail_power:
		rc = bluetooth_switch_regulators(0);
		if (rc < 0) {
			pr_err("%s: switch_regulators : rc = %d",\
					__func__, rc);
			goto exit;
		}
	}
	return rc;
exit:
	pr_err("%s: failed with rc = %d", __func__, rc);
	return rc;
}

static int __init bt_power_init(void)
{
	int i, rc = 0;
	struct device *dev = &msm_bt_power_device.dev;

	for (i = 0; i < ARRAY_SIZE(bt_vregs); i++) {
		bt_vregs[i].reg = regulator_get(dev, bt_vregs[i].name);
		if (IS_ERR(bt_vregs[i].reg)) {
			rc = PTR_ERR(bt_vregs[i].reg);
			dev_err(dev, "%s: could not get regulator %s: %d\n",
					__func__, bt_vregs[i].name, rc);
			goto reg_get_fail;
		}
	}

	dev->platform_data = &bluetooth_power;

	return rc;

reg_get_fail:
	while (i--) {
		regulator_put(bt_vregs[i].reg);
		bt_vregs[i].reg = NULL;
	}
	return rc;
}

static struct marimba_platform_data marimba_pdata = {
	.slave_id[SLAVE_ID_BAHAMA_FM]        = BAHAMA_SLAVE_ID_FM_ADDR,
	.slave_id[SLAVE_ID_BAHAMA_QMEMBIST]  = BAHAMA_SLAVE_ID_QMEMBIST_ADDR,
	.bahama_setup                        = msm_bahama_setup_power,
	.bahama_shutdown                     = msm_bahama_shutdown_power,
	.bahama_core_config                  = msm_bahama_core_config,
	.fm				     = &marimba_fm_pdata,
};

#endif

/* FIH-SW1-PERIPHERAL-FG-MSENSOR-00+[ */
#ifdef CONFIG_FIH_MSENSOR_AKM8975
static int akm8975_gpio_init(void)
{
    int COMPASS_INT = GPIO_COMPASS_INT;
    if (gpio_request(COMPASS_INT, "COMPASS_INT"))
    {
        printk(KERN_ERR "[MSENSOR] %s(%d): Request GPIO(%d) failed.\n", __FUNCTION__, __LINE__, COMPASS_INT);
        return -EIO;
    }
    if (gpio_tlmm_config(GPIO_CFG(COMPASS_INT, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), GPIO_CFG_ENABLE))
    {
        gpio_free(COMPASS_INT);
        printk(KERN_ERR "[MSENSOR] %s(%d): Config GPIO(%d) failed.\n", __FUNCTION__, __LINE__, COMPASS_INT);
        return -EIO;
    }
    gpio_direction_input(COMPASS_INT);

    printk("[MSENSOR] %s(%d): GPIO(%d) Done.\n", __FUNCTION__, __LINE__, COMPASS_INT);
    return 0;
}

static struct akm8975_platform_data akm8975_platform_data = {
    .gpio_init = akm8975_gpio_init,
    .layout = 2,
};
#endif
/* FIH-SW1-PERIPHERAL-FG-MSENSOR-00+] */

/* FIH-SW1-PERIPHERAL-FG-GSENSOR-00+[ */
#ifdef CONFIG_FIH_GSENSOR_BMA250
static int bma250_gpio_init(void)
{
    int GS_INT = GPIO_GS_INT;
    if (gpio_request(GS_INT, "GS_INT"))
    {
        GSENSOR_DEBUG(LEVEL0, "Request GPIO(%d) failed.", GS_INT);
        return -EIO;
    }
    if (gpio_tlmm_config(GPIO_CFG(GS_INT, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE))
    {
        gpio_free(GS_INT);
        GSENSOR_DEBUG(LEVEL0, "Config GPIO(%d) failed.", GS_INT);
        return -EIO;
    }
    gpio_direction_input(GS_INT);
    gpio_set_value_cansleep(GS_INT, 0);

    GSENSOR_DEBUG(LEVEL0, "GPIO(%d) Done.", GS_INT);
    return 0;
}

static struct bma250_platform_data bma250_platform_data = {
    .gpio_init = bma250_gpio_init,
    .layout = 2,
};
#endif
/* FIH-SW1-PERIPHERAL-FG-GSENSOR-00+] */

/* FIH-SW1-PERIPHERAL-FG-PSENSOR-00+[ */
#ifdef CONFIG_FIH_PSENSOR_QPDSS702
static int qpdss702_gpio_init(void)
{
    int ALPS_OUT = GPIO_ALPS_OUT;
    if (gpio_request(ALPS_OUT, "ALPS_OUT"))
    {
        PSENSOR_DEBUG(LEVEL0, "Request GPIO(%d) failed.", ALPS_OUT);
        return -EIO;
    }
    if (gpio_tlmm_config(GPIO_CFG(ALPS_OUT, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE))
    {
        PSENSOR_DEBUG(LEVEL0, "Config GPIO(%d) failed.", ALPS_OUT);
        return -EIO;
    }
    gpio_direction_input(ALPS_OUT);

    PSENSOR_DEBUG(LEVEL0, "GPIO(%d) Done.", ALPS_OUT);
    return 0;
}

static struct qpdss702_platform_data qpdss702_platform_data = {
    .gpio_init = qpdss702_gpio_init,
    .sensitivity = (QPDSS702_TYPICAL_MODE & QPDSS702_THRESHOLD_MASK) >> 2,
};
#endif
/* FIH-SW1-PERIPHERAL-FG-PSENSOR-00+] */

/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-00+[*/
/* SW1D3-Peripheral-OH-Cypress(TMA340)_TouchDriver_Porting-00+{ */
#ifdef CONFIG_FIH_TOUCHSCREEN_CYTTSP_I2C_TMA340
/*#define CY_I2C_IRQ_GPIO	  86*/	/* FIH-MTD-PERIPHERAL-CH-MES-02* */
#define TOUCH_DEVICE_VREG "emmc"
#define CY_RST_N_GPIO	  121 /*FIH-SW3-PERIPHERAL-CH-TAP-01++*/

/*FIH-MTD-PERIPHERAL-CH-Key_area-00++[*/
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-02+[*/
#ifndef FIH_VIRTUAL_BUTTON /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/
static ssize_t tma340_virtual_keys_show(struct kobject *kobj,
                               struct kobj_attribute *attr, char *buf)
{
                /* center: x: back: 53, menu: 160, home: 267, y: 514 */
				/*FIH-MTD-PERIPHERAL-CH-KEY_AREA-00++[*/
                /*return sprintf(buf,
                        __stringify(EV_KEY) ":" __stringify(KEY_BACK)  ":53:514:53:69"
                   ":" __stringify(EV_KEY) ":" __stringify(KEY_HOME)   ":160:514:53:69"
                   ":" __stringify(EV_KEY) ":" __stringify(KEY_MENU)   ":267:514:53:69"
                   "\n");*/
				/*FIH-MTD-PERIPHERAL-CH-KEY_AREA-01++[*/
				/* center: x: back: 45, menu: 160, home: 275, y: 523 SHIFT for moving down 14 points away  TOUCH AA */
				return sprintf(buf,
                        __stringify(EV_KEY) ":" __stringify(KEY_BACK)  ":45:523:70:55"
                   ":" __stringify(EV_KEY) ":" __stringify(KEY_HOME)   ":160:523:53:55"
                   ":" __stringify(EV_KEY) ":" __stringify(KEY_MENU)   ":275:523:70:55"
                   "\n");
				/*FIH-MTD-PERIPHERAL-CH-KEY_AREA-01++]*/
}
/*FIH-MTD-PERIPHERAL-CH-Key_area-00++]*/
static struct kobj_attribute tma340_virtual_keys_attr = {
        .attr = {
                .name = "virtualkeys.cyttsp_i2c_tma340",
                .mode = S_IRUGO,
        },
        .show = &tma340_virtual_keys_show,
};

static struct attribute *tma340_properties_attrs[] = {
        &tma340_virtual_keys_attr.attr,
        NULL
};

static struct attribute_group tma340_properties_attr_group = {
        .attrs = tma340_properties_attrs,
};
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-02+]*/
#endif /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/

static struct regulator_bulk_data regs_tch[] = {
	{ .supply = "emmc",   .min_uV = 3000000, .max_uV = 3000000 },
};
/*FIH-MTD-PERIPHERAL-CH-2020-00++[*/
/*FIH-MTD-PERIPHERAL-CH-MES-02++[*/
static unsigned touch_config_gpio[] = {
	/*IRQ for PD*/
	GPIO_CFG(40, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
	/*RESET*/
	GPIO_CFG(121, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	/*IRQ for after DP*/
	GPIO_CFG(86, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
	/*Wake up chip*/
	GPIO_CFG(40, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	GPIO_CFG(86, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
};
/*FIH-MTD-PERIPHERAL-CH-2020-00++]*/
/*FIH-MTD-PERIPHERAL-CH-MES-02++]*/
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-01+]*/

/* optional init function; set up IRQ GPIO;
 * call reference in platform data structure
 */
static int cyttsp_i2c_init(int on)
{ 
	int ret;
#ifndef FIH_VIRTUAL_BUTTON /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/
	struct kobject *properties_kobj;/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-03+*/
#endif /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/
	/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-01+[*/
	/*struct vreg *device_vreg; */

	/* add any special code to initialize any required system hw
	 * such as regulators or gpio pins
	 */
	//Power on vreg-emmc
	ret=regulator_bulk_get(NULL, ARRAY_SIZE(regs_tch), regs_tch);
	/*device_vreg = regulator_bulk_get(0, TOUCH_DEVICE_VREG);*/
	if (ret) 
	{
		printk(KERN_INFO"%s: vreg get failed \n", __func__); 
		return -EFAULT;
	}

	/*vreg_set_level(device_vreg, 3000);*/
	regulator_bulk_set_voltage(ARRAY_SIZE(regs_tch), regs_tch);
	/*ret = vreg_enable(device_vreg);*/
	ret=regulator_bulk_enable(ARRAY_SIZE(regs_tch), regs_tch);

	//request GPIO resource
	if (on) 
	{
		
		/* for MSM systems the call to gpio_direction_input can be
		 * replaced with the more explicit call:
		 */
		/*FIH-MTD-PERIPHERAL-CH-2020-00++[*/
		/*FIH-MTD-PERIPHERAL-CH-MES-02++[*/
		if(fih_get_product_phase() < Phase_DP)
		{
			printk(KERN_INFO "%s: PD config GPIO 40\n",
			       __func__);
			ret = gpio_tlmm_config(touch_config_gpio[0], GPIO_CFG_ENABLE);/*FIH-SW3-PERIPHERAL-CH-TAP-02++*/
		}
		else
		{
			printk(KERN_INFO "%s: DP config GPIO 86 \n",
			       __func__);
			ret = gpio_tlmm_config(touch_config_gpio[2], GPIO_CFG_ENABLE);
		}
		/*FIH-MTD-PERIPHERAL-CH-MES-02++]*/
		/*FIH-MTD-PERIPHERAL-CH-2020-00++]*/
		if (ret)
		{
			printk(KERN_ERR "%s: Failed to gpio_tlmm_config %d\n",
			       __func__, CY_I2C_IRQ_GPIO);
			return ret;
		}
		
		ret = gpio_request(CY_I2C_IRQ_GPIO, "CYTTSP IRQ GPIO");
		if (ret) 
		{
			printk(KERN_ERR "%s: Failed to request GPIO %d\n",
			       __func__, CY_I2C_IRQ_GPIO);
			return ret;
		}

		gpio_direction_input(CY_I2C_IRQ_GPIO);
/*FIH-SW3-PERIPHERAL-CH-TAP-01++[*/
		/*Add to control reset pin*/
		ret = gpio_tlmm_config(touch_config_gpio[1], GPIO_CFG_ENABLE);
		if (ret)
		{
			printk(KERN_ERR "%s: Failed to gpio_tlmm_config %d\n",
			       __func__, CY_RST_N_GPIO);
			return ret;
		}
		
		ret = gpio_request(CY_RST_N_GPIO, "CYTTSP RST GPIO");
		if (ret) 
		{
			printk(KERN_ERR "%s: Failed to request GPIO %d\n",
			       __func__, CY_RST_N_GPIO);
			return ret;
		}

		gpio_set_value_cansleep(CY_RST_N_GPIO, 1);
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-01+]*/
/*FIH-SW3-PERIPHERAL-CH-TAP-01++]*/
	} 
	else 
	{
		printk(KERN_INFO "gpio_free(%d)\n", CY_I2C_IRQ_GPIO);
		gpio_free(CY_I2C_IRQ_GPIO);
	}

#ifndef FIH_VIRTUAL_BUTTON /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-02+[*/
	properties_kobj = kobject_create_and_add("board_properties", NULL);
	if (properties_kobj)
        ret = sysfs_create_group(properties_kobj,&tma340_properties_attr_group);

	if (!properties_kobj || ret)
		printk(KERN_ERR "%s: failed to create board_properties\n",__func__);
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-02+]*/
#endif /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/

	return 0;
}
/*FIH-MTD-PERIPHERAL-CH-Add_command-00++[*/
#ifdef reset_cmd
static int cyttsp_reset(void)
{
	gpio_direction_output(CY_RST_N_GPIO, 0);
	msleep(10);
	gpio_direction_output(CY_RST_N_GPIO, 1);
	return 0;
}
#endif
/*FIH-MTD-PERIPHERAL-CH-Add_command-00++]*/
/*FIH-MTD-PERIPHERAL-CH-2020-00++[*/
static int cyttsp_i2c_wakeup(void)
{
	//assert from host to chip by interrupt pin
	int ret =0;
	if(fih_get_product_phase() < Phase_DP)
		ret = gpio_tlmm_config(touch_config_gpio[3], GPIO_CFG_ENABLE);
	else
		ret = gpio_tlmm_config(touch_config_gpio[4], GPIO_CFG_ENABLE);
	if (ret)
	{
		printk(KERN_ERR "%s: Failed to gpio_tlmm_config %d\n",
		       __func__, CY_I2C_IRQ_GPIO);
	}
	gpio_direction_output(CY_I2C_IRQ_GPIO, 1);
	msleep(10);
	gpio_direction_output(CY_I2C_IRQ_GPIO, 0);
	msleep(10);
	gpio_direction_output(CY_I2C_IRQ_GPIO, 1);
	if(fih_get_product_phase() < Phase_DP)
		ret = gpio_tlmm_config(touch_config_gpio[0], GPIO_CFG_ENABLE);
	else
		ret = gpio_tlmm_config(touch_config_gpio[2], GPIO_CFG_ENABLE);
	if (ret)
	{
		printk(KERN_ERR "%s: Failed to gpio_tlmm_config %d\n",
		       __func__, CY_I2C_IRQ_GPIO);
	}
	gpio_direction_input(CY_I2C_IRQ_GPIO);

	return 0;
}
/*FIH-MTD-PERIPHERAL-CH-2020-00++]*/

static struct cyttsp_platform_data cypress_i2c_ttsp_platform_data = {
	.wakeup = cyttsp_i2c_wakeup, /*wake up IC from deep sleep, assert interrupt pin by host-side*/
	.init = cyttsp_i2c_init, /*init power and gpio resource*/
	.mt_sync = input_mt_sync, /*sync mutli-touch event*/
#ifdef reset_cmd
	.reset = cyttsp_reset, /*FIH-MTD-PERIPHERAL-CH-Add_command-00*/
#endif
#ifdef SECOND_MODULE
	.module_1 = "    TPK", /*FIH-MTD-PERIPHERAL-CH-Add_command-00*/
	.module_2 = "    ELK",/*FIH-MTD-PERIPHERAL-CH-Add_command-00*/
#endif
	.maxx = 320, /*480, 479, 320 for Tapioca*/
	.maxy = 480/*553*/, /*800, 799, 480 for Tapioca(553 includes keys area) FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-01*/
	.flags = 0, /*0x05, reverse x / y or not, 1:yes, 0:no*/
	.gen = CY_GEN3, /*generation */
	.use_st = 0, /*support single-touch FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-02+*/
	.use_mt = 1, /*support multi-touch FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-02+*/
	.use_trk_id = 1, /*FIH-MTD-PERIPHERAL-CH-TRACKING_ID-00++*/
	.use_hndshk = 0, /*FIH-MTD-PERIPHERAL-CH-Handshake-00++*/
	.use_timer = 0, /*use polling*/
	.use_sleep = 1, /*deep sleep mode for early suspend/late resume*/
	.use_gestures = 0, /*use gestures function*/
	.use_load_file = 1,
	.use_force_fw_update = 1, /*useless value*/
	.use_virtual_keys = 0, /*use virtual key function*/
	/* activate up to 4 groups
	 * and set active distance
	 */
	.gest_set = CY_GEST_GRP_NONE | CY_ACT_DIST,
	/* change act_intrvl to customize the Active power state
	 * scanning/processing refresh interval for Operating mode
	 */
	.act_intrvl = CY_ACT_INTRVL_DFLT, //active refresh interval, page 13.
	/* change tch_tmout to customize the touch timeout for the
	 * Active power state for Operating mode
	 */
	.tch_tmout = CY_TCH_TMOUT_DFLT, //touch timeout, page 13.
	/* change lp_intrvl to customize the Low Power power state
	 * scanning/processing refresh interval for Operating mode
	 */
	.lp_intrvl = CY_LP_INTRVL_DFLT, //low power interval, page 13.
	.name = CY_I2C_NAME,
	.irq_gpio = 86,/*FIH-MTD-PERIPHERAL-CH-MES-02++[*/ //ISR Number
	.row_pins_number = 18, /*FIH-MTD-PERIPHERAL-CH-MES-02++*/	
	.col_pins_number = 11, /*FIH-MTD-PERIPHERAL-CH-MES-02++*/	
};
#endif
/* SW1D3-Peripheral-OH-Cypress(TMA340)_TouchDriver_Porting-00+} */
/*FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-00+]*/
#if defined(CONFIG_I2C) && defined(CONFIG_GPIO_SX150X)
static struct i2c_board_info core_exp_i2c_info[] __initdata = {
	{
		I2C_BOARD_INFO("sx1509q", 0x3e),
	},
};
static struct i2c_board_info cam_exp_i2c_info[] __initdata = {
	{
		I2C_BOARD_INFO("sx1508q", 0x22),
		.platform_data	= &sx150x_data[SX150X_CAM],
	},
};
#endif
#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
static struct i2c_board_info bahama_devices[] = {
{
	I2C_BOARD_INFO("marimba", 0xc),
	.platform_data = &marimba_pdata,
},
};
#endif

/*FIH-SW3-Peripheral-AC-I2C_INFO_CONFIG-00+{*/
#if defined(CONFIG_I2C)
static struct i2c_board_info i2c_bus1_i2c_info[] __initdata =
{
/* FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-00+{ */
#ifdef CONFIG_FIH_TOUCHSCREEN_CYTTSP_I2C_TMA340
    {
		I2C_BOARD_INFO(CY_I2C_NAME, 0x24),
		.platform_data = &cypress_i2c_ttsp_platform_data,
    },
#endif    
/* FIH-SW3-PERIPHERAL-CH-TouchDriver_Porting_2010-00+} */
/* FIH-SW1-PERIPHERAL-FG-MSENSOR-00+[ */
#ifdef CONFIG_FIH_MSENSOR_AKM8975
	{
		I2C_BOARD_INFO(AKM8975_I2C_NAME, 0x0C),
		//.flags = I2C_CLIENT_WAKE,
		.platform_data = &akm8975_platform_data,
		//.irq = MSM_GPIO_TO_INT(GPIO_COMPASS_INT),
	},
#endif
/* FIH-SW1-PERIPHERAL-FG-MSENSOR-00+] */
/* FIH-SW1-PERIPHERAL-FG-GSENSOR-00+[ */
#ifdef CONFIG_FIH_GSENSOR_BMA250
	{
		I2C_BOARD_INFO(GSENSOR_NAME, 0x18),
		.platform_data = &bma250_platform_data,
		.irq = MSM_GPIO_TO_INT(GPIO_GS_INT),
	},
#endif
/* FIH-SW1-PERIPHERAL-FG-GSENSOR-00+] */
/* FIH-SW1-PERIPHERAL-FG-PSENSOR-00+[ */
#ifdef CONFIG_FIH_PSENSOR_QPDSS702
	{
		I2C_BOARD_INFO(PSENSOR_NAME, 0x54),
		.platform_data = &qpdss702_platform_data,
		.irq = MSM_GPIO_TO_INT(GPIO_ALPS_OUT),
	},
#endif
/* FIH-SW1-PERIPHERAL-FG-PSENSOR-00+] */
};
#endif
/*FIH-SW3-Peripheral-AC-I2C_INFO_CONFIG-00+}*/

#if defined(CONFIG_I2C) && defined(CONFIG_GPIO_SX150X)
static void __init register_i2c_devices(void)
{

	i2c_register_board_info(MSM_GSBI0_QUP_I2C_BUS_ID,
				cam_exp_i2c_info,
				ARRAY_SIZE(cam_exp_i2c_info));

	if (machine_is_msm7x27a_surf() || machine_is_msm7625a_surf())
		sx150x_data[SX150X_CORE].io_open_drain_ena = 0xe0f0;

	core_exp_i2c_info[0].platform_data =
			&sx150x_data[SX150X_CORE];

	i2c_register_board_info(MSM_GSBI1_QUP_I2C_BUS_ID,
				core_exp_i2c_info,
				ARRAY_SIZE(core_exp_i2c_info));
#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
	i2c_register_board_info(MSM_GSBI1_QUP_I2C_BUS_ID,
				bahama_devices,
				ARRAY_SIZE(bahama_devices));
#endif
}
#endif

static struct msm_gpio qup_i2c_gpios_io[] = {
	{ GPIO_CFG(60, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_scl" },
	{ GPIO_CFG(61, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_sda" },
	{ GPIO_CFG(131, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_scl" },
	{ GPIO_CFG(132, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_sda" },
};

static struct msm_gpio qup_i2c_gpios_hw[] = {
	{ GPIO_CFG(60, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_scl" },
	{ GPIO_CFG(61, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_sda" },
	{ GPIO_CFG(131, 2, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_scl" },
	{ GPIO_CFG(132, 2, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
		"qup_sda" },
};

static void gsbi_qup_i2c_gpio_config(int adap_id, int config_type)
{
	int rc;

	if (adap_id < 0 || adap_id > 1)
		return;

	/* Each adapter gets 2 lines from the table */
	if (config_type)
		rc = msm_gpios_request_enable(&qup_i2c_gpios_hw[adap_id*2], 2);
	else
		rc = msm_gpios_request_enable(&qup_i2c_gpios_io[adap_id*2], 2);
	if (rc < 0)
		pr_err("QUP GPIO request/enable failed: %d\n", rc);
}

static struct msm_i2c_platform_data msm_gsbi0_qup_i2c_pdata = {
	.clk_freq		= 400000,
	.msm_i2c_config_gpio	= gsbi_qup_i2c_gpio_config,
};

static struct msm_i2c_platform_data msm_gsbi1_qup_i2c_pdata = {
	.clk_freq		= 400000,
	.msm_i2c_config_gpio	= gsbi_qup_i2c_gpio_config,
};

#ifdef CONFIG_ARCH_MSM7X27A
#define MSM_PMEM_MDP_SIZE       0x1500000/*MTD-SW-MM-CL-PMEMusage-00* //0x2300000 */
#define MSM7x25A_MSM_PMEM_MDP_SIZE       0x1500000

#define MSM_PMEM_ADSP_SIZE      0x1800000//0x1900000 /* FIH-SW3-MM-SL-AddForSoMCPanorama-00* / /*MTD-SW-MM-SL-CustmizeAdspSize-00*/
#define MSM7x25A_MSM_PMEM_ADSP_SIZE      0x1800000//0xB91000


#ifdef CONFIG_FB_MSM_TRIPLE_BUFFER
#define MSM_FB_SIZE		0xE1000/*MTD-SW-MM-CL-PMEMusage-00* //0x261000*/
#define MSM7x25A_MSM_FB_SIZE	0xE1000
#else
#define MSM_FB_SIZE		0xE1000/*MTD-SW-MM-CL-PMEMusage-00* //0x196000*/
#define MSM7x25A_MSM_FB_SIZE	0xE1000

#endif

#endif

static struct android_usb_platform_data android_usb_pdata = {
	.update_pid_and_serial_num = usb_diag_update_pid_and_serial_num,
};

static struct platform_device android_usb_device = {
	.name	= "android_usb",
	.id	= -1,
	.dev	= {
		.platform_data = &android_usb_pdata,
	},
};

#ifdef CONFIG_USB_EHCI_MSM_72K
static void msm_hsusb_vbus_power(unsigned phy_info, int on)
{
	int rc = 0;
	unsigned gpio;

	gpio = GPIO_HOST_VBUS_EN;

	rc = gpio_request(gpio, "i2c_host_vbus_en");
	if (rc < 0) {
		pr_err("failed to request %d GPIO\n", gpio);
		return;
	}
	gpio_direction_output(gpio, !!on);
	gpio_set_value_cansleep(gpio, !!on);
	gpio_free(gpio);
}

static struct msm_usb_host_platform_data msm_usb_host_pdata = {
	.phy_info       = (USB_PHY_INTEGRATED | USB_PHY_MODEL_45NM),
};

static void __init msm7x2x_init_host(void)
{
	msm_add_host(0, &msm_usb_host_pdata);
}
#endif

#ifdef CONFIG_USB_MSM_OTG_72K
static int hsusb_rpc_connect(int connect)
{
	if (connect)
		return msm_hsusb_rpc_connect();
	else
		return msm_hsusb_rpc_close();
}

static struct regulator *reg_hsusb;
static int msm_hsusb_ldo_init(int init)
{
	int rc = 0;

	if (init) {
		reg_hsusb = regulator_get(NULL, "usb");
		if (IS_ERR(reg_hsusb)) {
			rc = PTR_ERR(reg_hsusb);
			pr_err("%s: could not get regulator: %d\n",
					__func__, rc);
			goto out;
		}

		rc = regulator_set_voltage(reg_hsusb, 3300000, 3300000);
		if (rc) {
			pr_err("%s: could not set voltage: %d\n",
					__func__, rc);
			goto reg_free;
		}

		return 0;
	}
	/* else fall through */
reg_free:
	regulator_put(reg_hsusb);
out:
	reg_hsusb = NULL;
	return rc;
}

static int msm_hsusb_ldo_enable(int enable)
{
	static int ldo_status;

	if (IS_ERR_OR_NULL(reg_hsusb))
		return reg_hsusb ? PTR_ERR(reg_hsusb) : -ENODEV;

	if (ldo_status == enable)
		return 0;

	ldo_status = enable;

	return enable ?
		regulator_enable(reg_hsusb) :
		regulator_disable(reg_hsusb);
}

#ifndef CONFIG_USB_EHCI_MSM_72K
static int msm_hsusb_pmic_notif_init(void (*callback)(int online), int init)
{
	int ret = 0;

	if (init)
		ret = msm_pm_app_rpc_init(callback);
	else
		msm_pm_app_rpc_deinit(callback);

	return ret;
}
#endif

static struct msm_otg_platform_data msm_otg_pdata = {
#ifndef CONFIG_USB_EHCI_MSM_72K
	.pmic_vbus_notif_init	 = msm_hsusb_pmic_notif_init,
#else
	.vbus_power		 = msm_hsusb_vbus_power,
#endif
	.rpc_connect		 = hsusb_rpc_connect,
	.pemp_level		 = PRE_EMPHASIS_WITH_20_PERCENT,
	.cdr_autoreset		 = CDR_AUTO_RESET_DISABLE,
	.drv_ampl		 = HS_DRV_AMPLITUDE_DEFAULT,
	.se1_gating		 = SE1_GATING_DISABLE,
	.ldo_init		 = msm_hsusb_ldo_init,
	.ldo_enable		 = msm_hsusb_ldo_enable,
	.chg_init		 = hsusb_chg_init,
	.chg_connected		 = hsusb_chg_connected,
	.chg_vbus_draw		 = hsusb_chg_vbus_draw,
};
#endif

static struct msm_hsusb_gadget_platform_data msm_gadget_pdata = {
	.is_phy_status_timer_on = 1,
};

static struct resource smc91x_resources[] = {
	[0] = {
		.start = 0x90000300,
		.end   = 0x900003ff,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = MSM_GPIO_TO_INT(4),
		.end   = MSM_GPIO_TO_INT(4),
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device smc91x_device = {
	.name           = "smc91x",
	.id             = 0,
	.num_resources  = ARRAY_SIZE(smc91x_resources),
	.resource       = smc91x_resources,
};

#if (defined(CONFIG_MMC_MSM_SDC1_SUPPORT)\
	|| defined(CONFIG_MMC_MSM_SDC2_SUPPORT)\
	|| defined(CONFIG_MMC_MSM_SDC3_SUPPORT)\
	|| defined(CONFIG_MMC_MSM_SDC4_SUPPORT))

static unsigned long vreg_sts, gpio_sts;

struct sdcc_gpio {
	struct msm_gpio *cfg_data;
	uint32_t size;
	struct msm_gpio *sleep_cfg_data;
};

/**
 * Due to insufficient drive strengths for SDC GPIO lines some old versioned
 * SD/MMC cards may cause data CRC errors. Hence, set optimal values
 * for SDC slots based on timing closure and marginality. SDC1 slot
 * require higher value since it should handle bad signal quality due
 * to size of T-flash adapters.
 */
static struct msm_gpio sdc1_cfg_data[] = {
	{GPIO_CFG(51, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc1_dat_3"},
	{GPIO_CFG(52, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc1_dat_2"},
	{GPIO_CFG(53, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc1_dat_1"},
	{GPIO_CFG(54, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc1_dat_0"},
	{GPIO_CFG(55, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc1_cmd"},
	{GPIO_CFG(56, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
								"sdc1_clk"},
};

static struct msm_gpio sdc1_sleep_cfg_data[] = {
	{GPIO_CFG(51, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
								"sdc1_dat_3"},
	{GPIO_CFG(52, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
								"sdc1_dat_2"},
	{GPIO_CFG(53, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
								"sdc1_dat_1"},
	{GPIO_CFG(54, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
								"sdc1_dat_0"},
	{GPIO_CFG(55, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
								"sdc1_cmd"},
	{GPIO_CFG(56, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
								"sdc1_clk"},
};

static struct msm_gpio sdc2_cfg_data[] = {
	{GPIO_CFG(62, 2, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
								"sdc2_clk"},
	{GPIO_CFG(63, 2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc2_cmd"},
	{GPIO_CFG(64, 2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc2_dat_3"},
	{GPIO_CFG(65, 2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc2_dat_2"},
	{GPIO_CFG(66, 2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc2_dat_1"},
	{GPIO_CFG(67, 2, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc2_dat_0"},
/*FIH-SW3-CONN-JL-WiFiWakeUpHost-01+[*/								
	{GPIO_CFG(0xFF, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
								 "wlan_wakeup_host"}
/*FIH-SW3-CONN-JL-WiFiWakeUpHost-01+]*/									
};

static struct msm_gpio sdc2_sleep_cfg_data[] = {
	{GPIO_CFG(62, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
								"sdc2_clk"},
	{GPIO_CFG(63, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc2_cmd"},
	{GPIO_CFG(64, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc2_dat_3"},
	{GPIO_CFG(65, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc2_dat_2"},
	{GPIO_CFG(66, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc2_dat_1"},
	{GPIO_CFG(67, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc2_dat_0"},
/*FIH-SW3-CONN-JL-WiFiWakeUpHost-01+[*/									
	{GPIO_CFG(0xFF, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
								"wlan_wakeup_host"}
/*FIH-SW3-CONN-JL-WiFiWakeUpHost-01+]*/																	
};
static struct msm_gpio sdc3_cfg_data[] = {
	{GPIO_CFG(88, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
								"sdc3_clk"},
	{GPIO_CFG(89, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_cmd"},
	{GPIO_CFG(90, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_3"},
	{GPIO_CFG(91, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_2"},
	{GPIO_CFG(92, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_1"},
	{GPIO_CFG(93, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_0"},
#ifdef CONFIG_MMC_MSM_SDC3_8_BIT_SUPPORT
	{GPIO_CFG(19, 3, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_7"},
	{GPIO_CFG(20, 3, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_6"},
	{GPIO_CFG(21, 3, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_5"},
	{GPIO_CFG(108, 3, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc3_dat_4"},
#endif
};

static struct msm_gpio sdc3_sleep_cfg_data[] = {
	{GPIO_CFG(88, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
								"sdc3_clk"},
	{GPIO_CFG(89, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_cmd"},
	{GPIO_CFG(90, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_3"},
	{GPIO_CFG(91, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_2"},
	{GPIO_CFG(92, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_1"},
	{GPIO_CFG(93, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_0"},
#ifdef CONFIG_MMC_MSM_SDC3_8_BIT_SUPPORT
	{GPIO_CFG(19, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_7"},
	{GPIO_CFG(20, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_6"},
	{GPIO_CFG(21, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_5"},
	{GPIO_CFG(108, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
								"sdc3_dat_4"},
#endif
};

static struct msm_gpio sdc4_cfg_data[] = {
	{GPIO_CFG(19, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc4_dat_3"},
	{GPIO_CFG(20, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc4_dat_2"},
	{GPIO_CFG(21, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc4_dat_1"},
	{GPIO_CFG(107, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc4_cmd"},
	{GPIO_CFG(108, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_UP, GPIO_CFG_10MA),
								"sdc4_dat_0"},
	{GPIO_CFG(109, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_8MA),
								"sdc4_clk"},
};

static struct sdcc_gpio sdcc_cfg_data[] = {
	{
		.cfg_data = sdc1_cfg_data,
		.size = ARRAY_SIZE(sdc1_cfg_data),
		.sleep_cfg_data = sdc1_sleep_cfg_data,
	},
	{
		.cfg_data = sdc2_cfg_data,
		.size = ARRAY_SIZE(sdc2_cfg_data),
		.sleep_cfg_data = sdc2_sleep_cfg_data,
	},
	{
		.cfg_data = sdc3_cfg_data,
		.size = ARRAY_SIZE(sdc3_cfg_data),
		.sleep_cfg_data = sdc3_sleep_cfg_data,
	},
	{
		.cfg_data = sdc4_cfg_data,
		.size = ARRAY_SIZE(sdc4_cfg_data),
	},
};

static struct regulator *sdcc_vreg_data[ARRAY_SIZE(sdcc_cfg_data)];

/*FIH-SW3-CONN-JL-WiFiWakeUpHost-01+[*/
#define WLAN_SLOT 2
static void fih_wlan_wakeup_fix(void) 
{
	int wakeup_pin;
	struct sdcc_gpio *curr;
	curr = &sdcc_cfg_data[WLAN_SLOT - 1];

	if( curr->size < 7) {
		pr_err("%s: wlan wake up GPIO is not config\n", __func__ );
		return;
	}
	
	if(fih_get_product_phase() < Phase_SP)
		wakeup_pin = 83;
	else
		wakeup_pin = 112;
	
	curr->cfg_data[6].gpio_cfg = GPIO_CFG(wakeup_pin, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA);
	curr->sleep_cfg_data[6].gpio_cfg = GPIO_CFG(wakeup_pin, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA);		

}
/*FIH-SW3-CONN-JL-WiFiWakeUpHost-01+]*/

static int msm_sdcc_setup_gpio(int dev_id, unsigned int enable)
{
	int rc = 0;
	struct sdcc_gpio *curr;

	if (dev_id == WLAN_SLOT)
		fih_wlan_wakeup_fix();

	curr = &sdcc_cfg_data[dev_id - 1];
	if (!(test_bit(dev_id, &gpio_sts)^enable))
		return rc;

	if (enable) {
		set_bit(dev_id, &gpio_sts);
		rc = msm_gpios_request_enable(curr->cfg_data, curr->size);
		if (rc)
			pr_err("%s: Failed to turn on GPIOs for slot %d\n",
					__func__,  dev_id);
	} else {
		clear_bit(dev_id, &gpio_sts);
		if (curr->sleep_cfg_data) {
			rc = msm_gpios_enable(curr->sleep_cfg_data, curr->size);
			msm_gpios_free(curr->sleep_cfg_data, curr->size);
			return rc;
		}
		msm_gpios_disable_free(curr->cfg_data, curr->size);
	}
	return rc;
}

static int msm_sdcc_setup_vreg(int dev_id, unsigned int enable)
{
	int rc = 0;
	struct regulator *curr = sdcc_vreg_data[dev_id - 1];

	if (test_bit(dev_id, &vreg_sts) == enable)
		return 0;

	if (!curr)
		return -ENODEV;

	if (IS_ERR(curr))
		return PTR_ERR(curr);

	if (enable) {
		set_bit(dev_id, &vreg_sts);

		rc = regulator_enable(curr);
		if (rc)
			pr_err("%s: could not enable regulator: %d\n",
					__func__, rc);
	} else {
		clear_bit(dev_id, &vreg_sts);

		rc = regulator_disable(curr);
		if (rc)
			pr_err("%s: could not disable regulator: %d\n",
					__func__, rc);
	}
	return rc;
}

static uint32_t msm_sdcc_setup_power(struct device *dv, unsigned int vdd)
{
	int rc = 0;
	struct platform_device *pdev;

	pdev = container_of(dv, struct platform_device, dev);

	rc = msm_sdcc_setup_gpio(pdev->id, !!vdd);
	if (rc)
		goto out;

//CONN-EC-Regulator-01*[
    if (pdev->id == WLAN_SLOT) {
    } else {
	    rc = msm_sdcc_setup_vreg(pdev->id, !!vdd);
    }
//CONN-EC-Regulator-01*]
out:
	return rc;
}

#define GPIO_SDC1_HW_DET 85

#if defined(CONFIG_MMC_MSM_SDC1_SUPPORT) \
	&& defined(CONFIG_MMC_MSM_CARD_HW_DETECTION)
static unsigned int msm7x2xa_sdcc_slot_status(struct device *dev)
{
	int status;

	status = gpio_tlmm_config(GPIO_CFG(GPIO_SDC1_HW_DET, 2, GPIO_CFG_INPUT,
			GPIO_CFG_PULL_UP, GPIO_CFG_8MA), GPIO_CFG_ENABLE);
	if (status)
		pr_err("%s:Failed to configure tlmm for GPIO %d\n", __func__,
				GPIO_SDC1_HW_DET);

	status = gpio_request(GPIO_SDC1_HW_DET, "SD_HW_Detect");
	if (status) {
		pr_err("%s:Failed to request GPIO %d\n", __func__,
				GPIO_SDC1_HW_DET);
	} else {
		status = gpio_direction_input(GPIO_SDC1_HW_DET);
		if (!status)
			status = gpio_get_value(GPIO_SDC1_HW_DET);
		gpio_free(GPIO_SDC1_HW_DET);
	}
	return status;
}
#endif

#ifdef CONFIG_MMC_MSM_SDC1_SUPPORT
static struct mmc_platform_data sdc1_plat_data = {
	.ocr_mask	= MMC_VDD_28_29,
	.translate_vdd  = msm_sdcc_setup_power,
	.mmc_bus_width  = MMC_CAP_4_BIT_DATA,
	.msmsdcc_fmin	= 144000,
	.msmsdcc_fmid	= 24576000,
	.msmsdcc_fmax	= 49152000,
#ifdef CONFIG_MMC_MSM_CARD_HW_DETECTION
	.status      = msm7x2xa_sdcc_slot_status,
	.status_irq  = MSM_GPIO_TO_INT(GPIO_SDC1_HW_DET),
	.irq_flags   = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
#endif
};
#endif

#ifdef CONFIG_MMC_MSM_SDC2_SUPPORT
static struct mmc_platform_data sdc2_plat_data = {
	/*
	 * SDC2 supports only 1.8V, claim for 2.85V range is just
	 * for allowing buggy cards who advertise 2.8V even though
	 * they can operate at 1.8V supply.
	 */
	.ocr_mask	= MMC_VDD_28_29 | MMC_VDD_165_195,
	.translate_vdd  = msm_sdcc_setup_power,
	.mmc_bus_width  = MMC_CAP_4_BIT_DATA,
#ifdef CONFIG_MMC_MSM_SDIO_SUPPORT
	.sdiowakeup_irq = MSM_GPIO_TO_INT(66),
#endif
	.msmsdcc_fmin	= 144000,
	.msmsdcc_fmid	= 24576000,
	.msmsdcc_fmax	= 49152000,
};
#endif

#ifdef CONFIG_MMC_MSM_SDC3_SUPPORT
static struct mmc_platform_data sdc3_plat_data = {
	.ocr_mask	= MMC_VDD_28_29,
	.translate_vdd  = msm_sdcc_setup_power,
#ifdef CONFIG_MMC_MSM_SDC3_8_BIT_SUPPORT
	.mmc_bus_width  = MMC_CAP_8_BIT_DATA,
#else
	.mmc_bus_width  = MMC_CAP_4_BIT_DATA,
#endif
	.msmsdcc_fmin	= 144000,
	.msmsdcc_fmid	= 24576000,
	.msmsdcc_fmax	= 49152000,
	.nonremovable	= 1,
};
#endif

#if (defined(CONFIG_MMC_MSM_SDC4_SUPPORT)\
		&& !defined(CONFIG_MMC_MSM_SDC3_8_BIT_SUPPORT))
static struct mmc_platform_data sdc4_plat_data = {
	.ocr_mask	= MMC_VDD_28_29,
	.translate_vdd  = msm_sdcc_setup_power,
	.mmc_bus_width  = MMC_CAP_4_BIT_DATA,
	.msmsdcc_fmin	= 144000,
	.msmsdcc_fmid	= 24576000,
	.msmsdcc_fmax	= 49152000,
};
#endif

static int __init mmc_regulator_init(int sdcc_no, const char *supply, int uV)
{
	int rc;

	BUG_ON(sdcc_no < 1 || sdcc_no > 4);

	sdcc_no--;

	sdcc_vreg_data[sdcc_no] = regulator_get(NULL, supply);

	if (IS_ERR(sdcc_vreg_data[sdcc_no])) {
		rc = PTR_ERR(sdcc_vreg_data[sdcc_no]);
		pr_err("%s: could not get regulator \"%s\": %d\n",
				__func__, supply, rc);
		goto out;
	}

	rc = regulator_set_voltage(sdcc_vreg_data[sdcc_no], uV, uV);

	if (rc) {
		pr_err("%s: could not set voltage for \"%s\" to %d uV: %d\n",
				__func__, supply, uV, rc);
		goto reg_free;
	}

	return rc;

reg_free:
	regulator_put(sdcc_vreg_data[sdcc_no]);
out:
	sdcc_vreg_data[sdcc_no] = NULL;
	return rc;
}

static void __init msm7x27a_init_mmc(void)
{
	/* eMMC slot */
#ifdef CONFIG_MMC_MSM_SDC3_SUPPORT
	if (mmc_regulator_init(3, "emmc", 3000000))
		return;
	msm_add_sdcc(3, &sdc3_plat_data);
#endif
	/* Micro-SD slot */
#ifdef CONFIG_MMC_MSM_SDC1_SUPPORT
	if (mmc_regulator_init(1, "mmc", 2850000))
		return;
	msm_add_sdcc(1, &sdc1_plat_data);
#endif
	/* SDIO WLAN slot */
#ifdef CONFIG_MMC_MSM_SDC2_SUPPORT
//CONN-EC-Regulator-01-[
//	if (mmc_regulator_init(2, "mmc", 2850000))
//		return;
//CONN-EC-Regulator-01-]
	msm_add_sdcc(2, &sdc2_plat_data);
#endif
	/* Not Used */
#if (defined(CONFIG_MMC_MSM_SDC4_SUPPORT)\
		&& !defined(CONFIG_MMC_MSM_SDC3_8_BIT_SUPPORT))
	if (mmc_regulator_init(4, "mmc", 2850000))
		return;
	msm_add_sdcc(4, &sdc4_plat_data);
#endif
}
#endif

#ifdef CONFIG_SERIAL_MSM_HS
static struct msm_serial_hs_platform_data msm_uart_dm1_pdata = {
	.inject_rx_on_wakeup	= 1,
	.rx_to_inject		= 0xFD,
};
#endif
static struct msm_pm_platform_data msm7x27a_pm_data[MSM_PM_SLEEP_MODE_NR] = {
	[MSM_PM_SLEEP_MODE_POWER_COLLAPSE] = {
					.idle_supported = 1,
					.suspend_supported = 1,
					.idle_enabled = 1,
					.suspend_enabled = 1,
					.latency = 16000,
					.residency = 20000,
	},
	[MSM_PM_SLEEP_MODE_POWER_COLLAPSE_NO_XO_SHUTDOWN] = {
					.idle_supported = 1,
					.suspend_supported = 1,
					.idle_enabled = 1,
					.suspend_enabled = 1,
					.latency = 12000,
					.residency = 20000,
	},
	[MSM_PM_SLEEP_MODE_RAMP_DOWN_AND_WAIT_FOR_INTERRUPT] = {
					.idle_supported = 1,
					.suspend_supported = 1,
					.idle_enabled = 0,
					.suspend_enabled = 1,
					.latency = 2000,
					.residency = 0,
	},
	[MSM_PM_SLEEP_MODE_WAIT_FOR_INTERRUPT] = {
					.idle_supported = 1,
					.suspend_supported = 1,
					.idle_enabled = 1,
					.suspend_enabled = 1,
					.latency = 2,
					.residency = 0,
	},
};

static struct msm_pm_boot_platform_data msm_pm_boot_pdata __initdata = {
	.mode = MSM_PM_BOOT_CONFIG_RESET_VECTOR_PHYS,
	.p_addr = 0,
};

static struct android_pmem_platform_data android_pmem_adsp_pdata = {
	.name = "pmem_adsp",
	.allocator_type = PMEM_ALLOCATORTYPE_BITMAP,
	.cached = 1,
	.memory_type = MEMTYPE_EBI1,
};

static struct platform_device android_pmem_adsp_device = {
	.name = "android_pmem",
	.id = 1,
	.dev = { .platform_data = &android_pmem_adsp_pdata },
};

static unsigned pmem_mdp_size = MSM_PMEM_MDP_SIZE;
static int __init pmem_mdp_size_setup(char *p)
{
	pmem_mdp_size = memparse(p, NULL);
	return 0;
}

early_param("pmem_mdp_size", pmem_mdp_size_setup);

static unsigned pmem_adsp_size = MSM_PMEM_ADSP_SIZE;
static int __init pmem_adsp_size_setup(char *p)
{
	pmem_adsp_size = memparse(p, NULL);
	return 0;
}

early_param("pmem_adsp_size", pmem_adsp_size_setup);

static unsigned fb_size = MSM_FB_SIZE;
static int __init fb_size_setup(char *p)
{
	fb_size = memparse(p, NULL);
	return 0;
}

early_param("fb_size", fb_size_setup);



static struct resource msm_fb_resources[] = {
	{
		.flags  = IORESOURCE_DMA,
	}
};

#define LCDC_TOSHIBA_FWVGA_PANEL_NAME	"lcdc_toshiba_fwvga_pt"
#define MIPI_CMD_RENESAS_FWVGA_PANEL_NAME	"mipi_cmd_renesas_fwvga"

static int msm_fb_detect_panel(const char *name)
{
	int ret = -ENODEV;

	if (machine_is_msm7x27a_surf() || machine_is_msm7625a_surf()) {
		if (!strncmp(name, "lcdc_toshiba_fwvga_pt", 21) ||
				!strncmp(name, "mipi_cmd_renesas_fwvga", 22))
			ret = 0;
	} else if (machine_is_msm7x27a_ffa() || machine_is_msm7625a_ffa()) {
		if (!strncmp(name, "mipi_cmd_renesas_fwvga", 22))
			ret = 0;
	}

#if !defined(CONFIG_FB_MSM_LCDC_AUTO_DETECT) && \
	!defined(CONFIG_FB_MSM_MIPI_PANEL_AUTO_DETECT) && \
	!defined(CONFIG_FB_MSM_LCDC_MIPI_PANEL_AUTO_DETECT)
		if (machine_is_msm7x27a_surf() ||
			machine_is_msm7625a_surf()) {
			if (!strncmp(name, LCDC_TOSHIBA_FWVGA_PANEL_NAME,
				strnlen(LCDC_TOSHIBA_FWVGA_PANEL_NAME,
					PANEL_NAME_MAX_LEN)))
				return 0;
		}
#endif
	return ret;
}

static struct msm_fb_platform_data msm_fb_pdata = {
	.detect_client = msm_fb_detect_panel,
};

static struct platform_device msm_fb_device = {
	.name   = "msm_fb",
	.id     = 0,
	.num_resources  = ARRAY_SIZE(msm_fb_resources),
	.resource       = msm_fb_resources,
	.dev    = {
		.platform_data = &msm_fb_pdata,
	}
};

#define SND(desc, num) { .name = #desc, .id = num }
static struct snd_endpoint snd_endpoints_list[] = {
	SND(HANDSET, 0),
	SND(MONO_HEADSET, 2),
	SND(HEADSET, 3),
	SND(SPEAKER, 6),
	SND(TTY_HEADSET, 8),
	SND(TTY_VCO, 9),
	SND(TTY_HCO, 10),
	SND(BT, 12),
	SND(IN_S_SADC_OUT_HANDSET, 16),
	SND(IN_S_SADC_OUT_SPEAKER_PHONE, 25),
	SND(FM_DIGITAL_STEREO_HEADSET, 26),
	SND(FM_DIGITAL_SPEAKER_PHONE, 27),
	SND(FM_DIGITAL_BT_A2DP_HEADSET, 28),
	SND(STEREO_HEADSET_AND_SPEAKER, 31),
	SND(CURRENT, 0x7FFFFFFE),
	SND(FM_ANALOG_STEREO_HEADSET, 35),
	SND(FM_ANALOG_STEREO_HEADSET_CODEC, 36),
};
#undef SND

static struct msm_snd_endpoints msm_device_snd_endpoints = {
	.endpoints = snd_endpoints_list,
	.num = sizeof(snd_endpoints_list) / sizeof(struct snd_endpoint)
};

static struct platform_device msm_device_snd = {
	.name = "msm_snd",
	.id = -1,
	.dev    = {
		.platform_data = &msm_device_snd_endpoints
	},
};

#define DEC0_FORMAT ((1<<MSM_ADSP_CODEC_MP3)| \
	(1<<MSM_ADSP_CODEC_AAC)|(1<<MSM_ADSP_CODEC_WMA)| \
	(1<<MSM_ADSP_CODEC_WMAPRO)|(1<<MSM_ADSP_CODEC_AMRWB)| \
	(1<<MSM_ADSP_CODEC_AMRNB)|(1<<MSM_ADSP_CODEC_WAV)| \
	(1<<MSM_ADSP_CODEC_ADPCM)|(1<<MSM_ADSP_CODEC_YADPCM)| \
	(1<<MSM_ADSP_CODEC_EVRC)|(1<<MSM_ADSP_CODEC_QCELP))
#define DEC1_FORMAT ((1<<MSM_ADSP_CODEC_MP3)| \
	(1<<MSM_ADSP_CODEC_AAC)|(1<<MSM_ADSP_CODEC_WMA)| \
	(1<<MSM_ADSP_CODEC_WMAPRO)|(1<<MSM_ADSP_CODEC_AMRWB)| \
	(1<<MSM_ADSP_CODEC_AMRNB)|(1<<MSM_ADSP_CODEC_WAV)| \
	(1<<MSM_ADSP_CODEC_ADPCM)|(1<<MSM_ADSP_CODEC_YADPCM)| \
	(1<<MSM_ADSP_CODEC_EVRC)|(1<<MSM_ADSP_CODEC_QCELP))
#define DEC2_FORMAT ((1<<MSM_ADSP_CODEC_MP3)| \
	(1<<MSM_ADSP_CODEC_AAC)|(1<<MSM_ADSP_CODEC_WMA)| \
	(1<<MSM_ADSP_CODEC_WMAPRO)|(1<<MSM_ADSP_CODEC_AMRWB)| \
	(1<<MSM_ADSP_CODEC_AMRNB)|(1<<MSM_ADSP_CODEC_WAV)| \
	(1<<MSM_ADSP_CODEC_ADPCM)|(1<<MSM_ADSP_CODEC_YADPCM)| \
	(1<<MSM_ADSP_CODEC_EVRC)|(1<<MSM_ADSP_CODEC_QCELP))
#define DEC3_FORMAT ((1<<MSM_ADSP_CODEC_MP3)| \
	(1<<MSM_ADSP_CODEC_AAC)|(1<<MSM_ADSP_CODEC_WMA)| \
	(1<<MSM_ADSP_CODEC_WMAPRO)|(1<<MSM_ADSP_CODEC_AMRWB)| \
	(1<<MSM_ADSP_CODEC_AMRNB)|(1<<MSM_ADSP_CODEC_WAV)| \
	(1<<MSM_ADSP_CODEC_ADPCM)|(1<<MSM_ADSP_CODEC_YADPCM)| \
	(1<<MSM_ADSP_CODEC_EVRC)|(1<<MSM_ADSP_CODEC_QCELP))
#define DEC4_FORMAT (1<<MSM_ADSP_CODEC_MIDI)

static unsigned int dec_concurrency_table[] = {
	/* Audio LP */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DMA)), 0,
	0, 0, 0,

	/* Concurrency 1 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC1_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC2_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC3_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC4_FORMAT),

	 /* Concurrency 2 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC1_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC2_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC3_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC4_FORMAT),

	/* Concurrency 3 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC1_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC2_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC3_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC4_FORMAT),

	/* Concurrency 4 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC1_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC2_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC3_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC4_FORMAT),

	/* Concurrency 5 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_TUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC1_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC2_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC3_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC4_FORMAT),

	/* Concurrency 6 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	0, 0, 0, 0,

	/* Concurrency 7 */
	(DEC0_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC1_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC2_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC3_FORMAT|(1<<MSM_ADSP_MODE_NONTUNNEL)|(1<<MSM_ADSP_OP_DM)),
	(DEC4_FORMAT),
};

#define DEC_INFO(name, queueid, decid, nr_codec) { .module_name = name, \
	.module_queueid = queueid, .module_decid = decid, \
	.nr_codec_support = nr_codec}

static struct msm_adspdec_info dec_info_list[] = {
	DEC_INFO("AUDPLAY0TASK", 13, 0, 11), /* AudPlay0BitStreamCtrlQueue */
	DEC_INFO("AUDPLAY1TASK", 14, 1, 11),  /* AudPlay1BitStreamCtrlQueue */
	DEC_INFO("AUDPLAY2TASK", 15, 2, 11),  /* AudPlay2BitStreamCtrlQueue */
	DEC_INFO("AUDPLAY3TASK", 16, 3, 11),  /* AudPlay3BitStreamCtrlQueue */
	DEC_INFO("AUDPLAY4TASK", 17, 4, 1),  /* AudPlay4BitStreamCtrlQueue */
};

static struct msm_adspdec_database msm_device_adspdec_database = {
	.num_dec = ARRAY_SIZE(dec_info_list),
	.num_concurrency_support = (ARRAY_SIZE(dec_concurrency_table) / \
					ARRAY_SIZE(dec_info_list)),
	.dec_concurrency_table = dec_concurrency_table,
	.dec_info_list = dec_info_list,
};

static struct platform_device msm_device_adspdec = {
	.name = "msm_adspdec",
	.id = -1,
	.dev    = {
		.platform_data = &msm_device_adspdec_database
	},
};

static struct android_pmem_platform_data android_pmem_audio_pdata = {
	.name = "pmem_audio",
	.allocator_type = PMEM_ALLOCATORTYPE_BITMAP,
	.cached = 0,
	.memory_type = MEMTYPE_EBI1,
};

static struct platform_device android_pmem_audio_device = {
	.name = "android_pmem",
	.id = 2,
	.dev = { .platform_data = &android_pmem_audio_pdata },
};

static struct android_pmem_platform_data android_pmem_pdata = {
	.name = "pmem",
	.allocator_type = PMEM_ALLOCATORTYPE_BITMAP,
	.cached = 1,
	.memory_type = MEMTYPE_EBI1,
};
static struct platform_device android_pmem_device = {
	.name = "android_pmem",
	.id = 0,
	.dev = { .platform_data = &android_pmem_pdata },
};

/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*[ */
static struct msm_psy_batt_pdata msm_psy_batt_data = {
	.voltage_min_design     = 2800,
	.voltage_max_design     = 4300,
	.avail_chg_sources      = AC_CHG | USB_CHG ,
	.batt_technology        = POWER_SUPPLY_TECHNOLOGY_LION,
	.calculate_capacity     = NULL,	
};
/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*] */

static struct platform_device msm_batt_device = {
	.name               = "msm-battery",
	.id                 = -1,
	.dev.platform_data  = &msm_psy_batt_data,
};

static struct smsc911x_platform_config smsc911x_config = {
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_HIGH,
	.irq_type	= SMSC911X_IRQ_TYPE_PUSH_PULL,
	.flags		= SMSC911X_USE_16BIT,
};

static struct resource smsc911x_resources[] = {
	[0] = {
		.start	= 0x90000000,
		.end	= 0x90007fff,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= MSM_GPIO_TO_INT(48),
		.end	= MSM_GPIO_TO_INT(48),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL,
	},
};

static struct platform_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev		= {
		.platform_data	= &smsc911x_config,
	},
};

static struct msm_gpio smsc911x_gpios[] = {
	{ GPIO_CFG(48, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_6MA),
							 "smsc911x_irq"  },
	{ GPIO_CFG(49, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_6MA),
							 "eth_fifo_sel" },
};

#define ETH_FIFO_SEL_GPIO	49
static void msm7x27a_cfg_smsc911x(void)
{
	int res;

	res = msm_gpios_request_enable(smsc911x_gpios,
				 ARRAY_SIZE(smsc911x_gpios));
	if (res) {
		pr_err("%s: unable to enable gpios for SMSC911x\n", __func__);
		return;
	}

	/* ETH_FIFO_SEL */
	res = gpio_direction_output(ETH_FIFO_SEL_GPIO, 0);
	if (res) {
		pr_err("%s: unable to get direction for gpio %d\n", __func__,
							 ETH_FIFO_SEL_GPIO);
		msm_gpios_disable_free(smsc911x_gpios,
						 ARRAY_SIZE(smsc911x_gpios));
		return;
	}
	gpio_set_value(ETH_FIFO_SEL_GPIO, 0);
}

#ifdef CONFIG_MSM_CAMERA
static uint32_t camera_off_gpio_table[] = {
	GPIO_CFG(15, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
};

static uint32_t camera_on_gpio_table[] = {
	GPIO_CFG(15, 1, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA),
	GPIO_CFG(23, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), /* FIH-SW3-MM-SL-CameraPorting-00 */
};

#ifdef CONFIG_MSM_CAMERA_FLASH
static struct msm_camera_sensor_flash_src msm_flash_src = {
	.flash_sr_type = MSM_CAMERA_FLASH_SRC_EXT,
//SW2D2-MM-MC-Camera-BringUpLm3561ForFlashLed-00*{
#if defined CONFIG_CAMERA_FLASH_LM3561
	._fsrc.ext_driver_src.led_en = 85,
	._fsrc.ext_driver_src.led_flash_en = 84,
#else
	._fsrc.ext_driver_src.led_en = GPIO_CAM_GP_LED_EN1,
	._fsrc.ext_driver_src.led_flash_en = GPIO_CAM_GP_LED_EN2,
#endif
//SW2D2-MM-MC-Camera-BringUpLm3561ForFlashLed-00*}
};
#endif

/* FIH-SW3-MM-SL-CameraPorting-00-{ */
/*static struct regulator_bulk_data regs_camera[] = {
	{ .supply = "msme1", .min_uV = 1800000, .max_uV = 1800000 },
	{ .supply = "gp2",   .min_uV = 2850000, .max_uV = 2850000 },
	{ .supply = "usb2",  .min_uV = 1800000, .max_uV = 1800000 },
};

static void __init msm_camera_vreg_init(void)
{
	int rc;

	rc = regulator_bulk_get(NULL, ARRAY_SIZE(regs_camera), regs_camera);

	if (rc) {
		pr_err("%s: could not get regulators: %d\n", __func__, rc);
		return;
	}

	rc = regulator_bulk_set_voltage(ARRAY_SIZE(regs_camera), regs_camera);

	if (rc) {
		pr_err("%s: could not set voltages: %d\n", __func__, rc);
		return;
	}
}*/
/* FIH-SW3-MM-SL-CameraPorting-00-} */

/* FIH-SW3-MM-SL-CameraPorting-00*{ */
static struct regulator *vreg_gp3;
static void msm_camera_vreg_config(int vreg_en)
{
	int rc;
	printk(" msm_camera_vreg_config\n");

	if (vreg_gp3 == NULL) {
		vreg_gp3 = regulator_get(NULL, "bt");
		if (IS_ERR(vreg_gp3)) {
			pr_err("%s: regulator_get(%s) failed (%ld)\n",
				__func__, "gp3", PTR_ERR(vreg_gp3));
			return;
		}

		rc = regulator_set_voltage(vreg_gp3, 1800000, 1800000);
		if (rc) {
			pr_err("%s: GP3 set level failed (%d)\n",
				__func__, rc);
		}
	}

	if (vreg_en) {

		rc = regulator_enable(vreg_gp3);
		if (rc) {
			pr_err("%s: GP3 enable failed (%d)\n",
				__func__, rc);
		}
		mdelay(1);
	   
		rc = gpio_request(94, "camera power");
		if (rc < 0) {
		    pr_err("%s: gpio_request %d = %d\n", __func__,
			94, rc);
		}
        
		rc = gpio_direction_output(94, 1);
		if (rc < 0) {
			pr_err("%s: gpio_direction_output %d = %d\n", __func__,
				94, rc);
		}
	} else {

		rc = regulator_disable(vreg_gp3);
		if (rc) {
			pr_err("%s: GP3 disable failed (%d)\n",
				__func__, rc);
		}

		rc = gpio_direction_output(94, 0);
		if (rc < 0) {
		       pr_err("%s: gpio_direction_output %d = %d\n", __func__,
			       94, rc);
	         }
		gpio_free(94);
	}
}
/* FIH-SW3-MM-SL-CameraPorting-00*} */

static int config_gpio_table(uint32_t *table, int len)
{
	int rc = 0, i = 0;

	for (i = 0; i < len; i++) {
		rc = gpio_tlmm_config(table[i], GPIO_CFG_ENABLE);
		if (rc) {
			pr_err("%s not able to get gpio\n", __func__);
			for (i--; i >= 0; i--)
				gpio_tlmm_config(camera_off_gpio_table[i],
							GPIO_CFG_ENABLE);
			break;
		}
	}
	return rc;
}

/* FIH-SW3-MM-SL-CameraPorting-00*{ */
#ifdef CONFIG_S5K5CAG
static struct msm_camera_sensor_info msm_camera_sensor_s5k5cag_data;
#endif
#ifdef CONFIG_S5K4E1
static struct msm_camera_sensor_info msm_camera_sensor_s5k4e1_data;
#endif
#ifdef CONFIG_WEBCAM_OV9726
static struct msm_camera_sensor_info msm_camera_sensor_ov9726_data;
#endif
/* FIH-SW3-MM-SL-CameraPorting-00*} */
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+{
#ifdef CONFIG_ISX006
static struct msm_camera_sensor_info msm_camera_sensor_isx006_data;
#endif
#ifdef CONFIG_MT9V115
static struct msm_camera_sensor_info msm_camera_sensor_mt9v115_data;
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+}
static int config_camera_on_gpios_rear(void)
{
	int rc = 0;

	/* FIH-SW3-MM-SL-CameraPorting-00- */ //if (machine_is_msm7x27a_ffa() || machine_is_msm7625a_ffa())
		msm_camera_vreg_config(1);

	rc = config_gpio_table(camera_on_gpio_table,
			ARRAY_SIZE(camera_on_gpio_table));
	if (rc < 0) {
		pr_err("%s: CAMSENSOR gpio table request"
		"failed\n", __func__);
		return rc;
	}

	return rc;
}

static void config_camera_off_gpios_rear(void)
{
	/* FIH-SW3-MM-SL-CameraPorting-00- */ //if (machine_is_msm7x27a_ffa() || machine_is_msm7625a_ffa())
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00*{
#ifndef CONFIG_FIH_PROJECT_MES
		msm_camera_vreg_config(0);
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+}

	config_gpio_table(camera_off_gpio_table,
			ARRAY_SIZE(camera_off_gpio_table));
}

static int config_camera_on_gpios_front(void)
{
	int rc = 0;

	if (machine_is_msm7x27a_ffa() || machine_is_msm7625a_ffa())
		msm_camera_vreg_config(1);

	rc = config_gpio_table(camera_on_gpio_table,
			ARRAY_SIZE(camera_on_gpio_table));
	if (rc < 0) {
		pr_err("%s: CAMSENSOR gpio table request"
			"failed\n", __func__);
		return rc;
	}

	return rc;
}

static void config_camera_off_gpios_front(void)
{
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00*{
#ifndef CONFIG_FIH_PROJECT_MES
	if (machine_is_msm7x27a_ffa() || machine_is_msm7625a_ffa())
		msm_camera_vreg_config(0);
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00*}

	config_gpio_table(camera_off_gpio_table,
			ARRAY_SIZE(camera_off_gpio_table));
}

struct msm_camera_device_platform_data msm_camera_device_data_rear = {
	.camera_gpio_on  = config_camera_on_gpios_rear,
	.camera_gpio_off = config_camera_off_gpios_rear,
	.ioext.csiphy = 0xA1000000,
	.ioext.csisz  = 0x00100000,
	.ioext.csiirq = INT_CSI_IRQ_1,
	.ioclk.mclk_clk_rate = 24000000,
	.ioclk.vfe_clk_rate  = 192000000,
	.ioext.appphy = MSM_CLK_CTL_PHYS,
	.ioext.appsz  = MSM_CLK_CTL_SIZE,
};

struct msm_camera_device_platform_data msm_camera_device_data_front = {
	.camera_gpio_on  = config_camera_on_gpios_front,
	.camera_gpio_off = config_camera_off_gpios_front,
	.ioext.csiphy = 0xA0F00000,
	.ioext.csisz  = 0x00100000,
	.ioext.csiirq = INT_CSI_IRQ_0,
	.ioclk.mclk_clk_rate = 24000000,
	.ioclk.vfe_clk_rate  = 192000000,
	.ioext.appphy = MSM_CLK_CTL_PHYS,
	.ioext.appsz  = MSM_CLK_CTL_SIZE,
};

/* FIH-SW3-MM-SL-CameraPorting-00+{ */
#ifdef CONFIG_S5K5CAG
static struct msm_camera_sensor_platform_info s5k5cag_sensor_7627a_info = {
	.mount_angle = 90
};

static struct msm_camera_sensor_flash_data flash_s5k5cag = {
	.flash_type             = MSM_CAMERA_FLASH_NONE, //MTD_AP_MM_HovanChen_Patch_For_Camera_CTS
	.flash_src              = &msm_flash_src
};

static struct msm_camera_sensor_info msm_camera_sensor_s5k5cag_data = {
	.sensor_name    = "s5k5cag",
	.vreg_1v8 = "bt", /* FIH-SW3-MM-SL-ModifyGPIODefine-00+ */	
	.sensor_reset_enable = 1,
	.sensor_reset   = 23,
	.sensor_pwd             = 26,
	.mclk               = 15,  /* FIH-SW3-MM-SL-ModifyGPIODefine-00+ */
	.vreg_2v8        = 94, /* FIH-SW3-MM-SL-ModifyGPIODefine-00+ */
	.vcm_pwd                = GPIO_CAM_GP_CAM_PWDN,
	.vcm_enable             = 1,
	.pdata                  = &msm_camera_device_data_rear,
	.flash_data             = &flash_s5k5cag,
	.sensor_platform_info   = &s5k5cag_sensor_7627a_info,
	.csi_if                 = 1
};

static struct platform_device msm_camera_sensor_s5k5cag = {
	.name   = "msm_camera_s5k5cag",
	.dev    = {
		.platform_data = &msm_camera_sensor_s5k5cag_data,
	},
};
#endif
/* FIH-SW3-MM-SL-CameraPorting-00+} */

#ifdef CONFIG_S5K4E1
static struct msm_camera_sensor_platform_info s5k4e1_sensor_7627a_info = {
	.mount_angle = 90
};

static struct msm_camera_sensor_flash_data flash_s5k4e1 = {
	.flash_type             = MSM_CAMERA_FLASH_LED,
	.flash_src              = &msm_flash_src
};

static struct msm_camera_sensor_info msm_camera_sensor_s5k4e1_data = {
	.sensor_name    = "s5k4e1",
	.sensor_reset_enable = 1,
	.sensor_reset   = GPIO_CAM_GP_CAMIF_RESET_N,
	.sensor_pwd             = 85,
	.vcm_pwd                = GPIO_CAM_GP_CAM_PWDN,
	.vcm_enable             = 1,
	.pdata                  = &msm_camera_device_data_rear,
	.flash_data             = &flash_s5k4e1,
	.sensor_platform_info   = &s5k4e1_sensor_7627a_info,
	.csi_if                 = 1
};

static struct platform_device msm_camera_sensor_s5k4e1 = {
	.name   = "msm_camera_s5k4e1",
	.dev    = {
		.platform_data = &msm_camera_sensor_s5k4e1_data,
	},
};
#endif

#ifdef CONFIG_IMX072
static struct msm_camera_sensor_platform_info imx072_sensor_7627a_info = {
	.mount_angle = 90
};

static struct msm_camera_sensor_flash_data flash_imx072 = {
	.flash_type             = MSM_CAMERA_FLASH_LED,
	.flash_src              = &msm_flash_src
};

static struct msm_camera_sensor_info msm_camera_sensor_imx072_data = {
	.sensor_name    = "imx072",
	.sensor_reset_enable = 1,
	.sensor_reset   = GPIO_CAM_GP_CAMIF_RESET_N, /* TODO 106,*/
	.sensor_pwd             = 85,
	.vcm_pwd                = GPIO_CAM_GP_CAM_PWDN,
	.vcm_enable             = 1,
	.pdata                  = &msm_camera_device_data_rear,
	.flash_data             = &flash_imx072,
	.sensor_platform_info = &imx072_sensor_7627a_info,
	.csi_if                 = 1
};

static struct platform_device msm_camera_sensor_imx072 = {
	.name   = "msm_camera_imx072",
	.dev    = {
		.platform_data = &msm_camera_sensor_imx072_data,
	},
};
#endif

#ifdef CONFIG_WEBCAM_OV9726
static struct msm_camera_sensor_platform_info ov9726_sensor_7627a_info = {
	.mount_angle = 90
};

static struct msm_camera_sensor_flash_data flash_ov9726 = {
	.flash_type             = MSM_CAMERA_FLASH_NONE,
	.flash_src              = &msm_flash_src
};

static struct msm_camera_sensor_info msm_camera_sensor_ov9726_data = {
	.sensor_name    = "ov9726",
	.sensor_reset_enable = 0,
	.sensor_reset   = GPIO_CAM_GP_CAM1MP_XCLR,
	.sensor_pwd             = 85,
	.vcm_pwd                = 1,
	.vcm_enable             = 0,
	.pdata                  = &msm_camera_device_data_front,
	.flash_data             = &flash_ov9726,
	.sensor_platform_info   = &ov9726_sensor_7627a_info,
	.csi_if                 = 1
};

static struct platform_device msm_camera_sensor_ov9726 = {
	.name   = "msm_camera_ov9726",
	.dev    = {
		.platform_data = &msm_camera_sensor_ov9726_data,
	},
};
/*#else
static inline void msm_camera_vreg_init(void) { }*/
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+{
#ifdef CONFIG_ISX006
static struct msm_camera_sensor_platform_info isx006_sensor_7627a_info = {
	.mount_angle = 90
};

static struct msm_camera_sensor_flash_data flash_isx006 = {
	.flash_type             = MSM_CAMERA_FLASH_LED,//SW2D2-MM-MC-Camera-BringUpLm3561ForFlashLed-00*
	.flash_src              = &msm_flash_src
};

/* FIH-SW3-MM-URI-Add FTM-00+ */
static struct msm_camera_sensor_info msm_camera_sensor_isx006_data = {
	.sensor_name    = "isx006",
	.sensor_reset_enable = 1,
	.sensor_reset   = 23,
	.sensor_pwd     = 26,
	//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+{
	.sensor_f_reset = 0xFF,
	.sensor_f_pwd   = 128,
	//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+}
	/* FIH-SW3-MM-SL-ModifyGPIODefine-01+{ */
	.mclk                   = 15,
	.vreg_af_power          = "bt", 
	.vreg_v1p2               = 115,
	.vreg_v1p8              = 116,
	.vreg_v2p8               = 117,  
	/* FIH-SW3-MM-SL-ModifyGPIODefine-01+} */
	.vcm_pwd                = GPIO_CAM_GP_CAM_PWDN,
	.vcm_enable             = 1,
	.pdata                  = &msm_camera_device_data_rear,
	.flash_data             = &flash_isx006,
	.sensor_platform_info   = &isx006_sensor_7627a_info,
	.csi_if                 = 1
};
/* FIH-SW3-MM-URI-Add FTM-00- */

static struct platform_device msm_camera_sensor_isx006 = {
	.name   = "msm_camera_isx006",
	.dev    = {
		.platform_data = &msm_camera_sensor_isx006_data,
	},
};
#endif

#ifdef CONFIG_MT9V115
static struct msm_camera_sensor_platform_info mt9v115_sensor_7627a_info = {
	.mount_angle = 270 /* FIH-SW3-MM-SL-FaceUnlockRotation-00+} */ /*90*/
};

static struct msm_camera_sensor_flash_data flash_mt9v115 = {
	.flash_type             = MSM_CAMERA_FLASH_NONE,
	.flash_src              = &msm_flash_src
};

static struct msm_camera_sensor_info msm_camera_sensor_mt9v115_data = {
	.sensor_name    = "mt9v115",
	.sensor_reset_enable = 0,
	/* FIH-SW3-MM-SL-ModifyGPIODefine-01*{ */
	.mclk					= 15,
	.vreg_v1p8				= 116,
	.vreg_v2p8				= 117,
	/* FIH-SW3-MM-SL-ModifyGPIODefine-01*} */	
	//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+{
	.sensor_reset   = 23,
	.sensor_pwd     = 26,
    .sensor_f_reset = 0xFF,
    .sensor_f_pwd   = 128,
	//FIH-SW-MM-MC-ImplementSensorReSetForMt9v115-00+}
	.vcm_pwd                = 1,
	.vcm_enable             = 0,
	.pdata                  = &msm_camera_device_data_front,
	.flash_data             = &flash_mt9v115,
	.sensor_platform_info   = &mt9v115_sensor_7627a_info,
	.csi_if                 = 1
};

static struct platform_device msm_camera_sensor_mt9v115 = {
	.name   = "msm_camera_mt9v115",
	.dev    = {
		.platform_data = &msm_camera_sensor_mt9v115_data,
	},
};
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+}

#ifdef CONFIG_MT9E013
static struct msm_camera_sensor_platform_info mt9e013_sensor_7627a_info = {
	.mount_angle = 90
};

static struct msm_camera_sensor_flash_data flash_mt9e013 = {
	.flash_type = MSM_CAMERA_FLASH_LED,
	.flash_src  = &msm_flash_src
};

static struct msm_camera_sensor_info msm_camera_sensor_mt9e013_data = {
	.sensor_name    = "mt9e013",
	.sensor_reset   = 0,
	.sensor_reset_enable = 1,
	.sensor_pwd     = 85,
	.vcm_pwd        = 1,
	.vcm_enable     = 0,
	.pdata          = &msm_camera_device_data_rear,
	.flash_data     = &flash_mt9e013,
	.sensor_platform_info   = &mt9e013_sensor_7627a_info,
	.csi_if         = 1
};

static struct platform_device msm_camera_sensor_mt9e013 = {
	.name      = "msm_camera_mt9e013",
	.dev       = {
		.platform_data = &msm_camera_sensor_mt9e013_data,
	},
};
#endif

static struct i2c_board_info i2c_camera_devices[] = {
	/* FIH-SW3-MM-SL-CameraPorting-00+{ */
	#ifdef CONFIG_S5K5CAG
	{
		I2C_BOARD_INFO("s5k5cag", 0x3C),
	},
	{
		I2C_BOARD_INFO("s5k5cag_af", 0x8c >> 1),
	},
	#endif
	/* FIH-SW3-MM-SL-CameraPorting-00+} */	
	#ifdef CONFIG_S5K4E1
	{
		I2C_BOARD_INFO("s5k4e1", 0x36),
	},
	{
		I2C_BOARD_INFO("s5k4e1_af", 0x8c >> 1),
	},
	#endif
	#ifdef CONFIG_WEBCAM_OV9726
	{
		I2C_BOARD_INFO("ov9726", 0x10),
	},
	#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+{
       #ifdef CONFIG_ISX006
	{
		I2C_BOARD_INFO("isx006", 0x3C),//MIPI I/F
	},
	#endif
	#ifdef CONFIG_MT9V115
	{
		I2C_BOARD_INFO("mt9v115", 0x3D),//0x7A >> 1
	},
	#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+}    
//SW2D2-MM-MC-Camera-BringUpL03561LedDriverIC-00+{
	#ifdef CONFIG_CAMERA_FLASH_LM3561
	{
		I2C_BOARD_INFO("lm3561", 0x53),//0xA6 >> 1
	},
	#endif
//SW2D2-MM-MC-Camera-BringUpL03561LedDriverIC-00+}
	#ifdef CONFIG_IMX072
	{
		I2C_BOARD_INFO("imx072", 0x34),
	},
	#endif
	#ifdef CONFIG_MT9E013
	{
		I2C_BOARD_INFO("mt9e013", 0x6C >> 2),
	},
	#endif
	{
		I2C_BOARD_INFO("sc628a", 0x6E),
	},
};
#endif

#if defined(CONFIG_SERIAL_MSM_HSL_CONSOLE) \
		&& defined(CONFIG_MSM_SHARED_GPIO_FOR_UART2DM)
static struct msm_gpio uart2dm_gpios[] = {
	//{GPIO_CFG(19, 2, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	//						"uart2dm_rfr_n" },
	//{GPIO_CFG(20, 2, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
	//						"uart2dm_cts_n" },
	{GPIO_CFG(21, 2, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
							"uart2dm_rx"    },
	{GPIO_CFG(108, 2, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
							"uart2dm_tx"    },
};

static void msm7x27a_cfg_uart2dm_serial(void)
{
	int ret;
	ret = msm_gpios_request_enable(uart2dm_gpios,
					ARRAY_SIZE(uart2dm_gpios));
	if (ret)
		pr_err("%s: unable to enable gpios for uart2dm\n", __func__);
}
#else
static void msm7x27a_cfg_uart2dm_serial(void) { }
#endif

#ifdef CONFIG_SERIAL_MSM_CONSOLE
static struct msm_gpio uart3_gpios[] = {
	{GPIO_CFG(86, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
							"uart3_tx"    },
	{GPIO_CFG(87, 1, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
							"uart3_rx"    },
};

static void msm7x27a_cfg_uart3_serial(void)
{
	int ret;
	ret = msm_gpios_request_enable(uart3_gpios,
					ARRAY_SIZE(uart3_gpios));
	if (ret)
		pr_err("%s: unable to enable gpios for uart3\n", __func__);
}
#endif

/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*[ */
#ifdef CONFIG_FIH_SW3_BATTERY
static void __init fih_bq27520_driver_init(void)
{
    i2c_register_board_info(1, &msm_bq27520_board_info[0], 1);

    #ifdef CONFIG_FIH_SW3_BQ275X0_ROMMODE
        i2c_register_board_info(1, &msm_bq27520_board_info[1], 1);        
    #endif
}
#endif
/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*] */

static struct platform_device *rumi_sim_devices[] __initdata = {
	&msm_device_dmov,
	&msm_device_smd,
	&smc91x_device,
	&msm_device_uart1,
	&msm_device_nand,
	&msm_device_uart_dm1,
	&msm_gsbi0_qup_i2c_device,
	&msm_gsbi1_qup_i2c_device,
};

static struct platform_device *surf_ffa_devices[] __initdata = {
	&msm_device_dmov,
	&msm_device_smd,
	&msm_device_uart1,
#ifdef CONFIG_SERIAL_MSM_CONSOLE 
	&msm_device_uart3,
#endif
	&msm_device_uart_dm1,
#ifdef CONFIG_SERIAL_MSM_HSL_CONSOLE
	&msm_device_uart_dm2,
#endif	
	&msm_device_nand,
	&msm_gsbi0_qup_i2c_device,
	&msm_gsbi1_qup_i2c_device,
	&msm_device_otg,
	&msm_device_gadget_peripheral,
	&android_usb_device,
	&android_pmem_device,
	&android_pmem_adsp_device,
	&android_pmem_audio_device,
	&msm_device_snd,
	&msm_device_adspdec,
	&msm_fb_device,
	&msm_batt_device,
	&smsc911x_device,
/* FIH-SW3-MM-SL-CameraPorting-00+{ */	
#ifdef CONFIG_S5K5CAG
	&msm_camera_sensor_s5k5cag,
#endif	
/* FIH-SW3-MM-SL-CameraPorting-00+} */
#ifdef CONFIG_S5K4E1
	&msm_camera_sensor_s5k4e1,
#endif
#ifdef CONFIG_IMX072
	&msm_camera_sensor_imx072,
#endif
#ifdef CONFIG_WEBCAM_OV9726
	&msm_camera_sensor_ov9726,
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+{
#ifdef CONFIG_ISX006
	&msm_camera_sensor_isx006,
#endif
#ifdef CONFIG_MT9V115
	&msm_camera_sensor_mt9v115,
#endif
//SW2D2-MM-MC-Camera-BringUpMt9v115Sensor-00+}
#ifdef CONFIG_MT9E013
	&msm_camera_sensor_mt9e013,
#endif
	&msm_kgsl_3d0,
//#ifdef CONFIG_BT
//	&msm_bt_power_device,
//#endif
//#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
//	&msm_bt_power_device,
//#endif
	&asoc_msm_pcm,
	&asoc_msm_dai0,
   //MTD-Conn-JC-BT_FTM-00+[
  #if defined(CONFIG_BROADCOM_BCM4330_BTFM)
	&bcm4330_bt_power_device,
	#endif
	#if defined(CONFIG_BROADCOM_BCM4330_BTFM) && defined(CONFIG_BROADCOM_BCM4330_BTFM_SLEEP)
	&bluesleep_device,//MTD-Conn-JC-BTSleep-00+
	#endif
	//MTD-Conn-JC-BT_FTM-00+]	
	&asoc_msm_dai1,
};

static unsigned pmem_kernel_ebi1_size = PMEM_KERNEL_EBI1_SIZE;
static int __init pmem_kernel_ebi1_size_setup(char *p)
{
	pmem_kernel_ebi1_size = memparse(p, NULL);
	return 0;
}
early_param("pmem_kernel_ebi1_size", pmem_kernel_ebi1_size_setup);

static unsigned pmem_audio_size = MSM_PMEM_AUDIO_SIZE;
static int __init pmem_audio_size_setup(char *p)
{
	pmem_audio_size = memparse(p, NULL);
	return 0;
}
early_param("pmem_audio_size", pmem_audio_size_setup);

static void __init msm_msm7x2x_allocate_memory_regions(void)
{
	void *addr;
	unsigned long size;

	if (machine_is_msm7625a_surf() || machine_is_msm7625a_ffa())
		fb_size = MSM7x25A_MSM_FB_SIZE;
	else
		fb_size = MSM_FB_SIZE;

	size = fb_size;
	addr = alloc_bootmem_align(size, 0x1000);
	msm_fb_resources[0].start = __pa(addr);
	msm_fb_resources[0].end = msm_fb_resources[0].start + size - 1;
	pr_info("allocating %lu bytes at %p (%lx physical) for fb\n",
		size, addr, __pa(addr));
}

static struct memtype_reserve msm7x27a_reserve_table[] __initdata = {
	[MEMTYPE_SMI] = {
	},
	[MEMTYPE_EBI0] = {
		.flags	=	MEMTYPE_FLAGS_1M_ALIGN,
	},
	[MEMTYPE_EBI1] = {
		.flags	=	MEMTYPE_FLAGS_1M_ALIGN,
	},
	//MTD-SW3-KERNEL-MP-Fix_ioremap-00+[
	[MEMTYPE_EBI1_FIH] = {
		.start	=	RAM_CONSOLE_PHYS,
		.size	=	0x300000,	/* reserve 1M for each RAM_CONSOLE, MLOG, and FB for splash screen of ramdump*/
		.flags	=	MEMTYPE_FLAGS_FIXED,
	},
	//MTD-SW3-KERNEL-MP-Fix_ioremap-00+]
};

static void __init size_pmem_devices(void)
{

	if (machine_is_msm7625a_surf() || machine_is_msm7625a_ffa()) {
		pmem_mdp_size = MSM7x25A_MSM_PMEM_MDP_SIZE;
		pmem_adsp_size = MSM7x25A_MSM_PMEM_ADSP_SIZE;
	} else {
		pmem_mdp_size = MSM_PMEM_MDP_SIZE;
		pmem_adsp_size = MSM_PMEM_ADSP_SIZE;
	}

#ifdef CONFIG_ANDROID_PMEM
	android_pmem_adsp_pdata.size = pmem_adsp_size;
	android_pmem_pdata.size = pmem_mdp_size;
	android_pmem_audio_pdata.size = pmem_audio_size;
#endif
}

static void __init reserve_memory_for(struct android_pmem_platform_data *p)
{
	msm7x27a_reserve_table[p->memory_type].size += p->size;
}

static void __init reserve_pmem_memory(void)
{
#ifdef CONFIG_ANDROID_PMEM
	reserve_memory_for(&android_pmem_adsp_pdata);
	reserve_memory_for(&android_pmem_pdata);
	reserve_memory_for(&android_pmem_audio_pdata);
	msm7x27a_reserve_table[MEMTYPE_EBI1].size += pmem_kernel_ebi1_size;
#endif
}

static void __init msm7x27a_calculate_reserve_sizes(void)
{
	size_pmem_devices();
	reserve_pmem_memory();
}

static int msm7x27a_paddr_to_memtype(unsigned int paddr)
{
	return MEMTYPE_EBI1;
}

static struct reserve_info msm7x27a_reserve_info __initdata = {
	.memtype_reserve_table = msm7x27a_reserve_table,
	.calculate_reserve_sizes = msm7x27a_calculate_reserve_sizes,
	.paddr_to_memtype = msm7x27a_paddr_to_memtype,
};

static void __init msm7x27a_reserve(void)
{
	reserve_info = &msm7x27a_reserve_info;
	msm_reserve();
}

static void __init msm_device_i2c_init(void)
{
	msm_gsbi0_qup_i2c_device.dev.platform_data = &msm_gsbi0_qup_i2c_pdata;
	msm_gsbi1_qup_i2c_device.dev.platform_data = &msm_gsbi1_qup_i2c_pdata;
}

static struct msm_panel_common_pdata mdp_pdata = {
	.gpio = 97,
	.mdp_rev = MDP_REV_303,
};


#ifdef CONFIG_FB_MSM
/* FIH-SW3-MM-NC-LCM-10-[+ */
#define GPIO_LCM_RESET 34

static int gpio_lcm_reset;

enum {
	DSI_SINGLE_LANE = 1,
	DSI_TWO_LANES,
};

/* FIH-SW-MM-VH-MES-00*[ */
static int msm_fb_get_lane_config(void)
{
	return DSI_SINGLE_LANE;
}
/* FIH-SW-MM-VH-MES-00*] */

/* FIH-SW-MM-VH-DISPLAY-07*[ */
static int msm_fb_dsi_client_reset(int hold)
{
	int rc = 0;
	static int dsi_reset_initialized = 0;

	printk(KERN_ALERT "[DISPLAY] Enter %s\n", __func__);

	gpio_lcm_reset = GPIO_LCM_RESET;

	if(dsi_reset_initialized == 0)
	{
/* FIH-SW2-MM-NC-LCM_INIT-01-[+ */
		/*MTD-MM-CL-DISPLAY_PWR-00+[*/
		rc = gpio_request(gpio_lcm_reset, "gpio_disp_pwr");
		/*MTD-MM-CL-DISPLAY_PWR-00+]*/
		if (rc < 0) {
			pr_err("[DISPLAY] %s: Failed to request lcm_reset\n", __func__);
			return rc;
		}
/* FIH-SW2-MM-NC-LCM_INIT-01-]- */
		rc = gpio_tlmm_config(GPIO_CFG(gpio_lcm_reset, 0, GPIO_CFG_OUTPUT,
									GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE); 
		dsi_reset_initialized = 1;
	}
	if(hold) {
		gpio_direction_output(gpio_lcm_reset, 0);
	}
	else {
#ifdef CONFIG_FIH_HR_MSLEEP
		hr_msleep(2);  /* FIH-SW3-MM-NC-DEC_TIME-00 */
		rc = gpio_direction_output(gpio_lcm_reset, 1);
		hr_msleep(2);  /* FIH-SW3-MM-NC-DEC_TIME-00 */
		rc |= gpio_direction_output(gpio_lcm_reset, 0);
		hr_msleep(2);  /* FIH-SW3-MM-NC-DEC_TIME-00 */
		rc |= gpio_direction_output(gpio_lcm_reset, 1);
#else
		msleep(2);
		rc = gpio_direction_output(gpio_lcm_reset, 1);
		msleep(2);
		rc |= gpio_direction_output(gpio_lcm_reset, 0);
		msleep(2);
		rc |= gpio_direction_output(gpio_lcm_reset, 1);
#endif
	}
#ifdef CONFIG_FIH_HR_MSLEEP
	hr_msleep(150);
#else
	msleep(150);
#endif
	if (rc < 0) {
		pr_err("[DISPLAY] %s: Failed LCD reset enable\n", __func__);
		return rc;
	}

	return rc;
}


static struct regulator_bulk_data regs_dsi[] = {
	{ .supply = "rfrx1",   .min_uV = 2800000, .max_uV = 2800000 },
	{ .supply = "wlan4", .min_uV = 1800000, .max_uV = 1800000 },
};



static int mipi_dsi_panel_power(int on)
{
	int rc = 0;

    static int dsi_power_initialized = 0;

	printk(KERN_ALERT "[DISPLAY] Enter %s, on = %d\n", __func__, on);

	/* Power off, Reset Pin pull LOW must before power source off */
	if ((!on) || (!dsi_power_initialized)){
		rc = msm_fb_dsi_client_reset(1);
		if (rc < 0) {
			pr_err("[DISPLAY] %s: Failed to pull low lcm reset\n", __func__);
			goto fail_gpio;
		}
	}

	if (!dsi_power_initialized) {
		rc = regulator_bulk_get(NULL, ARRAY_SIZE(regs_dsi), regs_dsi);
		if (rc) {
			pr_err("%s: could not get regulators: %d\n",
					__func__, rc);
				goto fail_gpio;
		}

		rc = regulator_bulk_set_voltage(ARRAY_SIZE(regs_dsi), regs_dsi);
		if (rc) {
			pr_err("%s: could not set voltages: %d\n",
					__func__, rc);
				goto vreg_fail1;
			}

		dsi_power_initialized = 1;
	}


	/*Configure vreg lines */
	rc = on ? regulator_bulk_enable(ARRAY_SIZE(regs_dsi), regs_dsi) :
		  regulator_bulk_disable(ARRAY_SIZE(regs_dsi), regs_dsi);

	if (rc)
		pr_err("%s: could not %sable regulators: %d\n",
				__func__, on ? "en" : "dis", rc);

	return rc;

vreg_fail1:
	regulator_bulk_free(ARRAY_SIZE(regs_dsi), regs_dsi);

fail_gpio:
	gpio_free(gpio_lcm_reset);
	dsi_power_initialized = 0;
	return rc;
}
/* FIH-SW-MM-VH-DISPLAY-07*] */
/* FIH-SW3-MM-NC-LCM-10-]- */
#endif

#define MDP_303_VSYNC_GPIO 97

#ifdef CONFIG_FB_MSM_MDP303
static struct mipi_dsi_platform_data mipi_dsi_pdata = {
	.vsync_gpio = MDP_303_VSYNC_GPIO,
	.dsi_power_save   = mipi_dsi_panel_power,
	.dsi_client_reset = msm_fb_dsi_client_reset,
	.get_lane_config = msm_fb_get_lane_config,
};
#endif

static void __init msm_fb_add_devices(void)
{
	msm_fb_register_device("mdp", &mdp_pdata);
#ifdef CONFIG_FB_MSM_MDP303
	msm_fb_register_device("mipi_dsi", &mipi_dsi_pdata);
#endif
}

#define MSM_EBI2_PHYS			0xa0d00000
#define MSM_EBI2_XMEM_CS2_CFG1		0xa0d10030

static void __init msm7x27a_init_ebi2(void)
{
	uint32_t ebi2_cfg;
	void __iomem *ebi2_cfg_ptr;

	ebi2_cfg_ptr = ioremap_nocache(MSM_EBI2_PHYS, sizeof(uint32_t));
	if (!ebi2_cfg_ptr)
		return;

	ebi2_cfg = readl(ebi2_cfg_ptr);
	if (machine_is_msm7x27a_rumi3() || machine_is_msm7x27a_surf() ||
			machine_is_msm7625a_surf())
		ebi2_cfg |= (1 << 4); /* CS2 */

	writel(ebi2_cfg, ebi2_cfg_ptr);
	iounmap(ebi2_cfg_ptr);

	/* Enable A/D MUX[bit 31] from EBI2_XMEM_CS2_CFG1 */
	ebi2_cfg_ptr = ioremap_nocache(MSM_EBI2_XMEM_CS2_CFG1,
							 sizeof(uint32_t));
	if (!ebi2_cfg_ptr)
		return;

	ebi2_cfg = readl(ebi2_cfg_ptr);
	if (machine_is_msm7x27a_surf() || machine_is_msm7625a_surf())
		ebi2_cfg |= (1 << 31);

	writel(ebi2_cfg, ebi2_cfg_ptr);
	iounmap(ebi2_cfg_ptr);
}

#define ATMEL_TS_I2C_NAME "maXTouch"

static struct regulator_bulk_data regs_atmel[] = {
	{ .supply = "ldo2",  .min_uV = 2850000, .max_uV = 2850000 },
	{ .supply = "smps3", .min_uV = 1800000, .max_uV = 1800000 },
};

#define ATMEL_TS_GPIO_IRQ 82

static int atmel_ts_power_on(bool on)
{
	int rc = on ?
		regulator_bulk_enable(ARRAY_SIZE(regs_atmel), regs_atmel) :
		regulator_bulk_disable(ARRAY_SIZE(regs_atmel), regs_atmel);

	if (rc)
		pr_err("%s: could not %sable regulators: %d\n",
				__func__, on ? "en" : "dis", rc);
	else
		msleep(50);

	return rc;
}

static int atmel_ts_platform_init(struct i2c_client *client)
{
	int rc;
	struct device *dev = &client->dev;

	rc = regulator_bulk_get(dev, ARRAY_SIZE(regs_atmel), regs_atmel);
	if (rc) {
		dev_err(dev, "%s: could not get regulators: %d\n",
				__func__, rc);
		goto out;
	}

	rc = regulator_bulk_set_voltage(ARRAY_SIZE(regs_atmel), regs_atmel);
	if (rc) {
		dev_err(dev, "%s: could not set voltages: %d\n",
				__func__, rc);
		goto reg_free;
	}

	rc = gpio_tlmm_config(GPIO_CFG(ATMEL_TS_GPIO_IRQ, 0,
				GPIO_CFG_INPUT, GPIO_CFG_PULL_UP,
				GPIO_CFG_8MA), GPIO_CFG_ENABLE);
	if (rc) {
		dev_err(dev, "%s: gpio_tlmm_config for %d failed\n",
			__func__, ATMEL_TS_GPIO_IRQ);
		goto reg_free;
	}

	/* configure touchscreen interrupt gpio */
	rc = gpio_request(ATMEL_TS_GPIO_IRQ, "atmel_maxtouch_gpio");
	if (rc) {
		dev_err(dev, "%s: unable to request gpio %d\n",
			__func__, ATMEL_TS_GPIO_IRQ);
		goto ts_gpio_tlmm_unconfig;
	}

	rc = gpio_direction_input(ATMEL_TS_GPIO_IRQ);
	if (rc < 0) {
		dev_err(dev, "%s: unable to set the direction of gpio %d\n",
			__func__, ATMEL_TS_GPIO_IRQ);
		goto free_ts_gpio;
	}
	return 0;

free_ts_gpio:
	gpio_free(ATMEL_TS_GPIO_IRQ);
ts_gpio_tlmm_unconfig:
	gpio_tlmm_config(GPIO_CFG(ATMEL_TS_GPIO_IRQ, 0,
				GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
				GPIO_CFG_2MA), GPIO_CFG_DISABLE);
reg_free:
	regulator_bulk_free(ARRAY_SIZE(regs_atmel), regs_atmel);
out:
	return rc;
}

static int atmel_ts_platform_exit(struct i2c_client *client)
{
	gpio_free(ATMEL_TS_GPIO_IRQ);
	gpio_tlmm_config(GPIO_CFG(ATMEL_TS_GPIO_IRQ, 0,
				GPIO_CFG_INPUT, GPIO_CFG_NO_PULL,
				GPIO_CFG_2MA), GPIO_CFG_DISABLE);
	regulator_bulk_disable(ARRAY_SIZE(regs_atmel), regs_atmel);
	regulator_bulk_free(ARRAY_SIZE(regs_atmel), regs_atmel);
	return 0;
}

static u8 atmel_ts_read_chg(void)
{
	return gpio_get_value(ATMEL_TS_GPIO_IRQ);
}

static u8 atmel_ts_valid_interrupt(void)
{
	return !atmel_ts_read_chg();
}

#define ATMEL_X_OFFSET 13
#define ATMEL_Y_OFFSET 0

static struct mxt_platform_data atmel_ts_pdata = {
	.numtouch = 4,
	.init_platform_hw = atmel_ts_platform_init,
	.exit_platform_hw = atmel_ts_platform_exit,
	.power_on = atmel_ts_power_on,
	.display_res_x = 480,
	.display_res_y = 864,
	.min_x = ATMEL_X_OFFSET,
	.max_x = (505 - ATMEL_X_OFFSET),
	.min_y = ATMEL_Y_OFFSET,
	.max_y = (863 - ATMEL_Y_OFFSET),
	.valid_interrupt = atmel_ts_valid_interrupt,
	.read_chg = atmel_ts_read_chg,
};

static struct i2c_board_info atmel_ts_i2c_info[] __initdata = {
	{
		I2C_BOARD_INFO(ATMEL_TS_I2C_NAME, 0x4a),
		.platform_data = &atmel_ts_pdata,
		.irq = MSM_GPIO_TO_INT(ATMEL_TS_GPIO_IRQ),
	},
};

//MTD-BSP-Y.S-Enable drivers
// For keypad
static struct gpio_keys_button the_buttons[] = {
	{
		.gpio = 37,
		.code = KEY_VOLUMEUP,
		.desc = "Volume Up",
		.wakeup	= 1,
		.active_low = 1,
		.debounce_interval = 50,
		.wakeup_index = 0,
	},
	{
		.gpio = 38,
		.code = KEY_VOLUMEDOWN,
		.desc = "Volume Down",
		.wakeup	= 1,
		.active_low = 1,
		.debounce_interval = 50,
		.wakeup_index = 1,
	},
};

static struct gpio_keys_platform_data the_button_data = {
	.buttons = the_buttons,
	.nbuttons = ARRAY_SIZE(the_buttons),
};

static struct platform_device GUA_BMB_GPIO_key = {
	.name   = "fih_gpio-keys",
	.id     = -1,
	.dev    = {
		.platform_data = &the_button_data,
	},
};

// For Power key
static struct msm_handset_platform_data hs_platform_data = {
	.hs_name = "7k_handset",
	.pwr_key_delay_ms = 0, /* 0 will disable end key */
	.interval	= 1000, /* 1000 ms */
};

static struct platform_device hs_pdev = {
	.name   = "fih_power-key",
	.id     = -1,
	.dev    = {
		.platform_data = &hs_platform_data,
	},
};

// For LED
static struct led_device_data	fih_led_DP_data[] =
{
	{
		.name	= "button-backlight",
		.id	= 3,
		.use_hw	= LED_HW_PMIC_MPP,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_MPP_8,
				.lpg_out		= 3,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.current_sink	= PM_MPP__I_SINK__LEVEL_5mA,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
	{
		.name	= "red",
		.id	= 0,
		.use_hw	= LED_HW_PMIC_MPP,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_MPP_7,
				.lpg_out		= 2,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.current_sink	= PM_MPP__I_SINK__LEVEL_5mA,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
	{
		.name	= "green",
		.id	= 1,
		.use_hw	= LED_HW_PMIC_MPP,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_MPP_3,
				.lpg_out		= 1,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.current_sink	= PM_MPP__I_SINK__LEVEL_5mA,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
	{
		.name	= "blue",
		.id	= 2,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_1,
				.lpg_out		= 4,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
	{
		.name	= "sub-red",
		.id	= 4,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_5,
				.lpg_out		= 5,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 16,
				.lut_table_end	= 31,
			}
		},
	},
	{
		.name	= "sub-green",
		.id	= 5,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_6,
				.lpg_out		= 6,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 32,
				.lut_table_end	= 47,
			}
		},
	},
	{
		.name	= "sub-blue",
		.id	= 6,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_8,
				.lpg_out		= 7,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 48,
				.lut_table_end	= 63,
			}
		},
	},
};

static struct led_device_data	fih_led_SP_data[] =
{
// SP device does not support button-backlight
#if 0
	{
		.name	= "button-backlight",
		.id	= 3,
		.use_hw	= LED_HW_PMIC_MPP,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_MPP_4,
				.lpg_out		= 1,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.current_sink	= PM_MPP__I_SINK__LEVEL_5mA,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
#endif
	{
		.name	= "red",
		.id	= 0,
		.use_hw	= LED_HW_PMIC_MPP,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_MPP_8,
				.lpg_out		= 3,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.current_sink	= PM_MPP__I_SINK__LEVEL_5mA,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
	{
		.name	= "green",
		.id	= 1,
		.use_hw	= LED_HW_MSM_GPIO,
		.detail	=
		{
			.gpio_data	=
			{
				.msm_pin		= 129,
				.led_on_level	= 1,
				.led_off_level	= 0,
			}
		},
	},
	{
		.name	= "blue",
		.id	= 2,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_1,
				.lpg_out		= 4,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.invert		= 1,
				.lut_table_start	= 0,
				.lut_table_end	= 15,
			}
		},
	},
	{
		.name	= "sub-red",
		.id	= 4,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_5,
				.lpg_out		= 5,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 16,
				.lut_table_end	= 31,
			}
		},
	},
	{
		.name	= "sub-green",
		.id	= 5,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_6,
				.lpg_out		= 6,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 32,
				.lut_table_end	= 47,
			}
		},
	},
	{
		.name	= "sub-blue",
		.id	= 6,
		.use_hw	= LED_HW_PMIC_GPIO,
		.detail	=
		{
			.pmic_data	=
			{
				.pmic_pin	= PM_GPIO_8,
				.lpg_out		= 7,
				.on_off_pwm	= 250,
				.blinking_pwm1	= 0,
				.blinking_pwm2	= 511,
				.pwm_clock	= PM_LPG_CLK_SELECT_19P2M,
				.pwm_div_value	= 6,
				.pwm_div_exp	= 3,
				.blinking_time1	= 500,
				.blinking_time2	= 500,
				.interval	= 32,
				.toggle_up_down	= 1,
				.ramp_loop	= 1,
				.ramp_up_down	= 1,
				.use_table	= 0,
				.lut_table_start	= 48,
				.lut_table_end	= 63,
			}
		},
	},
};

struct leds_device_data	fih_leds_data;

static struct platform_device fih_device_leds = {
	.name   = "fih_leds",
	.id	= -1,
	.dev	=
	{
		.platform_data = &fih_leds_data,
	},
};

// For Vibrator
static struct vib_device_data	fih_vibrator_data =
{
	.name	= "pmic-vib",
	.level	= 3000,
};

static struct platform_device fih_device_vibrator = {
	.name   = "fih_vibrator",
	.id	= -1,
	.dev	=
	{
		.platform_data = &fih_vibrator_data,
	},
};
// MTD-BSP-Y.S-Enable drivers

static struct platform_device msm_proccomm_regulator_dev = {
	.name   = PROCCOMM_REGULATOR_DEV_NAME,
	.id     = -1,
	.dev    = {
		.platform_data = &msm7x27a_proccomm_regulator_data
	}
};

/* FIH-SW2-MM-AY-MES_headset_00 [ */
static struct h2w_platform_data fih_headset_data = {
	.cable_in1 = 18,
	.cable_in2 = 29,
};

static struct platform_device fih_device_headset = {
	.name   = "headset_sensor",
	.id     = -1,
	.dev    = {
		.platform_data = &fih_headset_data,
	},
};
/* FIH-SW2-MM-AY-MES_headset_00 ] */

static void __init msm7627a_rumi3_init(void)
{
	msm7x27a_init_ebi2();
	platform_add_devices(rumi_sim_devices,
			ARRAY_SIZE(rumi_sim_devices));
}

#define LED_GPIO_PDM		96
#define UART1DM_RX_GPIO		45
/* FIH-SW3-KERNEL-TH-add_last_alog-00+[ */
#ifdef CONFIG_ANDROID_RAM_CONSOLE
static struct resource ram_console_resources[1] = {
        [0] = {
                .start  = RAM_CONSOLE_PHYS,
                .end    = RAM_CONSOLE_PHYS + RAM_CONSOLE_SIZE - 1,
                .flags  = IORESOURCE_MEM,
        },
};

static struct platform_device ram_console_device = {
        .name   = "ram_console",
        .id     = 0,
        .num_resources  = ARRAY_SIZE(ram_console_resources),
        .resource       = ram_console_resources,
};

#ifdef CONFIG_FEATURE_FIH_SW3_LAST_ALOG
static struct resource alog_ram_console_resources[4] = {
        [0] = {
        .name = "alog_main_buffer",
                .start  = ALOG_RAM_CONSOLE_PHYS_MAIN,
                .end    = ALOG_RAM_CONSOLE_PHYS_MAIN + ALOG_RAM_CONSOLE_SIZE_MAIN - 1,
                .flags  = IORESOURCE_MEM,
        },
        [1] = {
            .name = "alog_radio_buffer",
                .start  = ALOG_RAM_CONSOLE_PHYS_RADIO,
                .end    = ALOG_RAM_CONSOLE_PHYS_RADIO + ALOG_RAM_CONSOLE_SIZE_RADIO - 1,
                .flags  = IORESOURCE_MEM,
        },
        [2] = {
        .name = "alog_events_buffer",
                .start  = ALOG_RAM_CONSOLE_PHYS_EVENTS,
                .end    = ALOG_RAM_CONSOLE_PHYS_EVENTS + ALOG_RAM_CONSOLE_SIZE_EVENTS - 1,
                .flags  = IORESOURCE_MEM,
        },
        [3] = {
		.name = "alog_system_buffer",
                .start  = ALOG_RAM_CONSOLE_PHYS_SYSTEM,
                .end    = ALOG_RAM_CONSOLE_PHYS_SYSTEM + ALOG_RAM_CONSOLE_SIZE_SYSTEM - 1,
                .flags  = IORESOURCE_MEM,
        },
};

static struct platform_device alog_ram_console_device = {
        .name   = "alog_ram_console",
        .id     = 0,
        .num_resources  = ARRAY_SIZE(alog_ram_console_resources),
        .resource       = alog_ram_console_resources,
};
#endif /* end of #ifdef CONFIG_FEATURE_FIH_SW3_LAST_ALOG */
#endif /* end of #ifdef CONFIG_ANDROID_RAM_CONSOLE */
/* FIH-SW3-KERNEL-TH-add_last_alog-00+] */

#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
static int __init msm7x27a_init_ar6000pm(void)
{
	return platform_device_register(&msm_wlan_ar6000_pm_device);
}
#else
static int __init msm7x27a_init_ar6000pm(void) { return 0; }
#endif

static void __init msm7x27a_init_regulators(void)
{
	int rc = platform_device_register(&msm_proccomm_regulator_dev);
	if (rc)
		pr_err("%s: could not register regulator device: %d\n",
				__func__, rc);
}

static void __init msm7x2x_init(void)
{
    fih_get_oem_info(); //MTD-BSP-REXER-SMEM-00
    fih_info_init(); //MTD-BSP-REXER-INFO-00
    
	msm7x2x_misc_init();

	/* Initialize regulators first so that other devices can use them */
	msm7x27a_init_regulators();

	/* Common functions for SURF/FFA/RUMI3 */
	msm_device_i2c_init();

//MTD-BSP-REXER-UART-02*[
  if(fih_get_product_id()==Project_GUA)
  { 
	msm7x27a_init_ebi2();
	msm7x27a_cfg_uart2dm_serial();
  }
  
#ifdef CONFIG_SERIAL_MSM_CONSOLE
  if((fih_get_product_id()==Project_TAP)
   &&(fih_get_product_phase()==Phase_DP)
   &&(fih_get_sim_id()==SINGLE_SIM))
  {
    msm7x27a_cfg_uart3_serial();
  }
  else if((fih_get_product_id()==Project_MES)
        &&(fih_get_product_phase()==Phase_EVB))
  {
    msm7x27a_cfg_uart3_serial();
  }
#endif

//MTD-BSP-REXER-UART-02*] 
#ifdef CONFIG_SERIAL_MSM_HS
	msm_uart_dm1_pdata.wakeup_irq = gpio_to_irq(UART1DM_RX_GPIO);
	msm_device_uart_dm1.dev.platform_data = &msm_uart_dm1_pdata;
#endif

#ifdef CONFIG_USB_MSM_OTG_72K
	msm_otg_pdata.swfi_latency =
		msm7x27a_pm_data
		[MSM_PM_SLEEP_MODE_RAMP_DOWN_AND_WAIT_FOR_INTERRUPT].latency;
	msm_device_otg.dev.platform_data = &msm_otg_pdata;
#endif
	msm_device_gadget_peripheral.dev.platform_data =
		&msm_gadget_pdata;
	msm7x27a_cfg_smsc911x();
	platform_add_devices(msm_footswitch_devices,
			msm_num_footswitch_devices);
	platform_add_devices(surf_ffa_devices,
			ARRAY_SIZE(surf_ffa_devices));
	/* Ensure ar6000pm device is registered before MMC/SDC */
	msm7x27a_init_ar6000pm();
#ifdef CONFIG_MMC_MSM
	msm7x27a_init_mmc();
#endif
	msm_fb_add_devices();
#ifdef CONFIG_USB_EHCI_MSM_72K
	msm7x2x_init_host();
#endif

	msm_pm_set_platform_data(msm7x27a_pm_data,
				ARRAY_SIZE(msm7x27a_pm_data));
	BUG_ON(msm_pm_boot_init(&msm_pm_boot_pdata));

#if defined(CONFIG_I2C) && defined(CONFIG_GPIO_SX150X)
	register_i2c_devices();
#endif
/*FIH-SW3-Peripheral-AC-I2C_INFO_CONFIG-00+{*/

#if defined(CONFIG_I2C)
	i2c_register_board_info(MSM_GSBI1_QUP_I2C_BUS_ID,
				i2c_bus1_i2c_info,
				ARRAY_SIZE(i2c_bus1_i2c_info));
#endif
/*FIH-SW3-Peripheral-AC-I2C_INFO_CONFIG-00+}*/
#if defined(CONFIG_BT) && defined(CONFIG_MARIMBA_CORE)
	bt_power_init();
#endif
	if (machine_is_msm7625a_surf() || machine_is_msm7625a_ffa()) {
		atmel_ts_pdata.min_x = 0;
		atmel_ts_pdata.max_x = 480;
		atmel_ts_pdata.min_y = 0;
		atmel_ts_pdata.max_y = 320;
	}

	i2c_register_board_info(MSM_GSBI1_QUP_I2C_BUS_ID,
		atmel_ts_i2c_info,
		ARRAY_SIZE(atmel_ts_i2c_info));

#if defined(CONFIG_MSM_CAMERA)
	/* FIH-SW3-MM-SL-CameraPorting-00- */ //msm_camera_vreg_init();
	i2c_register_board_info(MSM_GSBI0_QUP_I2C_BUS_ID,
			i2c_camera_devices,
			ARRAY_SIZE(i2c_camera_devices));
#endif

/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*[ */
#ifdef CONFIG_FIH_SW3_BATTERY
	fih_bq27520_driver_init();
#endif
/* FIH-SW3-KERNEL-PK-Battery_Gauge_Porting-00*] */

	// MTD-BSP-Y.S-Enable drivers
	gpio_tlmm_config( GPIO_CFG( 37, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA ), GPIO_CFG_ENABLE );
	gpio_tlmm_config( GPIO_CFG( 38, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA ), GPIO_CFG_ENABLE );

	if( fih_get_product_phase () < Phase_SP )
	{
		printk( "LED : Load DP setting" );
		fih_leds_data.device_data	= fih_led_DP_data;
		fih_leds_data.count	= sizeof( fih_led_DP_data ) / sizeof( *fih_led_DP_data );
	}
	else
	{
		printk( "LED : Load SP setting" );
		gpio_tlmm_config( GPIO_CFG( 129, 0, GPIO_CFG_OUTPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA ), GPIO_CFG_ENABLE );
		fih_leds_data.device_data	= fih_led_SP_data;
		fih_leds_data.count	= sizeof( fih_led_SP_data ) / sizeof( *fih_led_SP_data );
	}

	platform_device_register( &GUA_BMB_GPIO_key );
	platform_device_register( &fih_device_leds );
	platform_device_register( &fih_device_vibrator );
	platform_device_register( &hs_pdev );
	// MTD-BSP-Y.S-Enable drivers

#ifdef CONFIG_MSM_RPC_VIBRATOR
	if (machine_is_msm7x27a_ffa() || machine_is_msm7625a_ffa())
		msm_init_pmic_vibrator();
#endif		
    /* FIH-SW3-KERNEL-TH-add_last_alog-00+[ */
#ifdef CONFIG_ANDROID_RAM_CONSOLE
    platform_device_register(&ram_console_device);
	#ifdef CONFIG_FEATURE_FIH_SW3_LAST_ALOG
	    platform_device_register(&alog_ram_console_device);
	#endif
#endif
    /* FIH-SW3-KERNEL-TH-add_last_alog-00+] */

	platform_device_register( &fih_device_headset); /* FIH-SW2-MM-AY-MES_headset_00 */

	/*7x25a kgsl initializations*/
	msm7x25a_kgsl_3d0_init();
	//MTD-Conn-JC-BT_FTM-00+[
	#if defined(CONFIG_BROADCOM_BCM4330_BTFM)
	bcm4330_bt_power_init();
	#endif
	//MTD-Conn-JC-BT_FTM-00+]
	wifi_power(1); /*FIH-SW3-CONN-JL-WiFiInitFailed-01*/
}

static void __init msm7x2x_init_early(void)
{
	msm_msm7x2x_allocate_memory_regions();
}

MACHINE_START(MSM7X27A_RUMI3, "QCT MSM7x27a RUMI3")
	.boot_params	= PHYS_OFFSET + 0x100,
	.map_io		= msm_common_io_init,
	.reserve	= msm7x27a_reserve,
	.init_irq	= msm_init_irq,
	.init_machine	= msm7627a_rumi3_init,
	.timer		= &msm_timer,
	.init_early     = msm7x2x_init_early,
	.handle_irq	= vic_handle_irq,
MACHINE_END
MACHINE_START(MSM7X27A_SURF, "QCT MSM7x27a SURF")
	.boot_params	= PHYS_OFFSET + 0x100,
	.map_io		= msm_common_io_init,
	.reserve	= msm7x27a_reserve,
	.init_irq	= msm_init_irq,
	.init_machine	= msm7x2x_init,
	.timer		= &msm_timer,
	.init_early     = msm7x2x_init_early,
	.handle_irq	= vic_handle_irq,
MACHINE_END
MACHINE_START(MSM7X27A_FFA, "QCT MSM7x27a FFA")
	.boot_params	= PHYS_OFFSET + 0x100,
	.map_io		= msm_common_io_init,
	.reserve	= msm7x27a_reserve,
	.init_irq	= msm_init_irq,
	.init_machine	= msm7x2x_init,
	.timer		= &msm_timer,
	.init_early     = msm7x2x_init_early,
	.handle_irq	= vic_handle_irq,
MACHINE_END
MACHINE_START(MSM7625A_SURF, "QCT MSM7625a SURF")
	.boot_params    = PHYS_OFFSET + 0x100,
	.map_io         = msm_common_io_init,
	.reserve        = msm7x27a_reserve,
	.init_irq       = msm_init_irq,
	.init_machine   = msm7x2x_init,
	.timer          = &msm_timer,
	.init_early     = msm7x2x_init_early,
	.handle_irq	= vic_handle_irq,
MACHINE_END
MACHINE_START(MSM7625A_FFA, "QCT MSM7625a FFA")
	.boot_params    = PHYS_OFFSET + 0x100,
	.map_io         = msm_common_io_init,
	.reserve        = msm7x27a_reserve,
	.init_irq       = msm_init_irq,
	.init_machine   = msm7x2x_init,
	.timer          = &msm_timer,
	.init_early     = msm7x2x_init_early,
	.handle_irq	= vic_handle_irq,
MACHINE_END
