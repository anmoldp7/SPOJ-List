//Great problem to understand path compression in DSU
#include<bits/stdc++.h>
using namespace std;
int dsu[30000],dis[30000];
void init(int n){
    for(int i=0;i<=n;i++){
        dsu[i]=i;
        dis[i]=0;
    }
}
void uni(int x,int y){
    dsu[x]=y;
    dis[x]=abs(x-y)%1000;
}
long long distance(int x){
    long long s=0;
    while(x!=dsu[x]){
        dis[x]=dis[dsu[x]]+dis[x];
        dsu[x]=dsu[dsu[x]];
        s+=dis[x];
        x=dsu[x];
    }
    return s;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t,n,x,y;
    string str;
    cin>>t;
    while(t--){
        cin>>n;
        init(n);
        cin>>str;
        while(str[0]!='O'){
            if(str[0]=='I'){
                cin>>x>>y;
                uni(x,y);
            }
            else if(str[0]=='E'){
                cin>>x;
                cout<<distance(x)<<"\n";
            }
            cin>>str;
        }
    }
    return 0;
}
