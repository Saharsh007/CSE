#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b) for(int i=a;i<b;i++)

int n;

void print_page_table(int v[]){
	cout<<"CURRENT PAGE TABlE\t\t\t\t\t\t";
	f(i,0,n) cout<<v[i]<<"\t";
	cout<<"\n\n";
}

int main(){
	cout<<"ENTER SIZE OF PAGE TABLE\n";
	cin>>n;
	int pagetable[n];

	int m,mcopy;
	cout<<"ENTER NUMBER OF PAGES\n";
	cin>>m;
	mcopy = m;
	m = m-n;
	int v[mcopy];
	cout<<"ENTER THE PAGE VALUES\n";
	f(i,0,mcopy) cin>>v[i];
	cout<<"FIRST "<<n<<" PAGES ARE PUT AT FIRST "<<n<<" AVAILABLE SPACES\n\n\n";
	f(i,0,n) pagetable[i] = v[i];
	print_page_table(pagetable);

	int page_cost=min(m,n);
	if(m > 0)
	{

		while(m) 
		{
			m--;
			int currval = v[mcopy-m-1];
			cout<<"For "<<currval<<" pagevalue,";
			bool flag = 1;
			f(i,0,n)
			{
				if(pagetable[i] == currval) {
					cout<<"PAGE ALREADY EXIST\n";
					flag = 0;

					print_page_table(pagetable);

					break;
				}
			}

			if(flag == 0)
				continue;

			//page does not exist so we will place the page somewhere
			int tempcost[n]; // for temp cost of each position

			f(i,0,n) tempcost[i] = mcopy;

			f(i,0,n){
				f(j,mcopy-m-1,mcopy){

					if(v[j] == pagetable[i]){
						tempcost[i] = j;
						break; 
					}
				}
			}
			cout<<"\ntempcost is\t\t\t\t\t\t\t\t";
			f(i,0,n) cout<<tempcost[i]<<"\t";
			cout<<"\n";
			//now we know cost of all page slots, we choose the one with min value
			int index = 0, tempval = INT_MIN;
			f(i,0,n){
				if(tempcost[i] > tempval) tempval = tempcost[i],index = i;
			}

			page_cost++; //page cost increased
			cout<<currval<<" IS PUT AT "<<index+1<<" LOCATION REPLACING "<<pagetable[index]<<"\n";
			pagetable[index] = currval;
			print_page_table(pagetable);



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
3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/