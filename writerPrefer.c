#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


#define RNUM 10
#define WNUM 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t availRead = PTHREAD_COND_INITIALIZER;
pthread_cond_t availWrite = PTHREAD_COND_INITIALIZER;

int readers = 0;
int writers = 0;
int waiting_writers = 0;
int waiting_readers = 0;


void *reader(void *arg)
{
   
    while (1) {
        pthread_mutex_lock(&mutex);
        while((waiting_writers + writers) > 0){ // 현재 reader가 critical section에 들어갈 수 있는지 없는지 파악
          pthread_cond_wait(&availRead, &mutex); // availRead 컨디션에 대기.
        }
        readers++; // critical section에 들어가기전 reader(activated)의 수를 늘려줌
        pthread_mutex_unlock(&mutex);
        /*
         * Begin Critical Section
         */
       
        /* YOUR CODE IN HERE */
        
        /*
         * End Critical Section
         */
        pthread_mutex_lock(&mutex);
        readers--; // critical section에 빠져나오면서 reader의 수를 줄여줌
        if(readers == 0 && waiting_writers > 0){
          pthread_cond_signal(&availWrite); // reader가 없고 대기중인 writer가 있으면 writer가 진입가능한 상태이므로 signal.
        }
        pthread_mutex_unlock(&mutex);
        
    }
    pthread_exit(0);
}

void *writer(void *arg)
{
   
    while (1) {
        pthread_mutex_lock(&mutex);
        while((readers + writers) > 0){ // reader와 writer가 critical section에 있으면 진입 x
          waiting_writers++; // 대기 중인 writer 수 증가
          pthread_cond_wait(&availWrite, &mutex); // 대기중인 writer 대기큐에 진입
          waiting_writers--; // 위 코드 통과하면 대기 중인 writer 수 감소
        }
        writers++; // critical section에 진입하는 writer(activated) 수를 늘려줌.
        pthread_mutex_unlock(&mutex);
        /*
         * Begin Critical Section
         */
       
        /* YOUR CODE IN HERE */
        
        /*
         * End Critical Section
         */
        pthread_mutex_lock(&mutex);
        writers--; // critical section에 빠져나오고 writer(activated) 수를 --.
        if(waiting_writers > 0){ // 대기중인 writer가 있는지 없는지 판별 후 reader들에게 권한을 부여할 지 보는 조건절
          pthread_cond_signal(&availWrite); // 대기중인 writer가 있으면 진입하게끔 signal.
        }else
          pthread_cond_broadcast(&availRead); // reader는 중복을 허락하므로 대기큐에 있는 reader들을 동시에 깨움 (broadcast)

        pthread_mutex_unlock(&mutex);
       
    }
    pthread_exit(0);
}

int main(void)
{
    int rarg[RNUM], warg[WNUM];
    pthread_t rthid[RNUM];
    pthread_t wthid[WNUM];
    pthread_attr_t attr;
    
    /* YOUR CODE IN HERE */
  
    exit(0);
}

