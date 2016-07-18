#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Praveen ");
static unsigned int gpioLED=29;
static bool ledOn =0;
static int __init LedDriver_init(void)
{
	int result =0;
	printk(KERN_INFO " LedControl Intialisation\n");
	if(!gpio_is_valid(gpioLED))
	{
		printk(KERN_INFO" Invalid GPIO\n");
		return -ENODEV;
	}
	ledOn = 1;
	gpio_request(gpioLED,"sysfs");
	gpio_direction_output(gpioLED,ledOn);
	gpio_export(gpioLED,1);
	printk(KERN_INFO" Led Driver Created Succesfully");

}
static void __exit LedDriver_exit(void)
{
	gpio_set_value(gpioLED,0);
	gpio_unexport(gpioLED);
	gpio_free(gpioLED);
	printk(KERN_INFO,"Leaving Led control \n");
}
module_init(LedDriver_init);
module_exit(LedDriver_exit);
