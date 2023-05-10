#include <linux/module.h>

static char *cmdline[] = { "/sbin/jffs2reset", NULL };

static int __init bootcheck_init(void)
{
    int ret = 0;

    printk(KERN_INFO "=== bootcheck: module init  ===\n");
    ret = call_usermodehelper(cmdline[0], cmdline, NULL, UMH_WAIT_EXEC);
    printk(KERN_INFO "=== bootcheck: module loaded ===\n");
    return 0;
}

static void __exit bootcheck_exit(void)
{
    printk(KERN_INFO "=== bootcheck: unloaded ===\n");
}

module_init(bootcheck_init);
module_exit(bootcheck_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nick Arapau, Inspectron");
MODULE_DESCRIPTION("Bootcheck kernel module");
MODULE_VERSION("0.2");
