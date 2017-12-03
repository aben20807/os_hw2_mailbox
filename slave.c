#include "slave.h"

int main(int argc, char **argv)
{
	printf("slave start...\n\n");
	mail_t *m1 = create_mail("d", "p");
	char *q_w, *f_p;
	extract_mail(m1, &q_w, &f_p);
	printf("%s\n%s\n", q_w, f_p);
	while (1) {}
	printf("\nslave finished\n\n");
}

void extract_mail(const mail_t *m, char **q_w, char **f_p)
{
	CALLOC(*q_w, strlen(m->data.query_word), sizeof(char));
	CALLOC(*f_p, strlen(m->file_path), sizeof(char));
	// mail_t *tmp = NULL;
	// CALLOC(tmp, sizeof(*tmp), 1);
	*q_w = m->data.query_word;
	*f_p = m->file_path;
	// strncpy(*q_w, m->data.query_word, sizeof(m->data.query_word));
	// strncpy(*f_p, m->file_path, sizeof(m->file_path));
}

mail_t *create_mail(const char *q_w, const char *f_p) // test from master
{
	mail_t *tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	strncpy(tmp->data.query_word, q_w, sizeof(tmp->data.query_word));
	strncpy(tmp->file_path, f_p, sizeof(tmp->file_path));
	return tmp;
}

int send_to_fd(int sysfs_fd, struct mail_t *mail)
{
	/*
	 * write something or nothing
	 */

	// int ret_val = write(sysfs_fd, ...);
	// if (ret_val == ERR_FULL) {
	//     /*
	//      * write something or nothing
	//      */
	// } else {
	//     /*
	//      * write something or nothing
	//      */
	// }

	/*
	 * write something or nothing
	 */
	return 0;
}

int receive_from_fd(int sysfs_fd, struct mail_t *mail)
{
	/*
	 * write something or nothing
	 */

	// int ret_val = read(sysfs_fd, ...);
	// if (ret_val == ERR_EMPTY) {
	//     /*
	//      * write something or nothing
	//      */
	// } else {
	//     /*
	//      * write something or nothing
	//      */
	// }

	/*
	 * write something or nothing
	 */
	return 0;
}
