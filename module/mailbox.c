#include "mailbox.h"

MODULE_LICENSE("Dual BSD/GPL");

static void get_process_name(char *ouput_name);
static ssize_t mailbox_read(struct kobject *kobj,
                            struct kobj_attribute *attr, char *buf);
static ssize_t mailbox_write(struct kobject *kobj,
                             struct kobj_attribute *attr, const char *buf, size_t count);

static struct kobject *hw2_kobject;
static struct kobj_attribute mailbox_attribute
    = __ATTR(mailbox, 0660, mailbox_read, mailbox_write);

static int num_entry_max = 2;

module_param(num_entry_max, int, S_IRUGO);

static void get_process_name(char *ouput_name)
{
	memcpy(ouput_name, current->comm, sizeof(current->comm));
}

static ssize_t mailbox_read(struct kobject *kobj,
                            struct kobj_attribute *attr, char *buf)
{
	printk("call mailbox_read\n");
	return ERR_EMPTY;
}

static ssize_t mailbox_write(struct kobject *kobj,
                             struct kobj_attribute *attr, const char *buf, size_t count)
{
	// mailbox_entry_t *tmp = NULL; // tmp = kmalloc(sizeof(mailbox_entry_t), GFP_KERNEL);
	// tmp->mail_p = kmalloc(sizeof(mailbox_entry_t), GFP_KERNEL);
	// // sscanf(buf, "%du", &tmp->mail_p);
	// memcpy(tmp, buf, sizeof(char) * count);
	// list_add(&tmp->entry, &m_head->head);
	// mail_t *m = (mail_t *)kobj;
	// mail_t *m = NULL;
	// m = to_mail(kobj);
	mail_t *m = kmalloc(sizeof(struct mail_t), GFP_KERNEL);
	// printk("call mailbox_write %ld: %s\n", count, buf);
	// printk("buf siz %ld\n", PAGE_SIZE);
	// m = (struct mail_t *)buf;
	memcpy(m, buf - 64, count);
	printk("mail: %s, %s\n", m->data.query_word, m->file_path);
	// printk("call mailbox_write %s\n", m->file_path);
	// return ERR_FULL;
	return count;
}

static int __init mailbox_init(void)
{
	printk("Insert\n");
	hw2_kobject = kobject_create_and_add("hw2", kernel_kobj);
	sysfs_create_file(hw2_kobject, &mailbox_attribute.attr);
	// INIT_LIST_HEAD(&m_head->head);
	// m_head = kmalloc(sizeof(mailbox_head_t), GFP_KERNEL);
	// m_head->head =
	// INIT_LIST_HEAD(&m_head->head);
	return 0;
}

static void __exit mailbox_exit(void)
{
	printk("Remove\n");
	kobject_put(hw2_kobject);
}

module_init(mailbox_init);
module_exit(mailbox_exit);
