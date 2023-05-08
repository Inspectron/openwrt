#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/reboot.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/sysrq.h>
#include <linux/delay.h>

static char *cmdline1[] = { "/bin/umount", "/overlay", NULL };
static char *cmdline2[] = { "/sbin/jffs2reset", NULL };
static char *cmdline3[] = { "/bin/sh", "-c", "echo b > /proc/sysrq-trigger", NULL };
static char *cmdline4[] = { "/bin/sh", "-c", "touch /etc/boot_was_not_ok", NULL };
static char *cmdline5[] = { "/bin/sh", "-c", "touch /etc/reset_performed", NULL };

static char file1path[] = "/etc/boot_was_not_ok";
static char file2path[] = "/etc/reset_performed";

static int __init bootcheck_init(void)
{
    char message[128];
    struct file *f1, *f2;
    int ret = 0;

    sprintf(message, "=== bootcheck: module init  ===\n");
    printk(KERN_INFO "%s", message);
    ret = call_usermodehelper(cmdline2[0], cmdline2, NULL, UMH_WAIT_EXEC);
    printk(KERN_INFO "=== bootcheck: module loaded ===\n");
    return 0;

    //msleep(5000);

    //f1 = filp_open(file1path, O_RDONLY, 0);
    //printk(KERN_INFO "=== /etc/boot_was_not_ok open(): %ld ===\n", PTR_ERR(f1));

    //f2 = filp_open(file2path, O_RDONLY, 0);
    //printk(KERN_INFO "=== /etc/reset_performed open(): %ld ===\n", PTR_ERR(f2));

    // if (!IS_ERR(f1))
    if (PTR_ERR(f1) != -2)
    {
        //if (IS_ERR(f2))
        if (PTR_ERR(f2) == -2)
        {
            sprintf(message, "=== Previous boot was not OK, resetting the device ===\n");
            printk(KERN_INFO "%s", message);

            // Unmount overlay and reset JFFS2 partition
            ret = call_usermodehelper(cmdline1[0], cmdline1, NULL, UMH_WAIT_EXEC);
            if (ret < 0)
            {
                printk(KERN_INFO "=== Failed to execute command umount /overlay: %d ===\n", ret);
            }

            ret = call_usermodehelper(cmdline2[0], cmdline2, NULL, UMH_WAIT_EXEC);
            if (ret < 0)
            {
                printk(KERN_INFO "=== Failed to execute command jffs2reset: %d ===\n", ret);
            }
            else
            {
                // Create a flag file about reset
                // f2 = filp_open(file2path, O_CREAT | O_RDWR, 0666);
                // filp_close(f2, NULL);
                ret = call_usermodehelper(cmdline5[0], cmdline5, NULL, UMH_WAIT_EXEC);
                if (ret < 0)
                {
                    printk(KERN_INFO "=== Failed to execute touch reset_performed: %d ===\n", ret);
                }

                // Reboot
                ret = call_usermodehelper(cmdline3[0], cmdline3, NULL, UMH_WAIT_EXEC);
                if (ret < 0)
                {
                    printk(KERN_ERR "=== Failed to write to /proc/sysrq-trigger\n ===");
                }
                else
                {
                    printk(KERN_INFO "=== Restarting ===\n");
                }
            }
        }
        else
        {
            sprintf(message, "=== Reset WAS on previous boot ===\n");
            printk(KERN_INFO "%s", message);

            // /etc/boot_was_not_ok file should be there, no need to create it.
            // But let's create it, just in case the current boot won't be good.
            // f1 = filp_open(file1path, O_CREAT | O_RDWR, 0666);
            // filp_close(f1, NULL);
            ret = call_usermodehelper(cmdline4[0], cmdline4, NULL, UMH_WAIT_EXEC);
            if (ret < 0)
            {
                printk(KERN_INFO "=== Failed to execute touch boot_was_not_okay: %d ===\n", ret);
            }
        }
    }
    else
    {
        sprintf(message, "=== Previous boot was OK =====\n");
        printk(KERN_INFO "%s", message);

        // Create /etc/boot_was_not_ok file
        ret = call_usermodehelper(cmdline4[0], cmdline4, NULL, UMH_WAIT_EXEC);
        if (ret < 0)
        {
            printk(KERN_INFO "=== Failed to execute touch boot_was_not_okay: %d ===\n", ret);
        }

        //f1 = filp_open(file1path, O_CREAT | O_RDWR, 0666);
        //filp_close(f1, NULL);
    }

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
MODULE_VERSION("0.1");
