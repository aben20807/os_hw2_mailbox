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
	mail_t *m;
	struct list_head *iter;
	mailbox_entry_t *tmp;
	if (m_head == NULL) {
		m_head = kmalloc(sizeof(struct mailbox_head_t), GFP_KERNEL);
		INIT_LIST_HEAD(&m_head->head);
	}
	m = kmalloc(sizeof(struct mail_t), GFP_KERNEL);
	memcpy(m, buf - 64, count); // mysterious power number: 64
	printk("mail: %s, %s\n", m->data.query_word, m->file_path);
	if (m != NULL) {
		mailbox_entry_t *m_entry = kmalloc(sizeof(struct mailbox_entry_t), GFP_KERNEL);
		m_entry->mail_p = m;
		list_add(&m_entry->entry, &m_head->head);
	}
	printk("In list:\n");
	list_for_each(iter, &m_head->head) {
		tmp = list_entry(iter, struct mailbox_entry_t, entry);
		printk("%s\n", tmp->mail_p->file_path);
	}
	printk("\n");
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
	m_head = NULL;
	return 0;
}

static void __exit mailbox_exit(void)
{
	printk("Remove\n");
	kobject_put(hw2_kobject);
}

module_init(mailbox_init);
module_exit(mailbox_exit);
