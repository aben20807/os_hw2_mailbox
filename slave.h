#ifndef SLAVE_H
#define SLAVE_H

#include "mail.h"
#include <ctype.h>

/* Global Variable */
Queue *wordcount_queue;
bool master_send_done;

void extract_mail(mail_t *m, char **q_w, char **f_p);
bool open_file(FILE **fin, const char *file_path);
int word_count(char* q_w, const char* f_p);
bool is_delimiter(const char c);
mail_t *create_mail(const int w_c, char *f_p);
node *create_node(mail_t *mail_p);
void handler(int signum);
void send_all_mail();

/* Queue Function */
void init(Queue **q_ptr);
int size(Queue *self);
bool enq(Queue *self, node *item);
node *deq(Queue *self);
bool display(Queue *self);

#define MAIL_DEBUG
#ifdef MAIL_DEBUG
mail_t *create_mail_master(const char *q_w,
                           const char *f_p); // test from master
#endif

#endif
