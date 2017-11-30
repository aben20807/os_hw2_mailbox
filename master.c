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
	printf("\nmaster finished\n\n");
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
}
