#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>


static struct proc_dir_entry *entry;

static int proc_count(struct seq_file *m, void *v){
        int count;
	count=0;
        struct task_struct *p;
	for_each_process(p) {
	   count=count+1;
	}
        seq_printf(m,"%d\n",count);
	return 0;
}


static int __init proc_count_init(void)
{
        entry = proc_create_single("count",0,NULL,proc_count);
	pr_info("proc_count: init\n");
	return 0;
}

static void __exit proc_count_exit(void)
{
        proc_remove(entry);
	pr_info("proc_count: exit\n");
}

module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Aditya Mehta");
MODULE_DESCRIPTION("Counts the number of processes running on the machine");
MODULE_LICENSE("GPL");
