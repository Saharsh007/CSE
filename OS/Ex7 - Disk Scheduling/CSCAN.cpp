#include<bits/stdc++.h>
#define f(i,a,b) for(int i = a; i < b; i++)
using namespace std;

int main(){
	int n;
	cout<<"NUMBER OF REQUESTS\n";
	cin>>n;
	int request[n],done[n];
	cout<<"ENTER THE POSITION OF HEAD\n";
	int head;
	cin>>head;
	cout<<"ENTER THE REQUESTS\n";
	f(i,0,n){
		cin>>request[i];
		done[i] = 0;
	}
	sort(request,request+n);

	cout<<"SEEK SEQUENCE IS\n";
	int totalSeek = 0;
	
		int val = INT_MAX,index =0;
		f(j,0,n){
			if(done[j] == 0){
				if(abs(request[j] - head) < val ){
					index = j;
					val = abs(request[j] - head);
				}
			}
		}
		if(request[index] < head){
			int continuefromhere = index+1;

			for(int i = index ; i>=0 ; i--){

				cout<<"Head changed from "<<head<<" to "<<request[i]<<"\n";
				totalSeek += abs(head - request[i]);
				head = request[i];
				done[i] = 1;

			}
			for(int i=n;i>=continuefromhere ;i--){
				cout<<"Head changed from "<<head<<" to "<<request[i]<<"\n";
				totalSeek += abs(head - request[i]);
				head = request[i];
				done[i] = 1;

			}
		}
		else if(request[index] > head){
			int continuefromhere = index-1;

			for(int i = index ; i<n ; i++){

				cout<<"Head changed from "<<head<<" to "<<request[i]<<"\n";
				totalSeek += abs(head - request[i]);
				head = request[i];
				done[i] = 1;

			}
			for(int i = 0 ; i<=continuefromhere ; i++){
				cout<<"Head changed from "<<head<<" to "<<request[i]<<"\n";
				totalSeek += abs(head - request[i]);
				head = request[i];
				done[i] = 1;

			}
		}

	

	
	cout<<"TOTAL SEEK IS "<<totalSeek<<endl;
}

/*INPUT

8
53
98 183 37 122 14 124 65 67


OUTPUT

SEEK SEQUENCE IS
Head changed from 50 to 41
Head changed from 41 to 34
Head changed from 34 to 11
Head changed from 11 to 79
Head changed from 79 to 60
Head changed from 60 to 92
Head changed from 92 to 114
Head changed from 114 to 176
TOTAL SEEK IS 242

*/