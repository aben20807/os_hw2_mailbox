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

	// fullname_queue = NULL;
	//     DIR *dir = opendir(directory);
	//     if (dir == NULL) {
	//         char *err_msg = NULL;
	//         CALLOC(err_msg, ERRMSG_SIZE, sizeof(char));
	//         sprintf(err_msg, "opendir(%s)", directory);
	//         perror(err_msg);
	//         FREE(err_msg);
	//         // return NULL;
	//         exit(1);
	//     }
	//     struct dirent *entry;
	//     while ((entry = readdir(dir)) != NULL) {
	//         char *filename = NULL;
	//         CALLOC(filename, 255, sizeof(char));
	//         filename = entry->d_name;
	//         char *full_path = NULL;
	//         CALLOC(full_path, 255, sizeof(char));
	//         realpath(filename, full_path);
	//         printf("%d\n", (entry->d_type == DT_DIR));
	//         // printf("%s\n", filename);
	//         printf("%s\n", full_path);
	//     }
	//     closedir(dir);

	// listdir(directory, 0);
	Queue *q = NULL;
	init(&q);
	printf("%d\n", q->count);
	printf("%d\n", q->size(q));
	mail_t m = {{"a"}, "p"};
	printf("%s, %s\n", m.data.query_word, m.file_path);
	// mail_t *mm = NULL;
	// CALLOC(mm, sizeof(mail_ptr), 1);
	// strncpy(mm->data.query_word, "a", sizeof(mm->data.query_word));
	q->enq(q, &m);
	printf("%d\n", q->size(q));
	node_ptr p = q->deq(q);
	printf("%s, %s\n", p->mail.data.query_word, p->mail.file_path);
	printf("%d\n", q->size(q));
	printf("\nmaster finished\n\n");
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

void enq(Queue *self, node_ptr item)
{
	if (self->size() == 0) {
		self->head = item;
		self->tail = item;
	}
	self->count++;
	// node_ptr tmp = NULL;
	// MALLOC(tmp, sizeof(struct node));
	// tmp->mail = *mail;
	// self->head->prev = tmp;
	// self->head = self->head->prev;
}

node_ptr deq(Queue *self)
{
	// mail_ptr m = NULL;
	// MALLOC(m, sizeof(mail_ptr));
	// *m = self->tail->mail;
	// node_ptr tmp = self->tail;
	// self->tail = self->tail->prev;
	// self->tail->next = NULL;
	// FREE(tmp);
	// return m;
	node_ptr tmp = self->tail;
	self->tail = self->tail->prev;
	self->count--;
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
