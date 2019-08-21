#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<b;i++)

using namespace std;

int n,m;
int available[10];
int remaining[10];
int maxx[10][10];
int allocation[10][10];
int need[10][10];
bool finsihed[10];
int processes[10];
int complete =1;
int id;
int new_request[10];
vector<int> checkforsafe()
{
	vector<int> v;
	f(i,0,n)
		v.push_back(0);
	int count = 0;
	while(count<n)
	{
		bool found = 0;
		f(p,0,n)
		{		
			if(finsihed[p] == 0)
			{				//used p and r for process and resource for better understanding
				int r;
				for(r =0 ;r<m;r++)
					if(remaining[r] < need[p][r])
					{
						//cout<<remaining[r]<<"and need is "<<need[p][r]<<" and r and p is "<<r<<" "<<p<<endl;
						break;
					}
				//cout<<"R and p is "<<r<<" "<<p<<endl;
				if(r == m)					//resource allocation
				{
					//cout<<"yes here\n\n\n\n";
					if( p== id)
					{
						v[count] = p;
						count++;
						finsihed[p] = 1;
						f(k,0,m)
							remaining[k] += allocation[p][k] + new_request[k];
						found = 1;		
					}
					else{
					v[count] = p;
					count++;
					finsihed[p] = 1;
					f(k,0,m)
						remaining[k] += allocation[p][k];
					found = 1;
					}					
				}
			}
			cout<<"\nfor process "<<p<<"\n";
			f(i,0,m)
				cout<<remaining[i]<<"\t";
			cout<<"\n";	
		}
		if(found == 0)
		{
			complete = 0;
			return v;
		}

	}
	return v;

}

//changing remaining for resources change

int main()
{
	
	//cout<<"ENTER n and m\n";
	cin>>n>>m;
	// n is no of process and m is no of resources
	
	f(i,0,n)
		processes[i] = i;
	//cout<<"ENTER AVAILABLE RESOURCE\n";
	f(i,0,m){
		cin>>remaining[i];
		available[i] = remaining[i];
	}

	//cout<<"\nENTER MAX , ALLOCATION FOR ALL PROCESSES respectively \n";
	f(i,0,n)
	{
		f(j,0,m)
			cin>>maxx[i][j];
		f(j,0,m)
		{
			cin>>allocation[i][j];
			need[i][j] = maxx[i][j] - allocation[i][j];
			available[j] +=  allocation[i][j];
		}
	}

	//resource request

	//cout<<"ENTER PROCESS ID AND REQUEST\n";
	
	cin>>id;
	bool flag = 1;
	
	f(i,0,m)
		cin>>new_request[i];
	f(i,0,m)								//requested for more than max amount
		if(new_request[i] > need[id][i])
			{flag=0;
			break;}
	f(i,0,m)
		if(new_request[i] > remaining[i])
			{flag = 0;
				break;}

	if(flag == 0){
			cout<<"\ncan't entertain the request\n";
	}
	else{
		cout<<"\nThis request is entertained\n";
		f(i,0,m){
			remaining[i] -= new_request[i];
			need[id][i] -= new_request[i];
			}
	}

	// cout<<"\nTEST TEST TEST\n";
	// f(i,0,n)
	// {
	// 	cout<<"for process "<<i<<"need is \n";
	// f(j,0,m)
	// {
	// 	cout<<need[i][j]<<"\t";
	// }
	// }
	



	f(i,0,n)
		finsihed[i] = 0;

	vector<int> v = checkforsafe();

	if(complete == 0)
		cout<<"\nNOT IN SAFE STATE\n";
	else{
		cout<<"\nSAFE SEQUENCE IS:\n";
		f(i,0,n)
			cout<<v[i]<<"\t";
	}

}

/*
input

5 3
3 3 2
7 5 3 0 1 0
3 2 2 2 0 0
9 0 2 3 0 2
2 2 2 2 1 1
4 3 3 0 0 2
1
1 0 2


*/
