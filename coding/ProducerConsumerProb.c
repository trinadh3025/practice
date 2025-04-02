#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_producer, cond_consumer;

//Producer function
void* producer(void* arg){
	for(int i = 1; i<=MAX_ITEMS; i++){
		usleep(rand() % 500000);
		pthread_mutex_lock(&mutex);

		while(count == BUFFER_SIZE){
			pthread_cond_wait(&cond_producer, &mutex);
		}

		buffer[count++] = i;
		printf("Producer produced: %d (Buffer count: %d)\n", i, count);

		pthread_cond_signal(&cond_consumer);
		pthread_mutex_unlock(&mutex);
	}
	printf("Items done from producer side\n");
	return NULL;
}

//Consumer function
void* consumer(void* arg){
	for(int i=1;i<= MAX_ITEMS; i++){
		usleep(rand()%50000);
		pthread_mutex_lock(&mutex);
		while(count==0){
			pthread_cond_wait(&cond_consumer, &mutex);
		}	
		int item = buffer[--count];
		printf("Consumer consumed: %d (Buffer count: %d)\n", item, count);

		pthread_cond_signal(&cond_producer);
		pthread_mutex_unlock(&mutex);
	}

	printf("Items consumption done from consumer side\n");
	return NULL;
}

int main(){


	pthread_t producer_thread, consumer_thread;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_producer, NULL);
	pthread_cond_init(&cond_consumer, NULL);

	pthread_create(&producer_thread, NULL, producer, NULL);
	pthread_create(&consumer_thread, NULL, consumer, NULL);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_producer);
	pthread_cond_destroy(&cond_consumer);
	
	return 0;
}
