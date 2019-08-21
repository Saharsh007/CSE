#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b) for(int i=a;i<b;i++)


void print_page_table(vector<int>v){
	cout<<"CURRENT PAGE TABlE\t\t\t\t\t\t";
	f(i,0,v.size()) cout<<v[i]<<"\t";
	cout<<"\n\n";
}

int main(){
	int n;
	cout<<"ENTER SIZE OF PAGE TABLE\n";
	cin>>n;

	int m,mcopy;
	cout<<"ENTER NUMBER OF PAGES\n";
	cin>>m;
	mcopy = m;
	m = m-n;
	vector<int>v(n);
	cout<<"ENTER THE PAGE VALUES\n";
	int track[n];
	f(i,0,n){
		track[i] = n-i;
	}

	f(i,0,n) cin>>v[i];
	cout<<"FIRST "<<n<<" PAGES ARE PUT AT FIRST "<<n<<" AVAILABLE SPACES\n\n\n";
	print_page_table(v);

	int page_cost=min(m,n);
	if(m > 0)
	{

		while(m) 
		{
			int index = 0;
			int value = INT_MIN;
			m--;
			int currval;
			cin>>currval;
			cout<<"For "<<currval<<" pagevalue,";
			bool flag = 1;
			f(i,0,n)
			{
				if(v[i] == currval) {
					cout<<"PAGE ALREADY EXIST\n";
					flag = 0;
					track[i] = 1;

					print_page_table(v);

					break;
				}
				if(track[i] > value)
					value = track[i],index = i;
			}
			if(flag == 0)
				continue;
			page_cost++; //page cost increased
			cout<<currval<<" IS PUT AT "<<index+1<<" LOCATION REPLACING "<<v[index]<<"\n";

			f(i,0,n) track[i]++; //track of each page not used increased by one
			v[index] = currval; //value replaced

			track[index] = 1;
			print_page_table(v);
			// f(i,0,n) cout<<track[i]<<"\t";
			// cout<<"\n";


		}
	}
	cout<<"FINAL POSITIONS ARE\n";
	if(mcopy>n){
		f(i,0,n) cout<<v[i]<<"\t";
	}
	else{
		f(i,0,m) cout<<v[i]<<"\t";
	}
	cout<<"\n\nPAGE FAULT IS "<<page_cost<<"\n\n";
}

/* 
INPUT-
4
13
7 0 1 2 0 3 0 4 2 3 0 3 2
*/