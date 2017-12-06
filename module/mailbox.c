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
	int each_count = 0;
	struct list_head *iter = NULL;
	mailbox_entry_t *curr = NULL;
	printk("call mailbox_read\n");
	if (m_head->count == 0) {
		printk("ERR_FULL: %d\n", ERR_FULL);
		return ERR_EMPTY;
	} else {
		list_for_each(iter, &m_head->head) {
			if (each_count == m_head->count - 1) {
				curr = list_entry(iter, struct mailbox_entry_t, entry);
				printk("mail: %s, %s\n", curr->mail_p->data.query_word,
				       curr->mail_p->file_path);
				memcpy(buf, curr->mail_p, 32 + strlen(curr->mail_p->file_path));
				break;
			}
			each_count++;
		}
		m_head->count--;
		printk("size: %ld\n", 32 + strlen(curr->mail_p->file_path));
		return 32 + strlen(curr->mail_p->file_path);
	}
}

static ssize_t mailbox_write(struct kobject *kobj,
                             struct kobj_attribute *attr, const char *buf, size_t count)
{
	mail_t *mail;
	struct list_head *iter;
	mailbox_entry_t *curr;
	if (m_head == NULL) {
		m_head = kmalloc(sizeof(struct mailbox_head_t), GFP_KERNEL);
		INIT_LIST_HEAD(&m_head->head);
		m_head->count = 0;
		for (int i = 0; i < num_entry_max; i++) {
			mailbox_entry_t *m_entry = kmalloc(sizeof(struct mailbox_entry_t), GFP_KERNEL);
			m_entry->mail_p = NULL;
			list_add(&m_entry->entry, &m_head->head);
		}
	}
	if (m_head->count < num_entry_max) {
		mail = kmalloc(sizeof(struct mail_t), GFP_KERNEL);
		memcpy(mail, buf, count);
		// printk("size: %ld, %d\n", strlen(buf), (int)count);
		printk("mail: %s, %s\n", mail->data.query_word, mail->file_path);
		if (mail != NULL) {
			int each_count = 0;
			list_for_each(iter, &m_head->head) {
				if (each_count == m_head->count) {
					curr = list_entry(iter, struct mailbox_entry_t, entry);
					curr->mail_p = mail;
				}
				each_count++;
			}
			m_head->count++;
		}
	} else {
		printk("ERR_FULL: %d\n", ERR_FULL);
		return ERR_FULL;
	}
	printk("In list:\n");
	list_for_each(iter, &m_head->head) {
		curr = list_entry(iter, struct mailbox_entry_t, entry);
		if (curr->mail_p != NULL) {
			printk("mail: %s, %s\n", mail->data.query_word, mail->file_path);
		}
	}
	printk("\n");
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
