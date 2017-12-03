#include "slave.h"

int main(int argc, char **argv)
{
	printf("slave start...\n\n");

	mail_t *m1 = create_mail_master("apple", "/home/user/col5/os/test_set/a.txt");
	char *q_w, *f_p;
	extract_mail(m1, &q_w, &f_p);
	printf("%s\n%s\n", q_w, f_p);
	// printf("%d", word_count(q_w, f_p));
	FREE(m1);
	m1 = create_mail(word_count(q_w, f_p), f_p);
	printf("%d\n%s\n", m1->data.word_count, m1->file_path);

	printf("\nslave finished\n\n");
}

/*
 * Extract mail into query_word and file_path.
 */
void extract_mail(const mail_t *m, char **q_w, char **f_p)
{
	MALLOC(*q_w, strlen(m->data.query_word) + 1);
	MALLOC(*f_p, strlen(m->file_path) + 1);
	strcpy(*q_w, m->data.query_word);
	strcpy(*f_p, m->file_path);
}

bool open_file(FILE **fin, const char *file_path)
{
	if (!(*fin = fopen(file_path, "r"))) {
		perror(file_path);
		return false;
	} else {
		return true;
	}
}

int word_count(const char* q_w, const char* f_p)
{
	FILE *fin = NULL;
	if (!open_file(&fin, f_p)) {
		return -1;
	}
	int count = 0;
	int len = strlen(q_w);
	char c;
	while (true) {
		int i;
		if ((c = fgetc(fin)) == EOF)
			break;
		if ((char)c != *q_w)
			continue;
		for (i = 1; i < len; ++i) {
			if ((c = fgetc(fin)) == EOF)
				goto end;
			if ((char)c != q_w[i]) {
				fseek(fin, 1 - i, SEEK_CUR);
				goto next;
			}
		}
		++count;
next:
		;
	}
end:
	fclose(fin);
	return count;
}

mail_t *create_mail(const int w_c, const char *f_p)
{
	mail_t *tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	tmp->data.word_count = w_c;
	strncpy(tmp->file_path, f_p, sizeof(tmp->file_path));
	return tmp;
}

#ifdef MAIL_DEBUG // test from master
mail_t *create_mail_master(const char *q_w, const char *f_p)
{
	mail_t *tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	strncpy(tmp->data.query_word, q_w, sizeof(tmp->data.query_word));
	strncpy(tmp->file_path, f_p, sizeof(tmp->file_path));
	return tmp;
}
#endif

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
