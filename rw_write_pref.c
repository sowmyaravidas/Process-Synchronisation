/* Reader Writer Problem
   Giving preference to Writers
Author: Sowmya Ravidas */


#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
sem_t mutex1,mutex2,mutex3,writeblock,readblock;
int data = 0,rcount = 0,wcount=0;

void *reader(void *arg)
{
    sem_wait(&mutex3);
    sem_wait(&readblock);
    sem_wait(&mutex1);

     int f;
     f = ((int)arg);
    
     rcount = rcount + 1;
      if(rcount==1)
        {
            sem_wait(&writeblock);
        }

     sem_post(&mutex1);
     sem_post(&readblock);
     sem_post(&mutex3);

     printf("Data read by the reader%d is %d\n",f,data);
     sleep(1);
     sem_wait(&mutex1);
     rcount = rcount - 1;
     if(rcount==0)
     {
     sem_post(&writeblock);}
     sem_post(&mutex1);
}

void *writer(void *arg)
{

  sem_wait(&mutex2);
  wcount=wcount+1;
  if(wcount=1)
      sem_wait(&readblock);
   sem_post(&mutex2);

  int f;
  f = ((int) arg);
  sem_wait(&writeblock);
  
  data++;
  printf("Data writen by the writer%d is %d\n",f,data);
  sleep(1);
  int value;
  printf("%d",sem_getvalue(&writeblock,&value));
  sem_post(&writeblock);
   
  sem_wait(&mutex2);
  wcount=wcount-1;
  if(wcount=0)
      sem_post(&readblock);
  sem_post(&mutex2);
}



int main()
{
  int i; 
  pthread_t rtid[5],wtid[5];
  sem_init(&mutex1,0,1);
  sem_init(&mutex2,0,1);
  sem_init(&mutex3,0,1);
  sem_init(&writeblock,0,1);
  sem_init(&readblock,0,1);
  
  for(i=0;i<=2;i++)
  {
     pthread_create(&rtid[i],NULL,reader,(void *)i);
     pthread_create(&wtid[i],NULL,writer,(void *)i);
  }
  for(i=0;i<=2;i++)
  {
  pthread_join(wtid[i],NULL);
  pthread_join(rtid[i],NULL);
  }
  return 0;
}
