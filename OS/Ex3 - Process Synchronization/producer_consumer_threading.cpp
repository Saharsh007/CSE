//code logic from http://www.personal.kent.edu/~rmuhamma/OpSystems/Myos/semaphore.htm
//coding idea from https://github.com/Aj163/Operating-Systems/blob/master/Experiment%2004%20-%20Process%20Synchronization/Producer_Consumer.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;
#define f(i,a,b)     for(int i=a;i<b;i++)

#define N 1000
#define MAX_SEC 1000000 //1 second

sem_t mutexx,full,empty;
int BUFFER[N];
int front = 0 , rear = 0 , countt = 0,n;


void makeproduct(int product)
{
	if(countt >= N)
	{
		return;
	}
	
	BUFFER[rear] = product;
	rear = (rear+1)%N; 
	countt++;
}

int consumerproduct()
{
	if(countt <= 0)
	{
		return -1;
	}
	int item = BUFFER[front];
	front = (front+1)%N;
	countt--;
	return item;
}

void *produce(void *number)
{
	int tim;
	f(i,0,*(int *)number)
	{
		sem_wait(&empty);
		sem_wait(&mutexx);
		

		int product = rand()%1000; // some random value to push

		tim = rand()%MAX_SEC;
		usleep(tim);
		
		makeproduct(product);

		sem_post(&mutexx);
		sem_post(&full);
		cout<<"Producer produced item "<<product<<"\n";
	}
}

void *consume(void *number)
{
	int item,tim;
	f(i,0,*(int *)number)
	{
		sem_wait(&full);
		sem_wait(&mutexx);
		
		tim = rand()%MAX_SEC;
		usleep(tim);
		item = consumerproduct();
		
		sem_post(&mutexx);
		sem_post(&empty);

		cout<<"Consumer consumed item "<<item<<"\n";
	}
}

int main()
{
	srand(time(0)); // for random values according to current time and random

	pthread_t producer,consumer;
	
	int no_of_consumers = rand() % 10 +1 ;
	int no_of_producers = rand() % 10 + no_of_consumers ;
	

	cout<<"Enter size of BUFFER:";
	cin>>n;

	sem_init(&mutexx,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,n);

	pthread_create(&producer, NULL, produce , &no_of_producers);
	pthread_create(&consumer , NULL , consume , &no_of_consumers);

	

	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);

	sem_destroy(&mutexx);
	sem_destroy(&full);
	sem_destroy(&empty);



}