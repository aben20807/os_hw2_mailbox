#ifndef SLAVE_H
#define SLAVE_H

#include "mail.h"

void extract_mail(const mail_t *m, char **q_w, char **f_p);
mail_t *create_mail(const char *q_w, const char *f_p); // test from master

#endif
