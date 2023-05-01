#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/reboot.h>
#include <linux/syscalls.h>
#include <linux/module.h>


static char *cmdline1[] = { "/bin/umount", "/overlay", NULL };
static char *cmdline2[] = { "/sbin/jffs2reset", NULL };

static int __init bootcheck_init(void)
{
    char message[128];
    struct file *f;
    int ret = 0;
    int fd;

    sprintf(message, "=== Checking previous boot ... ===\n");
    printk(KERN_INFO "%s", message);

    f = filp_open("/etc/bootok", O_RDONLY, 0);

    if (IS_ERR(f))
    {
        sprintf(message, "=== Previous boot was not OK, resetting the device ===\n");
        printk(KERN_INFO "%s", message);

        // Create /etc/bootok file
        fd = sys_open("/etc/bootok", O_CREAT | O_RDWR, 0666);
        sys_close(fd);

        // Unmount overlay and reset JFFS2 partition
        ret = call_usermodehelper(cmdline1[0], cmdline1, NULL, UMH_WAIT_EXEC);
        if (ret < 0) {
            printk(KERN_INFO "=== Failed to execute command umount /overlay: %d ===\n", ret);
        }

        ret = call_usermodehelper(cmdline2[0], cmdline2, NULL, UMH_WAIT_EXEC);
        if (ret < 0) {
            printk(KERN_INFO "=== Failed to execute command jffs2reset: %d ===\n", ret);
        }
        else
        {
            // Reboot
            sprintf(message, "=== Restarting ===\n");
            printk(KERN_INFO "%s", message);
            kernel_restart(NULL);
        }
    }
    else
    {
        filp_close(f, NULL);
        sprintf(message, "===== Previous boot was OK =====\n");
        printk(KERN_INFO "%s", message);

        // Remove /etc/bootok file 
        sys_unlink("/etc/bootok");
    }

    return 0;
}

static void __exit bootcheck_exit(void)
{
    printk(KERN_INFO "bootcheck  has been unloaded\n");
}

module_init(bootcheck_init);
module_exit(bootcheck_exit);

MODULE_LICENSE("Commercial");
MODULE_AUTHOR("Nick Arapau, Inspectron");
MODULE_DESCRIPTION("Bootcheck kernel module");
MODULE_VERSION("0.1");
