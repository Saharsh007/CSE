#include<bits/stdc++.h>
 using namespace std;

 int main()
 {
 	int buff_size,buff_curr=0;
 	cout<<"Enter buffer size:";
 	cin>>buff_size;
 	int producer = 0, consumer = 0;
 	while(1)
 	{
 		int choice;
 		cout<<"\nSTART PRODUCING:1\nSTOP PRODUCING:2\nSTART CONSUMING:3\nSTOP CONSUMING:4\nEXIT:any\n";
 		cin>>choice;
 		if(choice ==1)
 		{
 			if(producer == 0 )
 			{
 				if(consumer == 0)
 				{
 				if(buff_curr < buff_size)
 				{
 				producer = 1;
 				cout<<"PRODUCING STARTED\n";
 				buff_curr++;
 				continue;
 				}
 				else
 				{
 					cout<<"BUFFER FULL\n";
 					continue;
 				}
 				}
 				else
 				{
 					cout<<"CONSUMER CONSUMING, CANNOT PRODUCE\n";
 					continue;
 				}

 			}
 			else 
 			{
 				cout<<"ALREADY PRODUCING\n";
 				continue;

 			}
 		}
 		if(choice ==2)
 		{
 			if(producer == 1 )
 			{
 				producer =0;
 				cout<<"PRODUCING STOPPED\n";
 				continue;
 			}
 			else 
 			{
 				cout<<"ALREADY STOPPED\n";
 				continue;
 			}
 		}
 		if(choice ==3)
 		{
 			if(consumer == 0 )
 			{
 				if(producer == 0)
 				{
 				if(buff_curr > 0)
 				{
 				consumer = 1;
 				cout<<"CONSUMING STARTED\n";
 				buff_curr--;
 				continue;
 				}
 				else
 				{
 					cout<<"BUFFER EMPTY\n";
 					continue;
 				}
 				}
 				else 
 				{
 					cout<<"PRODUCER PRODUCING CANNOT CONSUME\n";
 					continue;
 				}
 			}
 			else 
 			{
 				cout<<"ALREADY CONSUMING\n";
 				continue;
 			}
 			
 			
 		}
 		if(choice ==4)
 		{
 			if(consumer == 1 )
 			{
 				consumer =0;
 				cout<<"CONSUMING STOPPED\n";
 				continue;
 			}
 			else 
 			{
 				cout<<"ALREADY STOPPED\n";
 				continue;
 			}
 		}
 		else
 		{
 			break;
 		}
 		
 	}
 }
