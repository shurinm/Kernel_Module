#include "header/fs_proc.h"

MODULE_LICENSE("GPL");			/* лецензия */
MODULE_AUTHOR("SHURINM");		/* разработчик */

/* запуск модуля */
static int __init initate_module(void)
{
	proc_file_entry = proc_create("proc_file_name", S_IRWXU | S_IRWXG | S_IRWXO, NULL,
				      &proc_file_fops);
	if (proc_file_entry == NULL)
		return -ENOMEM;
	printk(KERN_ALERT "initate_module: initialization complite\n");
	return 0;
}

/* завершение модуля */
static void __exit exit_module(void)
{
	remove_proc_entry("proc_file_name", NULL);
	printk(KERN_ALERT "exit_module: exit complite\n");
}

module_init(initate_module);
module_exit(exit_module);

static int open_proc(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "open_proc: open file\n");
	return 0;
}

static ssize_t write_proc(struct file *filp, const char __user *buffer,
			  size_t length, loff_t *offset)
{
	char recv_msg[SIZE];

	copy_from_user(recv_msg, buffer, length);
	printk(KERN_ALERT "write_proc messagse: %s\n", recv_msg);
	return strlen(recv_msg);
}

static ssize_t read_proc(struct file *filp, char __user *buffer,
			 size_t length, loff_t *offset)
{
	char send_msg[] = "Hello user, I'm kernel!";

	printk(KERN_ALERT "read_proc: user read file\n");
	copy_to_user(buffer, send_msg, strlen(send_msg));
	return strlen(send_msg);
}

static int release_proc(struct inode *inode, struct  file *file)
{
	printk(KERN_ALERT "release_proc: release file\n");
	return 0;
}



