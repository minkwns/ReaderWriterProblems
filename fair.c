/* This algorithm is created by adding semaphore of readerPrefer.c. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include <semaphore.h>

#define RNUM 10
#define WNUM 2

sem_t rw_mutex;
sem_t mutex;
sem_t fair;

int read_count = 0;


void *reader(void *arg)
{
    while (1) {
        sem_wait(&fair); // reader와 writer가 같은 세마포에 레디큐에 들어감.
        sem_post(&fair); // reader는 중복으로 critical section에 진입이 가능하니 바로 release를 해준다.
        sem_wait(&mutex);
        read_count++;
        
        if(read_count == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);
        /*
         * Begin Critical Section
         */

        /* YOUR CODE IN HERE */
        
        /*
         * End Critical Section
         */
        sem_wait(&mutex);
        read_count--;
        if(read_count == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);
        
    }
    pthread_exit(0);
}

void *writer(void *arg)
{
    while (1) {
        sem_wait(&fair); // writer가 레디큐에 들어가고 순서가 오면 reader나 다른 writer가 기회를 받으면 안되므로 함수 끝에서 post.
        sem_wait(&rw_mutex);
        /*
         * Begin Critical Section
         */

        /* YOUR CODE IN HERE */

        /*
         * End Critical Section
         */
        sem_post(&rw_mutex);
        sem_post(&fair); // 온전하게 writer가 한번 다 통과한 다음 release.
        
    }
    pthread_exit(0);
}

int main(void)
{
    int i;
    int rarg[RNUM], warg[WNUM];
    pthread_t rthid[RNUM];
    pthread_t wthid[WNUM];
    
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    sem_init(&fair, 0, 1);
    

    /*
     * Initialize thread attributes
     */
    if (pthread_attr_init(&attr) != 0) {
            fprintf(stderr, "pthread_init error\n");
            exit(-1);
    }
  
    /*
     * Create RNUM reader threads
     */
    
    for (i = 0; i < RNUM; ++i) {
        rarg[i] = i;
        if (pthread_create(rthid+i, &attr, reader, rarg+i) != 0) {
            fprintf(stderr, "pthread_create error\n");
            exit(-1);
        }
    }
    
    /*
     * Create WNUM writer threads
     */
    for (i = 0; i < WNUM; ++i) {
        warg[i] = i;
        if (pthread_create(wthid+i, &attr, writer, warg+i) != 0) {
            fprintf(stderr, "pthread_create error\n");
            exit(-1);
        }
    }
        
    /* YOUR CODE IN HERE */
    
    exit(0);
}
