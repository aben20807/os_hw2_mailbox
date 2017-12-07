#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <linux/limits.h> // PATH_MAX
#include <fcntl.h> // open
#include <unistd.h> // lseek, execl
#include <signal.h> // kill
#include <sys/wait.h>

#define ERR_EMPTY -1
#define ERR_FULL -2

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
    if(p != NULL){ \
        free(p); \
        p = NULL; \
    }

typedef struct mail_t mail_t;

/*
 * Queue
 * Be used to store all full fullname under target directory.
 */
typedef struct node {
	struct mail_t *mail_p;
	struct node *prev;
	struct node *next;
} node;

typedef struct Queue {
	int count;
	node *head;
	node *tail;
	int (*size)();
	bool (*enq)();
	node *(*deq)();
	bool (*display)();
} Queue;

typedef struct element element;
typedef element *List;
struct element {
	pid_t pid;
	element *next;
};

#endif
