#include<stdio.h>
#include<sys/shm.h>
#include<string.h>

int main(){
	
	int shmid = shmget(1234, 1024, 0666 | IPC_CREAT);
	char *shm = (char*)shmat(shmid, NULL, 0);

	if(fork() == 0){
		sprintf(shm, "Hellow From child");
	}else{
		sleep(1);
		printf("Parent reads: %s\n", shm);
		shmdt(shm); //detach shared memory
		shmctl(shmid, IPC_RMID, NULL); //Remove shared memory
	}

	return 0;
}
