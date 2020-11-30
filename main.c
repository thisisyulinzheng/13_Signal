#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

static void sighandler(int signo) {
	if (signo == SIGINT) {
		int out_file = open("file.out", O_CREAT | O_WRONLY | O_APPEND, 0666);
		char msg[] = "The processed stopped running because SIGINT\n";
		write(out_file, msg, strlen(msg)*4);
		close(out_file);
		exit(0);
	}
	if (signo == SIGUSR1) {
		printf("Parent ID of Process: %d\n", getppid());
	}
}

int main() {
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	
	while (1) {
		printf("Process %d running in a loop\n", getpid());
		sleep(1);
	}
	
	return 0;
}