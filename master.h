#ifndef MASTER_H
#define MASTER_H

#include "mail.h"
#include <getopt.h>
#include <ctype.h>
#include <dirent.h>

// #define _GNU_SOURCE
#define ERRMSG_SIZE 30

/* Global Variable */
Queue *fullname_queue;
char *query_word;
char *directory;
List slave_list;

/* Queue Function */
void init(Queue **q_ptr);
int size(Queue *self);
bool enq(Queue *self, node *item);
node *deq(Queue *self);
bool display(Queue *self);

mail_t *create_mail(const char *q_w, const char *f_p);
node *create_node(mail_t *mail_p);
void listdir(const char *name, int indent);
void create_slave(int num);
void delete_list(const List l);
void print_list(const List l);
void kill_all_slave();
void notify_all_slave(const List l);
void send_all_mail();

void test_queue();
void test_listdir();

#endif
