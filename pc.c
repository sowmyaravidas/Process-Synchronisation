/* Producer Consumer Problem
Author: Sowmya Ravidas
*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
int buffer[5],f,r;
sem_t mutex,full_count,empty_count;
void *producer(void *arg)
{
   int i;
   for(i=0;i<10;i++)
   {
       sem_wait(&empty_count);
       sem_wait(&mutex);
       printf("producerd item is %d\n",i);
       buffer[(++r)%5]=i;
       sleep(1);
       sem_post(&mutex);
       sem_post(&full_count);
       printf("full_count %u\n",full_count);
                                                                               }
}

void *consumer(void *arg)
{
      int item,i;
      for(i=0;i<10;i++)
      {
        sem_wait(&full_count);
        printf("full_count %u\n",full_count);
        sem_wait(&mutex);
        item=buffer[(++f)%5];
        printf("consumerd item is %d\n",item);
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty_count);
                                                                                  }
}
main()
{
        pthread_t tid1,tid2;
        sem_init(&mutex,0,1);
        sem_init(&full_count,0,1);
        sem_init(&empty_count,0,5);
        pthread_create(&tid1,NULL,producer,NULL);
        pthread_create(&tid2,NULL,consumer,NULL);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
}


