#include <bits/stdc++.h>
using namespace std;
#define f(i,a,b)     for(int i=a;i<b;i++)
#define z "\t\t\t"
#define y "\t\t\t\t"

struct process{
	int id;
	int a,b,c;//arrival,burst,completion
	int tat;
	int b_copy;
	int w;
};

bool compare_via_arrival(process x, process yy)
{
	return (x.a < yy.a);
}
int main()
{
	int n,total_burst_time = 0 ;
	cout<<"Enter number of processes:";
	cin>>n;
	struct process p[n+1];
	cout<<"Enter arrival time:";
	f(i,0,n){ 
		p[i].id = i+1;
		cin>>p[i].a;
		p[i].c = 0;
		p[i].w = 0;
		p[i].tat = 0;
	}
	cout<<"Enter burst time:";
	f(i,0,n){ 
		cin>>p[i].b;
		total_burst_time +=p[i].b;
		p[i].b_copy = p[i].b;
	}
	
	sort(p,p+n,compare_via_arrival);
	int time = 0; //marking time 
	while(time <= total_burst_time)
	{
		int m = INT_MAX,exe = n;
		f(i,0,n)
		{
			if(p[i].a <= time)
			{
				if(p[i].b < m && p[i].b > 0)
				{
					m = p[i].b;
					exe = i;
				}	
			}
		}
		p[exe].b -= 1;
		time++;
		if(p[exe].b == 0)
		{
			p[exe].c = time;
			p[exe].w = time - p[exe].a - p[exe].b;
			p[exe].tat = time - p[exe].a;
		}
	}

	
	printf("\n====================================================================================\n");
	//now printing other details
	cout<<"\nprocess number\tarrival time\tburst time\tcompletion time\t  waiting time\tturn around time\n";
	f(i,0,n)
	{
		cout<<z<<p[i].id<<z<<p[i].a<<y<<p[i].b<<y<<p[i].c<<z<<p[i].w<<y<<p[i].tat<<"\n";
	}




}