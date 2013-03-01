#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/mm.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <asm/uaccess.h>
#include <../arch/arm/mach-msm/include/mach/oem_rapi_client.h>

#define WPS_STA_LIST_FILE "/etc/firmware/ath6k/AR6003/hw2.1.1/bdata.bin"

mm_segment_t oldfs;
unsigned int debug_mask;

module_param(debug_mask, uint, 0644);

void InitKernelEnv(void)
{
    oldfs = get_fs();
    set_fs(KERNEL_DS);
}

void DinitKernelEnv(void){
   set_fs(oldfs); 
}

struct file *OpenFile(char *path,int flag,int mode)
{
    struct file *fp;
 
    fp=filp_open(path, flag, 0);
    if (fp) 
		return fp;
    else 
		return NULL;
}

int WriteFile(struct file *fp,char *buf,int readlen) { 
   if (fp->f_op && fp->f_op->read) 
      return fp->f_op->write(fp,buf,readlen, &fp->f_pos); 
   else 
      return -1; 
} 

 
int ReadFile(struct file *fp,char *buf,int readlen)
{
    if (fp->f_op && fp->f_op->read)
        return fp->f_op->read(fp,buf,readlen, &fp->f_pos);
    else
        return -1;
}
 
int CloseFile(struct file *fp)
{
    filp_close(fp,NULL);
        return 0;
}

/*-- FelexChing - 20120808 Add for r/w wifi cali --*/
void set_wifi_cali(char* buff, int buff_size)
{
       struct oem_rapi_client_streaming_func_arg arg;
	struct oem_rapi_client_streaming_func_ret ret;	
	struct msm_rpc_client *mrc;
	char* input;
	int i = 0;
       int tmp = 0;
	
       input = kzalloc(128, GFP_KERNEL);
	memset(input, 0, 128);
       tmp = buff_size / 128;
	arg.event = OEM_RAPI_CLIENT_EVENT_WIFI_CALI_SET;
	arg.cb_func = NULL;
	arg.handle = (void *)0;
	arg.input = input;
	arg.in_len = 129;
	arg.output_valid = 1;
	arg.out_len_valid = 1;
	arg.output_size = 128;

	mrc = oem_rapi_client_init();

	for(i = 0; i < tmp; i++){
	    memcpy(input, buff + 128*i, 128);
	    oem_rapi_client_streaming_function(mrc, &arg, &ret);
	}

	oem_rapi_client_close();

	kfree(input);
}
/*-- FelexChing - 20120808 Add for r/w wifi cali --*/

/*-- FelexChing - 20120509 Add for r/w nv wlan mac --*/
//#define Buff_Lenght 32
#define Buff_Lenght 128
#define Buff_Size (Buff_Lenght*sizeof(u8))

int get_wifi_cali(char* buff_input)
{
#if 0
	struct oem_rapi_client_streaming_func_arg arg;
	struct oem_rapi_client_streaming_func_ret ret;	
	char* input;
	char* output;
	int out_len;
	int i = 0;	

	struct msm_rpc_client *mrc;

	input = kzalloc(Buff_Size, GFP_KERNEL);
	output = kzalloc(Buff_Size, GFP_KERNEL);

	arg.event = OEM_RAPI_CLIENT_EVENT_WIFI_CALI_GET;
	arg.cb_func = NULL;
	arg.handle = (void *)0;
	arg.in_len = strlen(input) + 1;
	arg.input = input;
	arg.output_valid = 1;
	arg.out_len_valid = 1;
	arg.output_size = Buff_Size;

	ret.output = output;
	ret.out_len = &out_len;

	mrc = oem_rapi_client_init();

	oem_rapi_client_streaming_function(mrc, &arg, &ret);
	oem_rapi_client_close();

       for(i = 0; i < 128; i++)
           pr_err("file_data: %u\n", ret.output[i]);
	
	kfree(input);
	kfree(output);
#else
	struct oem_rapi_client_streaming_func_arg arg;
	struct oem_rapi_client_streaming_func_ret ret;	
	char* input;
	char* output;
	int out_len;
	int tmp = 0;
	char* buff = NULL;
	const char* err_msg = "ERROR";
	
	struct msm_rpc_client *mrc;

	input = kzalloc(Buff_Size, GFP_KERNEL);
	output = kzalloc(Buff_Size, GFP_KERNEL);
	buff = kzalloc(2048, GFP_KERNEL);

	arg.event = OEM_RAPI_CLIENT_EVENT_WIFI_CALI_GET;
	arg.cb_func = NULL;
	arg.handle = (void *)0;
	arg.in_len = strlen(input) + 1;
	arg.input = input;
	arg.output_valid = 1;
	arg.out_len_valid = 1;
	arg.output_size = Buff_Size;

	ret.output = output;
	ret.out_len = &out_len;

	mrc = oem_rapi_client_init();
	for(tmp = 0; tmp < 16; tmp++){
	    oem_rapi_client_streaming_function(mrc, &arg, &ret);
	    if(strcmp(ret.output, err_msg) == 0)
	        return -1;
	    else
	        memcpy(buff + 128 * tmp, ret.output, 128);
	}
	oem_rapi_client_close();

       if(strcmp(buff, buff_input) == 0)
	    pr_err("---------------------read_file 123333333333333333333333333------------------------\n");
	else
	    pr_err("---------------------read_file fail------------------------\n");
	   	
	kfree(input);
	kfree(output);
	
	return 0;
#endif
}
/*-- FelexChing - 20120509 Add for r/w nv wlan mac --*/

static int __init readfile_init(void)
{
    char* read_buf = NULL;
    struct file *fp;
    int filesize;

    pr_err("---------------------readfile_init------------------------\n");
    InitKernelEnv(); 

    fp = OpenFile(WPS_STA_LIST_FILE, O_RDONLY | O_CREAT, 0);
    filesize = fp->f_op->llseek(fp,0,2) - fp->f_op->llseek(fp,0,0);
    read_buf = kzalloc(filesize, GFP_KERNEL);
	
    if(fp != NULL){ 
        ReadFile(fp, read_buf, filesize);
    }

    CloseFile(fp);

    set_wifi_cali(read_buf, filesize);

    DinitKernelEnv();
    get_wifi_cali(read_buf);
    kfree(read_buf);
    pr_err("---------------------readfile_finish------------------------\n");	
	
    return 0;
}
 
static void __exit readfile_exit(void)
{
    pr_err("read file module remove successfully\n");
}
module_init(readfile_init);
module_exit(readfile_exit);
 
MODULE_DESCRIPTION("read a file in kernel module");
MODULE_LICENSE("GPL");
MODULE_ALIAS("read file module");

