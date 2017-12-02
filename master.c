#include "master.h"

int main(int argc, char **argv)
{
	printf("master start...\n\n");
	query_word = NULL;
	directory = NULL;
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
	create_slave(num_slave);
	print_list(slave_list);
	printf("query_word: %s\n", query_word);
	printf("directory: %s\n", directory);
	printf("num_slave: %d\n", num_slave);
	test_listdir();
	char c;
	while (true) {
		scanf(" %c", &c);
		if (c == 'k') {
			kill_all_slave(slave_list);
			break;
		}
	}
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
		item->next = self->head;
		self->head = item;
	}
	self->count++;
	return true;
}

/*
 * Remove a node which cantains a mail_t from queue at tail.
 */
node_ptr deq(Queue *self)
{
	if ((self == NULL) || self->size(self) == 0) {
		return NULL;
	}
	node_ptr tmp = self->tail;
	self->tail = self->tail->prev;
	self->tail->next = NULL;
	self->count--;
	return tmp;
}

/*
 * Display all nodes in queue from head to tail.
 */
bool display(Queue *self)
{
	if (self == NULL) {
		return false;
	}
	printf("head->\n");
	node_ptr curr = self->head;
	int count = 0;
	while (curr != NULL) {
		printf("%d:\n%s\n%s\n", count++, curr->mail_p->data.query_word,
		       curr->mail_p->file_path);
		curr = curr->next;
	}
	printf("<-tail\n");
	return true;
}

mail_ptr create_mail(const char *q_w, const char *f_p)
{
	mail_ptr tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	strncpy(tmp->data.query_word, q_w, sizeof(tmp->data.query_word));
	strncpy(tmp->file_path, f_p, sizeof(tmp->file_path));
	return tmp;
}

node_ptr create_node(mail_ptr mail_p)
{
	node_ptr tmp = NULL;
	CALLOC(tmp, sizeof(*tmp), 1);
	tmp->mail_p = mail_p;
	tmp->prev = NULL;
	tmp->next = NULL;
	return tmp;
}

/*
 * Be use recursive to get all files under input directory and insert to queue.
 */
void listdir(const char *name, int layer)
{
	DIR *dir;
	struct dirent *entry;
	if (!(dir = opendir(name)))
		return;
	if (name[0] != '/') {
		char *full_path = NULL;
		CALLOC(full_path, PATH_MAX, sizeof(char));
		realpath(name, full_path);
		name = full_path;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			char path[1024];
			if (strcmp(entry->d_name, ".") == 0 ||
			    strcmp(entry->d_name, "..") == 0) {
				continue;
			}
			snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
			// printf("%*s[%s]\n", layer, "", entry->d_name);
			listdir(path, layer + 2);
		} else {
			// printf("%*s- %s\n", layer, "", entry->d_name);
			char fullname[PATH_MAX + 1];
			snprintf(fullname, sizeof(fullname), "%s/%s", name, entry->d_name);
			node_ptr tmp = create_node(create_mail(query_word, fullname));
			fullname_queue->enq(fullname_queue, tmp);
		}
	}
	closedir(dir);
}

/*
 * Create n slaves, n = num_slave
 */
void create_slave(int num)
{
	slave_list = NULL;
	MALLOC(slave_list, sizeof(struct element));
	element_ptr curr_ptr = slave_list;
	bool is_first = true;
	while (num--) {
		pid_t pid = fork();
		// printf("%d\n", pid);
		if (pid < 0) {
			perror("fork error");
			return;
		} else if (pid == 0) {
			char *full_path = NULL;
			CALLOC(full_path, PATH_MAX, sizeof(char));
			realpath("slave", full_path);
			// printf("%s\n", full_path);
			execl(full_path, "slave", NULL);
		} else {
			if (!is_first) {
				MALLOC(curr_ptr->next, sizeof(struct element));
				curr_ptr = curr_ptr->next;
			}
			curr_ptr->pid = pid;
			curr_ptr->next = NULL;
			is_first = false;
		}
	}
}

void delete_list(const List l)
{
	element_ptr curr_ptr = l;
	while (curr_ptr != NULL) {
		element_ptr tmp = curr_ptr;
		curr_ptr = curr_ptr->next;
		FREE(tmp);
	}
}

void print_list(const List l)
{
	element_ptr curr_ptr = l;
	while (curr_ptr != NULL) {
		printf("%d ", curr_ptr->pid);
		curr_ptr = curr_ptr->next;
	}
}

void kill_all_slave(const List l)
{
	element_ptr curr_ptr = l;
	while (curr_ptr != NULL) {
		element_ptr tmp = curr_ptr;
		curr_ptr = curr_ptr->next;
		kill(tmp->pid, SIGKILL);
		FREE(tmp);
	}
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

void test_queue()
{
	Queue *q = NULL;
	init(&q);
	mail_ptr m1 = create_mail("d", "p");
	mail_ptr m2 = create_mail("e", "u");
	mail_ptr m3 = create_mail("f", "t");
	node_ptr np = NULL;

	np = (node_ptr)create_node(m1);
	q->enq(q, np);
	printf("enq1, size: %d\n", q->size(q));
	printf("en: %s, %s\n\n", np->mail_p->data.query_word, np->mail_p->file_path);

	np = (node_ptr)create_node(m2);
	q->enq(q, np);
	printf("enq2, size: %d\n", q->size(q));
	printf("en: %s, %s\n\n", np->mail_p->data.query_word, np->mail_p->file_path);

	np = q->deq(q);
	printf("deq1, size: %d\n", q->size(q));
	printf("de: %s, %s\n\n", np->mail_p->data.query_word, np->mail_p->file_path);

	np = (node_ptr)create_node(m3);
	q->enq(q, np);
	printf("enq3, size: %d\n", q->size(q));
	printf("en: %s, %s\n\n", np->mail_p->data.query_word, np->mail_p->file_path);

	np = q->deq(q);
	printf("deq2, size: %d\n", q->size(q));
	printf("de: %s, %s\n\n", np->mail_p->data.query_word, np->mail_p->file_path);

	np = q->deq(q);
	printf("deq3, size: %d\n", q->size(q));
	printf("de: %s, %s\n\n", np->mail_p->data.query_word, np->mail_p->file_path);
}

void test_listdir()
{
	init(&fullname_queue);
	listdir(directory, 0);
	fullname_queue->display(fullname_queue);
	printf("size: %d\n", fullname_queue->size(fullname_queue));
	fullname_queue->deq(fullname_queue);
	fullname_queue->deq(fullname_queue);
	fullname_queue->display(fullname_queue);
	printf("size: %d\n", fullname_queue->size(fullname_queue));
}
