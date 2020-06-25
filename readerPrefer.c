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


int read_count = 0;


void *reader(void *arg)
{
    while (1) {
        sem_wait(&mutex);
        read_count++;
        
        if(read_count == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);
        /*
         * Begin Critical Section
         */
       
        /* ON YOUR CODE : CRITICAL SECTION */
        
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
    int id, i;
    struct timespec req, rem;
    id = *(int *)arg;
    req.tv_sec = 0;
    req.tv_nsec = 100000000L;
    
    while (1) {
        sem_wait(&rw_mutex);
        /*
         * Begin Critical Section
         */
        
        /* ON YOUR CODE : CRITICAL SECTION */
        
        /*
         * End Critical Section
         */
        sem_post(&rw_mutex);
        
       
    }
    pthread_exit(0);
}

int main(void){
    
    int rarg[RNUM], warg[WNUM];
    
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    
}
