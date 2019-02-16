
#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b)     for(long long i=a;i<b;++i)
typedef long long ll;
#define pb push_back
#define mod 1000000007
#define debug4(a,b,c,d) cout<<a<<"->"<<b<<"->"<<c<<"->"<<d<<endl; 
#define debug3(a,b,c) cout<<a<<"->"<<b<<"->"<<c<<endl; 

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

	//this is a copy to keep burst time intact for printing 
	vector< pair<int,pair<int,int> > > copy(n);
	f(i,0,n) copy[i] = p[i];


		cout<<"\nprocess number\tarrival time\tburst time\tcompletion time\n";
	f(i,0,n)
	{
		cout<<copy[i].second.first<<"\t"<<copy[i].first<<"\t"<<copy[i].second.second<<"\t"<<"\n";
	}


	// all insertions done




	//  //sorting on the basis of arrival time and putting in a queue
	// sort(p.begin() , p.end());
	// queue<pair<int , pair<int,int>> > q;
	// f(i,0,n){
	// 	q.push(p[i]);
	// }

	
	
	// pair<int,pair<int,int> > tempp;

	// // to mesure track of time
	// int time = 0;
	// //to find completion time 
	// int completion[n];
	// f(i,0,n) completion[i] = 0;

	// while(q.empty() == 0)
	// {	
	// 	tempp = q.front();
	// 	cout<<"Process "<<tempp.second.first<<" executed for ";

	// 	if(q.front().second.second > timequanta)
	// 	{
	// 		time += timequanta;
	// 		q.front().second.second -= timequanta;
	// 		cout<<timequanta<<" seconds\n";
			
	// 		q.pop();
	// 		q.push(tempp);

	// 	}
	// 	else if(q.front().second.second == timequanta)
	// 	{
	// 		time += timequanta;
	// 		q.front().second.second -= timequanta;
	// 		cout<<timequanta<<" seconds\n";
	// 		completion[tempp.second.first] = time;  //marking for completion time
 // 			q.pop();

	// 	}
	// 	else if(q.front().second.second < timequanta)
	// 	{
	// 		time += tempp.second.second;
	// 		cout<<tempp.second.second<<" seconds\n";
	// 		q.front().second.second = 0;
	// 		completion[tempp.second.first] = time;  //marking for completion time
 // 			q.pop();
	// 	}
	// }

	// //gaant chart already printed

	// //now printing other details
	// cout<<"\nprocess number\tarrival time\tburst time\tcompletion time\n";
	// f(i,0,n)
	// {
	// 	cout<<copy[i].second.first<<"\t"<<copy[i].first<<"\t"<<copy[i].second.second<<"\t"<<completion[copy[i].second.first]<<"\n";
	// }



}