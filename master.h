#ifndef MASTER_H
#define MASTER_H

#include "mail.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <linux/limits.h> // PATH_MAX
#include <unistd.h>
#include <signal.h> // kill

// #define _GNU_SOURCE
#define ERRMSG_SIZE 30

#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        fprintf(stderr, "insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
#define CALLOC(p, l, s) \
    if(!((p) = calloc(l, s))){ \
        fprintf(stderr, "insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
#define FREE(p) \
    free(p); \
    p = NULL; \

/*
 * Queue
 * Be used to store all full fullname under target directory.
 */
typedef struct mail_t mail_t;
typedef struct mail_t *mail_ptr;
typedef struct node *node_ptr;
struct node {
	struct mail_t *mail_p;
	struct node *prev;
	struct node *next;
};

typedef struct Queue {
	int count;
	node_ptr head;
	node_ptr tail;
	int (*size)();
	bool (*enq)();
	node_ptr (*deq)();
	bool (*display)();
} Queue;

typedef struct element *element_ptr;
typedef element_ptr List;
struct element {
	pid_t pid;
	element_ptr next;
};

/* Global Variable */
Queue *fullname_queue;
char *query_word;
char *directory;
List slave_list;

/* Queue Function */
void init(Queue **q_ptr);
int size(Queue *self);
bool enq(Queue *self, node_ptr item);
node_ptr deq(Queue *self);
bool display(Queue *self);

mail_ptr create_mail(const char *q_w, const char *f_p);
node_ptr create_node(mail_ptr mail_p);
void listdir(const char *name, int indent);
void create_slave(int num);
void delete_list(const List l);
void print_list(const List l);
void kill_all_slave();

void test_queue();
void test_listdir();

#endif
