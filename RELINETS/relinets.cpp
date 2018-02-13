//A good problem on bridges and bitmasks.
#include<bits/stdc++.h>
#define MAXN 21
using namespace std;
int disc[MAXN+1],low[MAXN+1],dsu[MAXN+1],siz[MAXN+1],tim,edgex[MAXN+1],edgey[MAXN+1],edge[MAXN+1],art;
vector<int> v[MAXN+1];
void init(int n){
	for(int i=1;i<=n;i++){
		dsu[i]=i;
		siz[i]=1;	
	}
}
int root_find(int x){
	while(x!=dsu[x]){
		dsu[x]=dsu[dsu[x]];
		x=dsu[x];
	}
	return x;
}
void uni(int x,int y){
	x=root_find(x);
	y=root_find(y);
	if(x!=y){
		if(siz[x]>=siz[y]){
			siz[x]+=siz[y];
			dsu[y]=x;
		}
		else{
			siz[y]+=siz[x];
			dsu[x]=y;
		}
	}
}
void dfs(int x,int p){
	disc[x]=low[x]=++tim;
	for(int i=0;i<v[x].size();i++)
		if(disc[v[x][i]]==-1){
			dfs(v[x][i],x);
			low[x]=min(low[v[x][i]],low[x]);
			if(disc[x]<low[v[x][i]])
				art++;
		}
		else if(v[x][i]!=p)
			low[x]=min(disc[v[x][i]],low[x]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m,t=1,x;
	long long cst,cst1;
	cin>>n>>m;
	do{
		cst=1LL<<60;
		for(int i=0;i<m;i++)
			cin>>edgex[i]>>edgey[i]>>edge[i];
		for(int i=0;i<(1<<m);i++){
			cst1=x=0;
			tim=-1;
			art=0;
			init(n);
			for(int i=1;i<=n;i++)
				v[i].clear();
			for(int j=1;j<=n;j++)
				disc[j]=-1;
			for(int j=0;j<m;j++){
				if((1<<j)&i){
					cst1+=edge[j];
					uni(edgex[j],edgey[j]);
					v[edgex[j]].push_back(edgey[j]);
					v[edgey[j]].push_back(edgex[j]);
				}
			}
			for(int j=1;j<=n;j++)
				if(disc[j]==-1)
					dfs(j,j);
			for(int j=1;j<=n;j++)
				if(dsu[j]==j)
					x++;
			if(x==1&&!art)
				cst=min(cst1,cst);
			for(int j=1;j<=n;j++)
				v[j].clear();
		}
		if(cst!=1LL<<60)
			cout<<"The minimal cost for test case "<<t++<<" is "<<cst<<".\n";
		else
			cout<<"There is no reliable net possible for test case "<<t++<<".\n";
		cin>>n>>m;
	}while(n!=0||m!=0);
	return 0;	
} 
