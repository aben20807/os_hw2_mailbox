#ifndef MASTER_H
#define MASTER_H

#include "mail.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>

#define _GNU_SOURCE
#define ERRMSG_SIZE 30

typedef struct mail_t *mail_ptr;
typedef mail_ptr Queue;
Queue fullname_queue;

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


void listdir(const char *name, int indent);

#endif
