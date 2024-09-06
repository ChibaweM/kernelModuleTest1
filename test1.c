#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define DEVICE_NAME "testchar"
#define CLASS_NAME "test"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mkwenya Chibawe");

static int majorNumber;
static int numberOpens = 0;
static short size_of_int;
static long studentNumber = 0;

static struct class* testcharClass = NULL:
static struct device* testcharDevice = NULL;

static int dev_opens(struct inode *, struct file *);
static int dev_release(struct inode *,struct file *);
static ssize_t dev_read(struct file *, char *, size_t,loff_t *);
static ssize_t dev_write(struct file *, const char *,size_t,loff_t *);

static struct file_operations fops =
{
	.open = dev_open,
	.write = dev_write,
	.read = dev_read,
	.release = dev_release,
}


static int __inti test_init(void){
	printk(KERN_INFO "TestChar: Initialising the TestChar LKM \n");

	//Registering a major number
	majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
	if(majorNumber<0){
		printk(KERN_INFO "TestChar: failed to register a major number \n");
		return majorNnumber;
	}
	printk(KERN_INFO "TestChar: register major number %d correctly\n", majorNumber);

	//Registering the device class
	testcharClass = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(testcharClass)){
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to register device class\n");
		return PTR_ERR(testcharClass);
	}
	printk(KERN_INFO "TestChar: device class registered correctly\n");

	//Register the device driver
	testcharDevice device_create(testcharClass, NULL, MKDEV(majorNumber, 0),NULL,DEVICE_NAME);
	if(IS_ERR(testcharDevice)){
		class_destroy(testcharClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ALERT "Failed to create the device\n");
		return PTR_ERR(testcharDevice);
	}
	printk(KERN_INFO "TestChar: device driver registered correctly\n");
	return 0;
}

static void __exit test_exit(void){
	device_destroy(testcharClass, MKDEV(majorNumber, 0));
	class_unregister(testcharClass);
	class_destroy(testcharClass);
	unregister_chrdev(majorNumber, DEVICE_NAME);
	printk(KERN_INFO "TestChar: Goodbye from LKM!\n");
}

static int dev_open(struct inode *inodep,struct file *filep){
	numberOpens++;
	printk(KERN_INFO "TestChar: Device has been opened %d time(s)\n");
	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep){
	printk(KERN_INFO "TestChar: Deviece successfullly closed\n");
	return 0;
}

module_init(test_init);
module_exit(test_exit);
	










































