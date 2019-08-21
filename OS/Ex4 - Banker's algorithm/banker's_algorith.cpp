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
				for(r=0;r<m;r++)
					if(remaining[r] < need[p][r])
						break;
				if(r == m)					//resource allocation
				{
					v[count] = p;
					count++;
					finsihed[p] = 1;
					f(k,0,m)
						remaining[k] += allocation[p][k];
					found = 1;					
				}
			}	
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
	
	cout<<"ENTER n and m\n";
	cin>>n>>m;
	// n is no of process and m is no of resources
	
	f(i,0,n)
		processes[i] = i;
	cout<<"ENTER AVAILABLE RESOURCE\n";
	f(i,0,m){
		cin>>remaining[i];
		available[i] = remaining[i];
	}

	cout<<"\nENTER MAX , ALLOCATION FOR ALL PROCESSES respectively \n";
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
*/
