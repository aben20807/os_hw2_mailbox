#include "master.h"

int main(int argc, char **argv)
{
	printf("master start...\n\n");
	char *query_word = NULL;
	char *directory = NULL;
	int num_slave = 1;
	char arg;
	while ((arg = getopt(argc, argv, "q:d:s:")) != -1) {
		switch (arg) {
		case 'q':
			query_word = optarg;
			break;
		case 'd':
			directory = optarg;
			break;
		case 's':
			num_slave = atoi(optarg);
			break;
		case '?':
			if (optopt == 'c')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			abort();
		}
	}
	printf("query_word: %s\n", query_word);
	printf("directory: %s\n", directory);
	printf("num_slave: %d\n", num_slave);
	// listdir(directory, 0);
	Queue *q = NULL;
	init(&q);
	// printf("%d\n", q->count);
	printf("%d\n", q->size(q));
	mail_t m = {{"a"}, "p"};
	mail_t m2 = {{"b"}, "u"};
	mail_t m3 = {{"c"}, "t"};
	// printf("%s, %s\n", m.data.query_word, m.file_path);
	// q->enq(q, &m);
	// printf("%d\n", q->size(q));
	// mail_t m2 = {{"b"}, "u"};
	// printf("%s, %s\n", m2.data.query_word, m2.file_path);
	// q->enq(q, &m2);
	// printf("%d\n", q->size(q));
	// node_ptr p = q->deq(q);
	// printf("%s, %s\n", p->mail.data.query_word, p->mail.file_path);
	// printf("%d\n", q->size(q));
	// p = q->deq(q);
	// printf("%s, %s\n", p->mail.data.query_word, p->mail.file_path);
	// printf("%d\n", q->size(q));
	// printf("\nmaster finished\n\n");

	node_ptr np = (node_ptr)create_node(&m);
	printf("%s, %s\n", np->mail_p->data.query_word, np->mail_p->file_path);
	q->enq(q, np);
	printf("%d\n", q->size(q));

	np = (node_ptr)create_node(&m2);
	printf("%s, %s\n", np->mail_p->data.query_word, np->mail_p->file_path);
	q->enq(q, np);
	printf("%d\n", q->size(q));

	np = q->deq(q);
	printf("%s, %s\n", np->mail_p->data.query_word, np->mail_p->file_path);
	printf("%d\n", q->size(q));

	np = (node_ptr)create_node(&m3);
	printf("%s, %s\n", np->mail_p->data.query_word, np->mail_p->file_path);
	q->enq(q, np);
	printf("%d\n", q->size(q));

	np = q->deq(q);
	printf("%s, %s\n", np->mail_p->data.query_word, np->mail_p->file_path);
	printf("%d\n", q->size(q));

	np = q->deq(q);
	printf("%s, %s\n", np->mail_p->data.query_word, np->mail_p->file_path);
	printf("%d\n", q->size(q));
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
	*q_ptr = q;
}

int size(Queue *self)
{
	return self->count;
}

bool enq(Queue *self, node_ptr item)
{
	if ((self == NULL) || (item == NULL)) {
		return false;
	}
	if (self->size(self) == 0) {
		self->head = item;
		self->tail = item;
	} else {
		self->head->prev = item;
		self->head = item;
	}
	self->count++;
	return true;
}

node_ptr deq(Queue *self)
{
	if ((self == NULL) || self->size(self) == 0) {
		return NULL;
	}
	node_ptr tmp = self->tail;
	self->tail = self->tail->prev;
	self->count--;
	return tmp;
}

node_ptr create_node(mail_ptr mail_p)
{
	node_ptr tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	CALLOC(tmp->mail_p, sizeof(tmp->mail_p), 1);
	tmp->mail_p = mail_p;
	return tmp;
}

void listdir(const char *name, int layer)
{
	DIR *dir;
	struct dirent *entry;
	if (!(dir = opendir(name)))
		return;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;
			// snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
			// printf("%*s[%s]\n", layer, "", entry->d_name);
			listdir(path, layer + 2);
		} else {
			// printf("%*s- %s\n", layer, "", entry->d_name);
		}
	}
	closedir(dir);
}

int send_to_fd(int sysfs_fd, struct mail_t *mail)
{
	/*
	 * write something or nothing
	 */

	// int ret_val = write(sysfs_fd, ...);
	// if (ret_val == ERR_FULL) {
	/*
	 * write something or nothing
	 */
	// } else {
	/*
	 * write something or nothing
	 */
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
	/*
	 * write something or nothing
	 */
	// } else {
	/*
	 * write something or nothing
	 */
	// }

	/*
	 * write something or nothing
	 */
	return 0;
}
