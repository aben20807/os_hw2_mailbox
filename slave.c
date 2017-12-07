#include "slave.h"

int main(int argc, char **argv)
{
	printf("slave start...\n\n");

	signal(SIGUSR1, handler);
	init(&wordcount_queue);
	master_send_done = false;
	mail_t *mail = NULL;
	while (true) {
		CALLOC(mail, sizeof(*mail), 1);
		int sysfs_fd = open("/sys/kernel/hw2/mailbox", O_RDONLY);
		if (receive_from_fd(sysfs_fd, mail) != ERR_EMPTY) {
			// printf("mail: %s, %s\n", mail->data.query_word, mail->file_path);
			char *q_w, *f_p;
			extract_mail(mail, &q_w, &f_p);
			// printf("from m: \n%s\n%s\n", q_w, f_p);
			int w_c = word_count(q_w, f_p);
			printf("count: %d\n\n", w_c);
			// create_mail(w_c, f_p);
			node *tmp = create_node(create_mail(w_c, f_p));
			wordcount_queue->enq(wordcount_queue, tmp);
		} else {
			if (master_send_done) break;
		}
		close(sysfs_fd);
		FREE(mail);
	}
	wordcount_queue->display(wordcount_queue);

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

node *create_node(mail_t *mail_p)
{
	node *tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	tmp->mail_p = mail_p;
	tmp->prev = NULL;
	tmp->next = NULL;
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
	// printf("write mail: %s, %s\n", mail->data.query_word, mail->file_path);
	lseek(sysfs_fd, 0, SEEK_SET);
	int ret_val = write(sysfs_fd, mail, sizeof(*mail));
	if (ret_val < 0) {
		// printf("ERR_FULL\n");
		return ERR_FULL;
	} else {
		printf("write mail: %s, %s\n", mail->data.query_word, mail->file_path);
		// printf("count: %zd\n", (ssize_t)ret_val);
		return ret_val;
	}
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

void handler(int signum)
{
	if (signum == SIGUSR1) {
		master_send_done = true;
		printf("Received SIGUSR1!\n");
	}
}

void init(Queue **q_ptr)
{
	Queue *q = NULL;
	MALLOC(q, sizeof(Queue));
	q->count = 0;
	q->head = NULL;
	q->tail = NULL;
	q->size = size;
	q->enq = enq;
	q->deq = deq;
	q->display = display;
	*q_ptr = q;
}

int size(Queue *self)
{
	return self->count;
}

/*
 * Insert a node which cantains a mail_t into queue at head.
 */
bool enq(Queue *self, node *item)
{
	if ((self == NULL) || (item == NULL)) {
		return false;
	}
	if (self->size(self) == 0) {
		self->head = item;
		self->tail = item;
	} else {
		self->head->prev = item;
		item->next = self->head;
		self->head = item;
	}
	self->count++;
	return true;
}

/*
 * Remove a node which cantains a mail_t from queue at tail.
 */
node *deq(Queue *self)
{
	if ((self == NULL) || self->size(self) == 0) {
		printf("0\n");
		return NULL;
	}
	node *tmp = self->tail;
	if (self->size(self) != 1) {
		self->tail = self->tail->prev;
		self->tail->next = NULL;
	} else {
		self->tail = self->head;
		self->count = 0;
		return tmp;
	}
	self->count--;
	return tmp;
}

/*
 * Display all nodes in queue from head to tail.
 */
bool display(Queue *self)
{
	if (self == NULL || self->size(self) == 0) {
		return false;
	}
	printf("head->\n");
	node *curr = self->head;
	int count = 0;
	while (curr != NULL) {
		printf("%d:\n%d\n%s\n", count++, curr->mail_p->data.word_count,
		       curr->mail_p->file_path);
		curr = curr->next;
	}
	printf("<-tail\n");
	return true;
}
