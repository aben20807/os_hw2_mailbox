#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <linux/limits.h> // PATH_MAX

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
    free(p); \
    p = NULL;

typedef struct mail_t mail_t;

#endif
