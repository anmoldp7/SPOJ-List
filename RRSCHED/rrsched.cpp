//A very interesting problem involving Round Robin Scheduling. Problems involving CS concepts are much more fun. Solved using binary indexed tree/fenwick tree.
#include<bits/stdc++.h>
#define MAXN 50010
using namespace std;
int bitree[MAXN+1];
long long soln[MAXN+1];
pair<int,int> pr[MAXN+1];
int bitQry(int x){
	int s=0;
	while(x>0){
		s+=bitree[x];
		x-=(x&(-1*x));
	}
	return s;
}
void bitUpd(int x,int val,int siz){
	if(x==0)
		return;
	while(x<=siz){
		bitree[x]+=val;
		x+=(x&(-1*x));
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,x,y;
	long long sol,ss,fx;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>pr[i].first;
		pr[i].second=i+1;
	}
	sort(pr,pr+n);
	for(int i=1;i<=n;i++)
		bitUpd(i,1,n);
	x=0;
	y=1;
	fx=0LL;
	for(int i=0;i<n;i++){
		ss=bitQry(n);
		if(pr[i].second>x){
			sol=pr[i].first-y;
			sol*=ss;
			sol+=(bitQry(pr[i].second)-bitQry(x));
			fx+=sol;
			soln[pr[i].second]=fx;
		}
		else{
			sol=pr[i].first-y-1;
			sol*=ss;
			sol+=((ss-bitQry(x))+bitQry(pr[i].second));
			fx+=sol;
			soln[pr[i].second]=fx;
		}
		bitUpd(pr[i].second,-1,n);
		x=pr[i].second;
		y=pr[i].first;
	}
	for(int i=1;i<=n;i++)
		cout<<soln[i]<<"\n";
	return 0;
} 
