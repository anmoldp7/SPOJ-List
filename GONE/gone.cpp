//Baisc problem on Digit DP.
//Find more problems at http://codeforces.com/blog/entry/53960
#include<bits/stdc++.h>
#define LEN 9
#define SUM 81
#define TGT 2
#define MAXN 100
using namespace std;
int dp[LEN+1][SUM+1][TGT+1];
bool siev[MAXN+1];
int dpSol(int idx,int sum,int tgt,vector<int> &v){
	if(idx==-1)
		if(!siev[sum])
			return 1;
		else
			return 0;
	if(dp[idx][sum][tgt]!=-1&&tgt!=1)
		return dp[idx][sum][tgt];
	int k,ret=0;
	if(tgt)
		k=v[idx];
	else
		k=9;
	for(int i=0;i<=k;i++)
		if(i==v[idx])
			ret+=dpSol(idx-1,sum+i,tgt,v);
		else
			ret+=dpSol(idx-1,sum+i,0,v);
	if(tgt!=1)
		dp[idx][sum][tgt]=ret;
	return ret;
}
int mkSol(int x){
	vector<int> v;
	int s=x;
	while(s>0){
		v.push_back(s%10);
		s/=10;
	}
	for(int i=0;i<=LEN;i++)
		for(int j=0;j<=SUM;j++)
			for(int k=0;k<=TGT;k++)
				dp[i][j][k]=-1;
	s=dpSol(v.size()-1,0,1,v);
	return s;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t,x,y;
	siev[0]=siev[1]=true;
	for(int i=2;i*i<=MAXN;i++)
		if(!siev[i])
			for(int j=i*i;j<=MAXN;j+=i)
				siev[j]=true;
	cin>>t;
	while(t--){
		cin>>x>>y;
		cout<<mkSol(y)-mkSol(x-1)<<"\n";
	}
	return 0;
}
