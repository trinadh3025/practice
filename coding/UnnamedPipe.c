#include<stdio.h>
#include<unistd.h>

int main(){
	int fd[2];
	char buffer[20];
	pipe(fd);

	if(fork() == 0){
		close(fd[0]);
		write(fd[1], "hello", 5);
		close(fd[1]);
	}else{
		close(fd[1]);
		read(fd[0], buffer, 5);
		printf("Received: %s\n", buffer);
		close(fd[0]);
	}
	return 0;
}
