//coding idea from https://github.com/Aj163/Operating-Systems/blob/master/Experiment%2004%20-%20Process%20Synchronization/Readers_Writers.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <bits/stdc++.h>
using namespace std;
#define f(i,a,b)     for(int i=a;i<b;i++)

#define N 100
#define MAX_SEC 1000000 //1 second

sem_t mutexx,spoon[N]; // n semaphores for n spoons
int n;

void *eat(void *number)
{
	int id = *(int *)number,tim;
	int temp = rand()%3 +1;
	f(i,0,temp)
	{


		tim = rand()%MAX_SEC;
		usleep(tim);

		sem_wait(&spoon[id-1]);
		sem_wait(&spoon[id%n]);

		tim = rand()%MAX_SEC;
		usleep(tim);

		cout<<"philosopher "<<id<<" is eating \n";
		tim = rand()%MAX_SEC;
		usleep(tim);
		cout<<"philosopher "<<id<<" is done eating\n";

		
		sem_post(&spoon[id%n]);
		sem_post(&spoon[id-1]);
	}
}

int main()
{
	srand(time(0)); // for random values according to current time and random

	pthread_t phil[N]; // n threads for n philosopher
	int id[N];
	f(i,0,N)
	id[i] = i+1;

	
	
	cout<<"Enter number of philosopher:";
	cin>>n;
	
	sem_init(&mutexx,0,1);
	f(i,0,n)
	sem_init(&spoon[i],0,1);

	f(i,0,n)
	pthread_create(&phil[i], NULL, eat , &id[i]);
	

	
	
	f(i,0,n)
	pthread_join(phil[i],NULL);

	sem_destroy(&mutexx);
	f(i,0,n)
	sem_destroy(&spoon[i]);

}