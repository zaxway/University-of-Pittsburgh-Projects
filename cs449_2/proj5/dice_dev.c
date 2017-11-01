/*
 * "dice, world!" minimal kernel module - /dev version
 *
 * Mohit Jain <moj10@pitt.edu>
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>

#include <asm/uaccess.h>

/*
 * dice_read is the function called when a process calls read() on
 * /dev/dice.  It writes "dice, world!" to the buffer passed in the
 * read() call.
 */


static ssize_t dice_read(struct file * file, char * buf,
			  size_t count, loff_t *ppos)
{

	// unsigned char mybuf;
	// int d;
	// for (d = count; count != 0; count--) {
	//     get_random_bytes(&mybuf, sizeof(char));
	//     mybuf = mybuf %6;
	//     copy_to_user(buf, &mybuf, sizeof(char));
	//     buf++;
	// }
	int i;
	unsigned char mybuf[32];
	int d;
	int tmp;
	tmp = count;

	while (tmp > 0) {
		get_random_bytes(mybuf, sizeof(mybuf)); // contains 32 random bytes

		for (i = 0; i < sizeof(mybuf); i++) {
			mybuf[i] = mybuf[i] % 6;
		}
		copy_to_user(buf, &mybuf, sizeof(mybuf));
		tmp = tmp - 32;
	}

	if (tmp <= sizeof(mybuf) && tmp != 0) {
		get_random_bytes(mybuf, tmp); // contains tmp random bytes

		for (d = tmp; d != 0; d--) {
			mybuf[i] = mybuf[i] % 6;
		}
		copy_to_user(buf, &mybuf, tmp);
	}

	/*
	 * We only support reading the whole string at once.
	 */
	// if (count < len)
	// 	return -EINVAL;
	/*
	 * If file position is non-zero, then assume the string has
	 * been read and indicate there is no more data to be read.
	 */
	// if (*ppos != 0)
	// 	return 0;
	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	// if (copy_to_user(buf, &dice_str, len))
	// 	return -EINVAL;
	/*
	 * Tell the user how much data we wrote.
	 */
	*ppos = *ppos + count;

 	return count;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations dice_fops = {
	.owner		= THIS_MODULE,
	.read		= dice_read,
};

static struct miscdevice dice_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/dice.
	 */
	"dice",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&dice_fops
};

static int __init
dice_init(void)
{
	int ret;

	/*
	 * Create the "dice" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/dice device using
	 * the default rules.
	 */
	ret = misc_register(&dice_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"dice, world!\" misc device\n");

	return ret;
}

module_init(dice_init);

static void __exit
dice_exit(void)
{
	misc_deregister(&dice_dev);
}

module_exit(dice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mohit Jain <moj10@pitt.edu>");
MODULE_DESCRIPTION("\"dice, world!\" minimal module");
MODULE_VERSION("dev");
