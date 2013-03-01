/* drivers/video/msm/logo.c
 *
 * Show Logo in RLE 565 format
 *
 * Copyright (C) 2008 Google Incorporated
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <linux/vt_kern.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
/*MTD-MM-CL-DrawLogo-00+[*/
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
/*MTD-MM-CL-DrawLogo-00+]*/
#include <linux/irq.h>
#include <asm/system.h>

#define fb_width(fb)	((fb)->var.xres)
#define fb_height(fb)	((fb)->var.yres)

#if !defined(CONFIG_FB_MSM_DEFAULT_DEPTH_RGBA8888)
static void memset16(void *_ptr, unsigned short val, unsigned count)
{
	unsigned short *ptr = _ptr;
	count >>= 1;
	while (count--)
		*ptr++ = val;
}
/*MTD-MM-CL-DrawLogo-00+[*/
int fih_load_565rle_image(char *filename)
{
	struct fb_info *info;
	int count, err  = 0;
	unsigned max;
	unsigned short  *bits, *ptr;
	unsigned char *data;
	struct file   *filp=NULL;

	mm_segment_t old_fs = get_fs();
	set_fs (KERNEL_DS);

	info = registered_fb[0];
	if (!info) {
		printk(KERN_WARNING "%s: Can not access framebuffer\n",
			__func__);
		return -ENODEV;
	}

	filp = filp_open(filename, O_RDONLY, 0);
	if (IS_ERR(filp)) {
		printk(KERN_WARNING "%s: Can not open %s\n",
			__func__, filename);
		err=-ENOENT;
		goto error2;
	}

	count = filp->f_dentry->d_inode->i_size;
	data = kmalloc(count, GFP_KERNEL);
	if(data==NULL) {
		printk(KERN_WARNING "%s: Can not alloc data\n", __func__);
		err = -ENOMEM;;
		goto error1;
	}

	if(filp->f_op->read(filp, data, count, &filp->f_pos)<0) {
		printk(KERN_WARNING"%s:read file error?\n", __func__);
		err = -EIO;
        goto error1;
	}

	max = fb_width(info) * fb_height(info);
	ptr = (unsigned short *)data;
	bits = (unsigned short *)(info->screen_base);
	while (count > 3) {
		unsigned n = ptr[0];
		if (n > max)
			break;
		memset16(bits, ptr[1], n << 1);
		bits += n;
		max -= n;
		ptr += 2;
		count -= 4;
	}

error1:
	filp_close(filp,NULL);
	kfree(data);
error2:
	set_fs (old_fs);
	return err;
}
/*MTD-MM-CL-DrawLogo-00+]*/
/* 565RLE image format: [count(2 bytes), rle(2 bytes)] */
int load_565rle_image(char *filename)
{
	struct fb_info *info;
	int fd, count, err = 0;
	unsigned max;
	unsigned short *data, *bits, *ptr;

	info = registered_fb[0];
	if (!info) {
		printk(KERN_WARNING "%s: Can not access framebuffer\n",
			__func__);
		return -ENODEV;
	}

	fd = sys_open(filename, O_RDONLY, 0);
	if (fd < 0) {
		printk(KERN_WARNING "%s: Can not open %s\n",
			__func__, filename);
		return -ENOENT;
	}
	count = sys_lseek(fd, (off_t)0, 2);
	if (count <= 0) {
		err = -EIO;
		goto err_logo_close_file;
	}
	sys_lseek(fd, (off_t)0, 0);
	data = kmalloc(count, GFP_KERNEL);
	if (!data) {
		printk(KERN_WARNING "%s: Can not alloc data\n", __func__);
		err = -ENOMEM;
		goto err_logo_close_file;
	}
	if (sys_read(fd, (char *)data, count) != count) {
		err = -EIO;
		goto err_logo_free_data;
	}

	max = fb_width(info) * fb_height(info);
	ptr = data;
	bits = (unsigned short *)(info->screen_base);
	while (count > 3) {
		unsigned n = ptr[0];
		if (n > max)
			break;
		memset16(bits, ptr[1], n << 1);
		bits += n;
		max -= n;
		ptr += 2;
		count -= 4;
	}

err_logo_free_data:
	kfree(data);
err_logo_close_file:
	sys_close(fd);
	return err;
}
EXPORT_SYMBOL(load_565rle_image);
#else /* !defined(CONFIG_FB_MSM_DEFAULT_DEPTH_RGBA8888) */
/* FIH-SW2-MM-KW-RGBA8888-00+{ */
int fih_load_565rle_image_to_RGBA8888(char *filename)
{
    struct fb_info *info  = NULL;
    struct file    *filp  = NULL;
    unsigned short *ptr  = NULL;
    unsigned char  *bits = NULL;
    unsigned char  *data = NULL;
    unsigned max = 0;
    int bits_count = 0, count = 0, err = 0;

    mm_segment_t old_fs = get_fs();
    set_fs (KERNEL_DS);

    info = registered_fb[0];
    if (!info) {
        printk(KERN_WARNING "%s: Can not access framebuffer\n",
            __func__);
        return -ENODEV;
    }

    filp = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(filp)) {
        printk(KERN_WARNING "%s: Can not open %s\n",
            __func__, filename);
        err = -ENOENT;
        goto error2;
    }

    count = filp->f_dentry->d_inode->i_size;
    data = kmalloc(count, GFP_KERNEL);
    if (!data) {
        printk(KERN_WARNING "%s: Can not alloc data\n", __func__);
        err = -ENOMEM;;
        goto error1;
    }

    if (filp->f_op->read(filp, data, count, &filp->f_pos) < 0) {
        printk(KERN_WARNING "%s: read file error?\n", __func__);
        err = -EIO;
        goto error1;
    }

    max = fb_width(info) * fb_height(info);
    ptr = (unsigned short *)data;
    bits = (unsigned char *)(info->screen_base);
    while (count > 3) {
        unsigned n = ptr[0];
        if (n > max)
            break;
        bits_count = n;
        while (bits_count--) {
            *bits++ = (ptr[1] & 0xF800) >> 8;
            *bits++ = (ptr[1] & 0x7E0) >> 3;
            *bits++ = (ptr[1] & 0x1F) << 3;
            *bits++ = 0xFF;
        }
        max -= n;
        ptr += 2;
        count -= 4;
    }

error1:
    filp_close(filp, NULL);
    kfree(data);
error2:
    set_fs(old_fs);
    return err;
}
/* FIH-SW2-MM-KW-RGBA8888-00-} */
#endif /* !defined(CONFIG_FB_MSM_DEFAULT_DEPTH_RGBA8888) */
