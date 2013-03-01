#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

static unsigned int wlan_keepalive = 30;

module_param(wlan_keepalive, uint, 0644);


static ssize_t keepalive_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	return sprintf(buf, "%d\n", wlan_keepalive);
}
	
static ssize_t keepalive_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count)
{
	sscanf(buf, "%du", &wlan_keepalive);
	return count;
}

static struct kobj_attribute keepalive_attribute =
	__ATTR(wlan_keepalive, 0666, keepalive_show, keepalive_store);

static struct attribute *attrs[] = {
	&keepalive_attribute.attr,
	NULL,	/* need to NULL terminate the list of attributes */
};
	
static struct attribute_group attr_group = {
	.attrs = attrs,
};
	
static struct kobject *ath6kl_kobj;
	
static int __init kobj_init(void)
{
	int retval;
	pr_err("---------------------kobj_init------------------------\n");

	ath6kl_kobj = kobject_create_and_add("ath6kl", kernel_kobj);
	if (!ath6kl_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(ath6kl_kobj, &attr_group);
	if (retval)
		kobject_put(ath6kl_kobj);

	return retval;
}
	
static void __exit kobj_exit(void)
{
	pr_err("---------------------kobj_exit------------------------\n");
	kobject_put(ath6kl_kobj);
}

int get_keepalive(void){
	return wlan_keepalive;
}

EXPORT_SYMBOL(get_keepalive);

module_init(kobj_init);
module_exit(kobj_exit);
MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
