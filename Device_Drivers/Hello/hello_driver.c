#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HARI SINGH");
MODULE_DESCRIPTION("Hello Program");

static int __init driver_init(void)
{
  printk(KERN_INFO "Hello, Driver is Loaded\n");
  return 0;
}

static void __exit driver_exit(void) {
    printk(KERN_INFO "Goodbye, World! My driver is unloaded.\n");
}

// Register the entry and exit points
module_init(driver_init);
module_exit(driver_exit);
