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
			for(int i=continuefromhere;i< n ;i++){
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
			for(int i = continuefromhere ; i>=0 ; i--){
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
Head changed from 53 to 65
Head changed from 65 to 67
Head changed from 67 to 98
Head changed from 98 to 122
Head changed from 122 to 124
Head changed from 124 to 183
Head changed from 183 to 37
Head changed from 37 to 14
TOTAL SEEK IS 299

*/