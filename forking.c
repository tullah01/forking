#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int randomint(int a, int b){
	unsigned int random_int;
	int fd = open("/dev/random", O_RDONLY);
	read(fd, &random_int, 4);
	random_int = (random_int % (b - a)) + a;
	close(fd);
	return random_int;
}

int main(){
	int f1, f2;
	printf("This is from the parent process, before forking\n");
	if((f1 = fork())){
		if((f2 = fork())){	// Parent process
			printf("Parent %d\n", getpid());
			int status1;
			int pid1 = wait(&status1);
			printf("Process %d slept for %d seconds, parent is done\n", pid1, WEXITSTATUS(status1));
			return 0;
		}
	} 
	
	printf("Child created with pid %d\n", getpid());
	int sleep_time = randomint(5, 20);
	sleep(sleep_time);
	printf("Child done sleeping for %d seconds\n", sleep_time);
	return sleep_time;
}
