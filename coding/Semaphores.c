#include<stdio.h>
#include<sys/sem.h>

int main(){
	int semid= semget(1234, 1, 0666 | IPC_CREAT);
	struct sembuf sb = {0, -1, 0};

	if (fork() == 0){
		semop(semid, &sb, 0);
		printf("Child enters critical section\n");
		sleep(2);
		sb.sem_op = 1;
		semop(semid, &sb, 1);
	}else{
		sleep(1);
		semop(semid, &sb, 1);
		printf("Parent enters critical section\n");
		sb.sem_op = 1;
		semop(semid, &sb, 1);
	}

	return 0;
}
