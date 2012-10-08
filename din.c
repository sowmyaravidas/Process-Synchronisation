/*Dining Philosophers Problem 
Author: Sowmya Ravidas
Idea borrowed from http://siber.cankaya.edu.tr/ozdogan/OperatingSystems/ceng328/node149.html */


#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define N 5
#define HUNGRY 1
#define EATING 2
#define THINKING 0
#define LEFT (pno+4)%N
#define RIGHT (pno+1)%N

sem_t mutex;
sem_t S[N];

void *philosopher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);

int state[N];
int ph_no[N]={0,1,2,3,4};

int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philosopher,&ph_no[i]);
      printf("philosopher %d is thinking \n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}

void *philosopher(void *num)
{
    while(1)
    {
        int *i=num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

void take_fork(int pno)
{
    sem_wait(&mutex);
    state[pno]=HUNGRY;
    printf("hungry\n");
    test(pno);
    sem_post(&mutex);
    sem_wait(&S[pno]);
    sleep(1);
}

void test(int pno)
{
    if(state[pno]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
    {
        state[pno]=EATING;
    printf("Philosopher %d takes fork %d and %d\n",pno+1,LEFT+1,pno+1);
            printf("Philosopher %d is Eating\n",pno+1);
        sleep(2);
        sem_post(&S[pno]);
    }
}

void put_fork(int pno)
{
    sem_wait(&mutex);
    state[pno]=THINKING;
printf("Philosopher %d putting fork %d and %d down\n",pno+1,LEFT+1,pno+1);
    printf("Philosopher %d is thinking\n",pno+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}











