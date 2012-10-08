#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#define True 1
#define False 0

int global=0;
int turn=0;
int interested[]={0,1};


void enter_region(int process)
{
    
    int other=0;
    other = 1-process;
    turn = process;
    interested[process] = True;
    while(turn==process && interested[other]==True)
    {}
}

void leave_region(int process)
{
    interested[process] = False;
}

int main()
{

    void *fn(void *arg);
    int id[]={0,1};


    pthread_t thread[2];
    int i;
    for(i=0;i<2;i++)
    {
    pthread_create(&thread[i],NULL,fn,(void*)id[i]);

    }

    for(i=0;i<2;i++)
    {

    pthread_join(thread[i],NULL);

    }
    return EXIT_SUCCESS;
}


void *fn(void *arg)
{
    int ip=(int)arg;
    int i;
    for(i=0;i<4;i++)
    {
        enter_region(ip);
        global++;
        leave_region(ip);

        enter_region(ip);
        global--;
        leave_region(ip);


    }

printf("%d",global);
}







