#include <stdio.h>
#include <pthread.h>

#ifdef PTHREAD_JOIN
	void* thread_A(void* arg){
		printf("Thread A is running..\n");
		return NULL;
	}

	void* thread_B(void* arg){
		pthread_t* threadA = (pthread_t*)arg;
		pthread_join(*threadA, NULL);
		printf("Thread A is finished, now Thread B runs\n");
		return NULL;
	}

	int main(){

		pthread_t A, B;
		pthread_create(&A, NULL, thread_A, NULL);
		pthread_create(&B, NULL, thread_B, &A);

		pthread_join(B, NULL);
		return 0;
	}
#endif

#ifdef MUTEX_AND_FLAG

	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	int thread_A_done = 0;

	void* thread_A(void* arg){
		printf("Thread A is running...\n");
		pthread_mutex_lock(&lock);
		thread_A_done = 1;
		pthread_mutex_unlock(&lock);
		return NULL;
	}

	void* thread_B(void* arg){
		while(1){
			pthread_mutex_lock(&lock);
			if(thread_A_done){
				pthread_mutex_unlock(&lock);
				break;
			}
			pthread_mutex_unlock(&lock);
		}
		printf("Thread A finished, now Thread B runs.\n");
		return NULL;
	}

	int main(){
		
		pthread_t A,B;
		pthread_create(&A, NULL, thread_A, NULL);
		pthread_create(&B, NULL, thread_B, NULL);

		pthread_join(A, NULL);
		pthread_join(B, NULL);
		return 0;
	}
#endif

#ifdef COND_VARIABLE
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	int thread_A_done = 0;

	void* thread_A(void* arg){
		printf("Thread A is running...\n");
		pthread_mutex_lock(&lock);
		thread_A_done = 1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);

		return NULL;
	}

	void* thread_B(void* arg){
		pthread_mutex_lock(&lock);
		while(!thread_A_done){
			pthread_cond_wait(&cond, &lock);
		}
		pthread_mutex_unlock(&lock);
		printf("Thread A finished, now Thread B runs.\n");
		return NULL;
	}

	int main(){

		pthread_t A, B;
		pthread_create(&A, NULL, thread_A, NULL);
		pthread_create(&B, NULL, thread_B, NULL);

		pthread_join(A, NULL);
		pthread_join(B, NULL);
		return 0;
	}
#endif

#if COND_VARIABLE == 0 && MUTEX_AND_FLAG == 0 && PTHREAD_JOIN == 0
	int main(){
		
		printf("Incorrect macros used at compilation time\n");
		return 0;
	}
#endif
