#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEV_NAME "mychardev"
#define BUF_SIZE 4096

static int major;
static char kbuf[BUF_SIZE];
static size_t data_len = 0;

static int my_open(struct inode *inode, struct file *file){
	pr_info(DEV_NAME ": Open\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file){
	pr_info(DEV_NAME ": release\n");
	return 0;
}

static ssize_t my_read(struct file *file, char __user *ubuf, size_t len, loff_t *ppos){
	size_t available;
	size_t to_copy;

	if(*ppos >= data_len)
		return 0;
	
	available = data_len - *ppos;
	to_copy = (len < available) ? len : available;

	if(copy_to_user(ubuf, kbuf + *ppos, to_copy))
		return -EFAULT;

	*ppos += to_copy;
	pr_info(DEV_NAME ": read %zu bytes (pos=%lld)\n", to_copy, *ppos);
	return to_copy;
}

static ssize_t my_write(struct file *file, const char __user *ubuf, size_t len, loff_t *ppos){
	size_t space = BUF_SIZE - *ppos;
	size_t to_copy;

	if(len == 0)
		return 0;
	if(*ppos >= BUF_SIZE)
		return -ENOSPC;
	to_copy = (len < space) ? len : space;

	if(copy_from_user(kbuf + *ppos, ubuf, to_copy))
		return -EFAULT;

	*ppos += to_copy;
	if(*ppos > data_len)
		data_len = *ppos;

	pr_info(DEV_NAME "wrote %zu bytes (pos=%lld, data_len=%zu)\n", to_copy, *ppos, data_len);
	return to_copy;
}

static loff_t my_llseek(struct file *file, loff_t off, int whence){
	loff_t newpos;

	switch(whence){
		case SEEK_SET: newpos = off;
			       break;
		case SEEK_CUR: newpos = file->f_pos + off;
			       break;
		case SEEK_END: newpos = data_len + off;
			       break;
		default:
			       return -EINVAL;
	}

	if(newpos <0 || newpos > BUF_SIZE)
		return -EINVAL;
	file->f_pos = newpos;
	return newpos;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_release,
	.read = my_read,
	.write = my_write,
	.llseek = my_llseek,
};

static int __init my_init(void){
	major = register_chrdev(0, DEV_NAME, &my_fops);
	
	if(major < 0){
		pr_err(DEV_NAME ": Register_Chrdev failed: %d\n", major);
		return major;
	}

	data_len = 0;
	pr_info(DEV_NAME ": loaded. major=%d\n", major);
	pr_info(DEV_NAME ": create node with: mknod /dev/%s c %d 0 && chmod 666 /dev/%s\n", DEV_NAME, major, DEV_NAME);
	return  0;
}

static void __exit my_exit(void){
	unregister_chrdev(major, DEV_NAME);
	pr_info(DEV_NAME ": unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YOU");
MODULE_DESCRIPTION("Simple /dev/mychardev using register_chrdev");
module_init(my_init);
module_exit(my_exit);

