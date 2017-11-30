#include "master.h"

int main(int argc, char **argv)
{
    printf("master start...\n");
    char arg;
    while((arg = getopt(argc, argv, "q:d:s:"))!= -1) {
        switch(arg) {
            case 'q':
                printf("option q:'%s'\n",optarg);
                break;
            case 'd':
                printf("option d:'%s'\n",optarg);
                break;
            case 's':
                printf("option s:'%s'\n",optarg);
                break;
        }
    }
    printf("master finished\n\n");
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
