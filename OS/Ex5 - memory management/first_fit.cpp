#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,m;
	cout<<"ENTER NUMBER OF PROCESSES AND NUMBER OF BLOCKS\n";
	cin>>n>>m;
	int process[n];
	int blocks[m];
	int assigned[n];
	bool done[m];

	cout<<"ENTER THE PROCESS SIZES:\n";
	for(int i=0 ;i <n; i++)
		cin>>process[i];	

cout<<"ENTER THE BLOCK SIZES:\n";
	for(int i=0 ;i <m; i++)
		cin>>blocks[i];	

	for(int i=0 ;i <n; i++)
		assigned[i] = -1;
	for(int i=0 ;i <m; i++)
		done[i] = false;

	for(int i=0;i<n ; i++){			//loop for processes
		int j;
		for( j=0; j<m; j++){			//loop for blocks
			if(process[i] <= blocks[j] && done[j] == false){
				blocks[j] -=  process[i];
				assigned[i] = j+1;
				done[j] = true;
				break;
			}
		}

	}

	cout<<"FINAL ASSIGNMENT IS \n";
	for(int i=0;i<n;i++){
		if(assigned[i] != -1)
		cout<<"process no - "<<process[i]<<" is assigned to "<<assigned[i]<<endl;
	else
		cout<<"process no - "<<process[i]<<" is not assigned\n"<<endl;

	}

}

/*
input:
4 5
212 417 112 426
100 500 200 300 600
*/