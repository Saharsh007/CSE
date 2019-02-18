
#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b)     for(long long i=a;i<b;++i)
#define z "\t\t\t"
#define y "\t\t\t\t"
#define pb push_back

int main()
{	
	int n,temp;
	int timequanta;
	cout<<"Enter time quanta:";
	cin>>timequanta;
	cout<<"Enter number of processes:";
	cin>>n;
	//arrival is first then process number and  burst are second
	vector< pair<int,pair<int,int> > > p(n);

	cout<<"Enter arrival time:";
	f(i,0,n){ 
		cin>>temp;
		p[i].second.first = i+1;		//process number assigned
		p[i].first = temp;
	}
	cout<<"Enter burst time:";
	f(i,0,n){ 
		cin>>temp;
		p[i].second.second = temp;
	}

	// all insertions done



//this is a copy to keep burst time intact for printing 
	vector< pair<int,pair<int,int> > > copy(n);
	f(i,0,n) copy[i] = p[i];


	 //sorting on the basis of arrival time and putting in a queue
	sort(p.begin() , p.end());
	queue<pair<int , pair<int,int>> > q;
	f(i,0,n){
		q.push(p[i]);
	}

	
	// cout<<"\nprocess number\tarrival time\tburst time\n";
	// f(i,0,n)
	// {
	// 	cout<<p[i].second.first<<"\t"<<p[i].first<<"\t"<<p[i].second.second<<"\n";
	// }

	pair<int,pair<int,int> > tempp;

	// to mesure track of time
	int time = 0;
	//to find completion time 
	int c[n];
	f(i,0,n) c[i] = 0;
	cout<<endl;
	while(q.empty() == 0)
	{	

		tempp = q.front();
		cout<<"Process "<<tempp.second.first<<" executed for ";

		if(tempp.second.second > timequanta)
		{
			time += timequanta;
			tempp.second.second -= timequanta;
			cout<<timequanta<<" seconds with remaining burst time is "<<tempp.second.second<<"\n";
			q.pop();
			q.push(tempp);

		}
		else if(tempp.second.second == timequanta)
		{
			time += timequanta;
			tempp.second.second -= timequanta;
			cout<<timequanta<<" seconds with remaining burst time is "<<tempp.second.second<<"\n";
			c[tempp.second.first] = time;  //marking for completion time
 			q.pop();

		}
		else if(tempp.second.second < timequanta)
		{
			time += tempp.second.second;
			cout<<timequanta<<" seconds with remaining burst time is "<<tempp.second.second<<"\n";
			tempp.second.second = 0;
			c[tempp.second.first] = time;  //marking for completion time
 			q.pop();
		}
	}

	//gaant chart already printed	

	//calculating waiting time and tat
	int w[n],tat[n];
	f(i,0,n)
	{
		w[copy[i].second.first] = c[copy[i].second.first] - copy[i].second.second - copy[i].first;
		tat[copy[i].second.first] = c[copy[i].second.first] - copy[i].first;
	}

	printf("\n====================================================================================\n");
	//now printing other details
	cout<<"\nprocess number\tarrival time\tburst time\tcompletion time\t  waiting time\tturn around time\n";
	f(i,0,n)
	{
		cout<<z<<copy[i].second.first<<z<<copy[i].first<<y<<copy[i].second.second<<y<<c[copy[i].second.first]<<z<<w[copy[i].second.first]<<y<<tat[copy[i].second.first]<<"\n";
	}



}

/*
INPUT

3
4
0 1 2 3
10 4 5 3

OUTPUT

Process 1 executed for 3 seconds with remaining burst time is 7
Process 2 executed for 3 seconds with remaining burst time is 1
Process 3 executed for 3 seconds with remaining burst time is 2
Process 4 executed for 3 seconds with remaining burst time is 0
Process 1 executed for 3 seconds with remaining burst time is 4
Process 2 executed for 3 seconds with remaining burst time is 1
Process 3 executed for 3 seconds with remaining burst time is 2
Process 1 executed for 3 seconds with remaining burst time is 1
Process 1 executed for 3 seconds with remaining burst time is 1

process number	arrival time	burst time	completion time	  waiting time	turn around time
			1			0				10				22			12				22
			2			1				4				16			11				15
			3			2				5				18			11				16
			4			3				3				12			6				9
*/
