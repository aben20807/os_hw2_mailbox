#include "slave.h"

int main(int argc, char **argv)
{
	printf("slave start...\n\n");

	// mail_t *m1 = create_mail_master("apple", "/home/user/col5/os/test_set/a.txt");
	// char *q_w, *f_p;
	// extract_mail(m1, &q_w, &f_p);
	// printf("from m: %s\n%s\n", q_w, f_p);
	// // printf("%d", word_count(q_w, f_p));
	// m1 = create_mail(word_count(q_w, f_p), f_p);
	// printf("from s: %d\n%s\n", m1->data.word_count, m1->file_path);

	// int sysfs_fd = open("/sys/kernel/hw2/mailbox", O_RDONLY);
	// mail_t *mail = NULL;
	// CALLOC(mail, sizeof(*mail), 1);
	// while (receive_from_fd(sysfs_fd, mail) != ERR_EMPTY) {
	//     // printf("mail: %s, %s\n", mail->data.query_word, mail->file_path);
	//     char *q_w, *f_p;
	//     extract_mail(mail, &q_w, &f_p);
	//     printf("from m: \n%s\n%s\n", q_w, f_p);
	//     printf("count: %d\n\n", word_count(q_w, f_p));
	// }
	// close(sysfs_fd);

	// int i = 0;
	mail_t *mail = NULL;
	while (true) {
		CALLOC(mail, sizeof(*mail), 1);
		int sysfs_fd = open("/sys/kernel/hw2/mailbox", O_RDONLY);
		if (receive_from_fd(sysfs_fd, mail) != ERR_EMPTY) {
			// printf("mail: %s, %s\n", mail->data.query_word, mail->file_path);
			char *q_w, *f_p;
			extract_mail(mail, &q_w, &f_p);
			printf("from m: \n%s\n%s\n", q_w, f_p);
			printf("count: %d\n\n", word_count(q_w, f_p));
		}
		close(sysfs_fd);
		FREE(mail);
	}
	printf("\nslave finished\n\n");
}

/*
 * Extract mail into query_word and file_path.
 */
void extract_mail(mail_t *m, char **q_w, char **f_p)
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

/*
 * Count number of words in file form file_path.
 */
int word_count(char *q_w, const char *f_p)
{
	FILE *fin = NULL;
	if (!open_file(&fin, f_p)) {
		return -1;
	}
	int count = 0;
	int len = strlen(q_w);
	char c, cl;
	while (true) {
		int i;
		if ((c = fgetc(fin)) == EOF) {
			break;
		}
		if (c >= 'A' && c <= 'Z') {
			c -= ('A' - 'a');
		}
		if (c != *q_w) {
			cl = c;
			continue;
		}
		for (i = 1; i < len + 1; i++) {
			if ((c = fgetc(fin)) == EOF)
				goto end;
			if (i == len && !is_delimiter(c)) {
				count--;
			}
			if (c != q_w[i] || !is_delimiter(cl)) {
				if (i == len)
					goto count;
				fseek(fin, 1 - i, SEEK_CUR);
				goto next;
			}
		}
count:
		count++;
next:
		;
	}
end:
	fclose(fin);
	FREE(q_w);
	return count;
}

bool is_delimiter(const char c)
{
	return (c == ',' || c == '.' || c == '!' || c == '?' || c == ' ' || c == '\n');
}

mail_t *create_mail(const int w_c, char *f_p)
{
	mail_t *tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	tmp->data.word_count = w_c;
	strncpy(tmp->file_path, f_p, sizeof(tmp->file_path));
	FREE(f_p);
	return tmp;
}

/*
 * Test as get mail from master.
 */
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
	// printf("read\n");
	lseek(sysfs_fd, 0, SEEK_SET);
	int ret_val = read(sysfs_fd, mail, sizeof(*mail));
	// printf("mail: %s, %s\n", mail->data.query_word, mail->file_path);
	if (ret_val < 0) {
		// printf("ERR_EMPTY\n");
		return ERR_EMPTY;
	} else {
		// printf("count: %zd\n", (ssize_t)ret_val);
		return ret_val;
	}
}
