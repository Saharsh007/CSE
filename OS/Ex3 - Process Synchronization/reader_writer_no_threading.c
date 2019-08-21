#include<stdio.h>
#include<stdlib.h>
int mutex=1;
int readcnt=0;
int writing=0;
int wait(int semaphore)
{
	return (--semaphore);
}
int signal(int semaphore)
{
	return (++semaphore);
}
void reader()
{
	mutex=wait(mutex);
	readcnt++;
	printf("READER ADDED \n");
	mutex=signal(mutex);
}
void writer()
{
	writing=1;
	mutex=wait(mutex);
	printf("WRITER ADDED\n");
	mutex=signal(mutex);
}

	
int main()
{
	int ch;
	while(1)
	{
		printf("ADD READER:1\nSTART WRITING:2\nSTROP WRITING:3\nREDUCE READER:4\nEXIT:5\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				if(mutex==1 && writing==0)
				reader();
				else
				printf("CANNOT WRITE READING IN PROGRESS\n");
				break;
			case 2:
				if(writing==1)
				printf("CANNOT WRITE , ANOTHER USER IS WRITING\n");
				else if(mutex==1 && readcnt==0 && writing==0)
				writer();
				if(readcnt!=0) 
				printf("CANNOT WRITE ,READER ACTIVE\n");
				break;
			case 3:
				if(mutex==1 && writing==1)
				{
					writing=0;
					printf("Writing stopped!\n");
				}
				else
				printf("No writing taking place\n");
				break;
			case 4:
				if(readcnt==0)printf("NO READER\n");
				else
				{
					printf("READER REDUCED\n");
					readcnt--;
				}
				break;
			case 5:
				break;
		}
		if(ch==5)break;
	}
}

	
				
				
