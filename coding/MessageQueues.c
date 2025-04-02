#include<stdio.h>
#include<sys/msg.h>

struct msg{
	long type;
	char text[100];
};

int main(){
	int msgid = msgget(1234, 0666 | IPC_CREAT);
	struct msg message;

	if(fork() == 0){
		message.type = 1;
		printf("Message text address in child %d\n", &(message.text));
		sprintf(message.text, "Hello from chile");
		msgsnd(msgid, &message, sizeof(message.text), 0);
	}else{
		printf("Message text before receiving: %s, %d\n", message.text, &(message.text));
		msgrcv(msgid, &message, sizeof(message.text), 1, 0);
		printf("After Received: %s\n", message.text);
	}

	return 0;
}
