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
        sem_wait(&mutex); // semaphore for counting # of readers
        read_count++;
        
        if(read_count == 1) // If there is a reader, then writer can not enter critical section
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
            sem_post(&rw_mutex); // reader is 0, then writer can enter critical section
        sem_post(&mutex);
        
    }
    pthread_exit(0);
}

void *writer(void *arg)
{
    
    while (1) {
        sem_wait(&rw_mutex); // waiting signal what is reader is 0
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
    
    sem_init(&rw_mutex, 0, 1); // semaphore initialize
    sem_init(&mutex, 0, 1); // semaphore initialize
    
    pthread_t rthid[RNUM]; // pthread for reader. If there are a lot of reader, then there is a possibility that the writer will not get the opportunity.
    pthread_t wthid[WNUM];
    
    /* YOUR CODE */
}
