//Good problem on DSU and trees.
#include<bits/stdc++.h>
using namespace std;
int colors[100100],dsu[100100],siz[100100];
vector<int> v[100100];
void init(int n){
    for(int i=0;i<n;i++){
        dsu[i]=i;
        siz[i]=1;
        colors[i]=-1;
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
    if(x==y)
        return;
    if(siz[x]>=siz[y]){
        dsu[y]=x;
        siz[x]+=siz[y];
    }
    else{
        dsu[x]=y;
        siz[y]+=siz[x];
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,x,y,z,q;
    cin>>n;
    init(n);
    for(int i=0;i<(n-1);i++){
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    cin>>q;
    while(q--){
        cin>>x>>y>>z;
        if(x==1){
            colors[y]=z;
            for(int i=0;i<v[y].size();i++)
                if(colors[y]==colors[v[y][i]])
                    uni(y,v[y][i]);
        }
        if(x==2){
            if(root_find(y)==root_find(z))
                cout<<"YES\n";
            else
                cout<<"NO\n";
        }
    }
    return 0;
}
