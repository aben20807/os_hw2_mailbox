#ifndef SLAVE_H
#define SLAVE_H

#include "mail.h"

void extract_mail(const mail_t *m, char **q_w, char **f_p);
bool open_file(FILE **fin, const char *file_path);
int word_count(const char* q_w, const char* f_p);
mail_t *create_mail(const int w_c, const char *f_p);

#define MAIL_DEBUG
#ifdef MAIL_DEBUG
mail_t *create_mail_master(const char *q_w,
                           const char *f_p); // test from master
#endif

#endif
