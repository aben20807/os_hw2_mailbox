#ifndef MAILBOX_H
#define MAILBOX_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/fs.h>
#include <linux/spinlock_types.h>
#include <linux/slab.h> // kmalloc

#define ERR_EMPTY -1
#define ERR_FULL -2

#define to_mail(x) container_of(x, struct mail_t, kobj)

typedef struct mailbox_head_t mailbox_head_t;
struct mailbox_head_t {
	struct list_head head;
};
mailbox_head_t *m_head;

typedef struct mailbox_entry_t mailbox_entry_t;
struct mailbox_entry_t {
	struct mail_t *mail_p;
	struct list_head entry;
};

typedef struct mail_t mail_t;
struct mail_t {
	struct kobject kobj;
	union {
		char query_word[32];
		unsigned int word_count;
	} data;
	char file_path[4096];
};

#endif
