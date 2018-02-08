//Simple LCA problem. Solution using sparse table.
#include<bits/stdc++.h>
#define MAXN 100010
#define MAXM 20
using namespace std;
bool vis[MAXN+1];
vector<pair<long long,int>> v[MAXN+1];
int spT[(2*MAXN)+1][MAXM+1],trav[(2*MAXN)+1],id[MAXN+1],level[MAXN+1],pt[MAXN+1],maxPow[MAXN+1],s=0;
long long dist[MAXN+1];
void dfs(int x,int l,int p,long long d){
	trav[s++]=x;
	level[x]=l;
	pt[x]=p;
	dist[x]=d;
	for(int i=0;i<v[x].size();i++)
		if(v[x][i].second!=p){
			dfs(v[x][i].second,l+1,x,d+v[x][i].first);
			trav[s++]=x;
		}
}
void mkTable(){
	for(int i=0;i<s;i++)
		spT[i][0]=trav[i];
	for(int j=1;(1<<j)<=s;j++)
		for(int i=(1<<j)-1;i<s;i++)
			if(level[spT[i][j-1]]<level[spT[i-(1<<(j-1))][j-1]])
				spT[i][j]=spT[i][j-1];
			else if(level[spT[i][j-1]]>level[spT[i-(1<<(j-1))][j-1]])
				spT[i][j]=spT[i-(1<<(j-1))][j-1];
			else
				spT[i][j]=min(spT[i][j-1],spT[i-(1<<(j-1))][j-1]);
}
int lcq(int x,int y){
	int x1=id[x],y1=id[y];
	if(x1>y1){
		x1^=y1;
		y1^=x1;
		x1^=y1;
	}
	if(level[spT[y1][maxPow[y1-x1]]]<level[spT[x1+(1<<maxPow[y1-x1])-1][maxPow[y1-x1]]])
		return spT[y1][maxPow[y1-x1]];
	return spT[x1+(1<<maxPow[y1-x1])-1][maxPow[y1-x1]];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t,n,x,y,k,d;
	long long z;
	string str;
	maxPow[1]=0;
	for(int i=1;(1<<i)<=MAXN;i++)
		maxPow[(1<<i)]=i;
	for(int i=2;i<=MAXN;i++)
		maxPow[i]=max(maxPow[i-1],maxPow[i]);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>x>>y>>z;
			v[x].push_back(make_pair(z,y));
			v[y].push_back(make_pair(z,x));
		}
		dfs(1,0,1,0);
		mkTable();
		for(int i=0;i<s;i++)
			if(!vis[trav[i]]){
				vis[trav[i]]=true;
				id[trav[i]]=i;
			}
		cin>>str;
		while(str[0]!='D'||str[1]!='O'){
			if(str[0]=='D'){
				cin>>x>>y;
				d=lcq(x,y);
				cout<<dist[x]+dist[y]-(2*dist[lcq(x,y)])<<"\n";
			}
			else{
				cin>>x>>y>>k;
				d=lcq(x,y);
				if((level[x]-level[d]+1)>=k){
					while(--k)
						x=pt[x];
					cout<<x<<"\n";
				}
				else{
					k=level[x]+level[y]-(2*level[d])+1-k;
					while(k--)
						y=pt[y];
					cout<<y<<"\n";
				}
			}
			cin>>str;
		}
		s=0;
		for(int i=1;i<=n;i++){
			vis[i]=false;
			v[i].clear();
		}
	}
	return 0;
} 
