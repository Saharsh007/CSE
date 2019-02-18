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

sem_t mutexx,db;
int no_of_readers,no_of_writers,r_count = 0;

void *readd(void *number)
{
	int id = *(int *)number,tim;
	int temp = rand()%3 +1;
	f(i,0,temp)
	{
		tim = rand()%MAX_SEC;
		usleep(tim);

		sem_wait(&mutexx);
		r_count++;
		if(r_count == 1)
			sem_wait(&db);
		sem_post(&mutexx);


		cout<<"reader number "<<id<<" is reading \n";
		tim = rand()%MAX_SEC;
		usleep(tim);
		cout<<"reader number "<<id<<" is idle now\n";

		sem_wait(&mutexx);
		r_count--;
		if(r_count == 0)
			sem_post(&db);
		sem_post(&mutexx);
		

		
	}
}

void *writee(void *number)
{
	int id = *(int *)number,tim;
	int temp = rand()%3 +1;
	f(i,0,temp)
	{
		tim = rand()%MAX_SEC;
		usleep(tim);
		sem_wait(&db);
		cout<<"writer number "<<id<<" is writing \n";
		tim = rand()%MAX_SEC;
		usleep(tim);
		cout<<"writer number "<<id<<" is idle now\n";
		sem_post(&db);
	}
}

int main()
{
	srand(time(0)); // for random values according to current time and random

	pthread_t reader[N],writer[N];
	int id[N];
	f(i,0,N)
	id[i] = i+1;

	
	
	cout<<"Enter number of readers and writers:";
	cin>>no_of_readers>>no_of_writers;
	
	sem_init(&mutexx,0,1);
	sem_init(&db,0,1);

	f(i,0,no_of_writers)
	pthread_create(&writer[i], NULL, readd , &id[i]);
	f(i,0,no_of_readers)
	pthread_create(&reader[i] , NULL , writee ,&id[i]);

	
	f(i,0,no_of_writers)
	pthread_join(writer[i],NULL);

	f(i,0,no_of_readers)
	pthread_join(reader[i],NULL);

	sem_destroy(&mutexx);
	sem_destroy(&db);

}