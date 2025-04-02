#include<stdio.h>
#include<pthread.h>

#define MAX_NUM 20

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int counter = 1;

void* print_odd(void* arg){
	while(counter <= MAX_NUM){
		pthread_mutex_lock(&mutex);
		while(counter % 2 == 0){
			pthread_cond_wait(&cond, &mutex);
		}
		if(counter <= MAX_NUM){
			printf("%d ", counter);
			counter++;
		}
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
}
void* print_even(void* arg){
	while(counter <= MAX_NUM){
		pthread_mutex_lock(&mutex);
		while(counter % 2 == 1){
			pthread_cond_wait(&cond, &mutex);
		}
		if(counter <= MAX_NUM){
			printf("%d ", counter);
			counter++;
		}
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	
	pthread_t odd_thread, even_thread;
	pthread_create(&odd_thread, NULL, print_odd, NULL);
	pthread_create(&even_thread, NULL, print_even, NULL);

	pthread_join(odd_thread, NULL);
	pthread_join(even_thread, NULL);

	printf("\n");
	return 0;
}
