//My solution to the problem using bitmasks.
#include<bits/stdc++.h>
#define MAXN 1024
#define MAXM 10
using namespace std;
long long arr[MAXN+1];
bool vis[MAXM+1];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	long long x,sol;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		while(x){
			vis[x%10]=true;
			x/=10LL;
		}
		sol=0LL;
		x=1;
		for(int i=0;i<MAXM;i++,x<<=1)
			if(vis[i]){
				sol+=x;
				vis[i]=false;	
			}
		arr[sol]++;
	}
	sol=0LL;
	for(int i=1;i<MAXN;i++)
		if(arr[i]!=0LL){
			sol+=((arr[i]*(arr[i]-1))/2LL);
			for(int j=1;j<i;j++)
				if(arr[j]!=0LL&&(j&i))
					sol+=(arr[i]*arr[j]);
		}
	cout<<sol<<"\n";
	return 0;
}
