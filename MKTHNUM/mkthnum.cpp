//Basic problem on persistent data structure
#include<bits/stdc++.h>
#define MAXN 100010
#define MAXQ 5010
using namespace std;
int arr[MAXN+1],arr1[MAXN+1];
unordered_map<int,int> mp,mprev;
struct node{
	struct node *left,*right;
	int val;
	node(){}
	node(struct node *l,struct node *r,int c){
		left=l;
		right=r;
		val=c;
	}
};
struct node *version[MAXN+1];
int getMidUtil(int x,int y){
	return (x+((y-x)/2));
}
void mkBuild(int ss,int se,struct node *nd){
	if(ss==se){
		return;
	}
	int mid=getMidUtil(ss,se);
	nd->left=new struct node(NULL,NULL,0);
	mkBuild(ss,mid,nd->left);
	nd->right=new struct node(NULL,NULL,0);
	mkBuild(mid+1,se,nd->right);
}
void mkUpgrade(int ss,int se,int x,int w,struct node *prev,struct node *nd){
	if(x>se||x<ss)
		return;
	if(ss==x&&se==x){
		(nd->val)=(prev->val)+w;
		return;
	}
	int mid=getMidUtil(ss,se);
	if(x<=mid){
		nd->right=prev->right;
		nd->left=new struct node(NULL,NULL,0);
		mkUpgrade(ss,mid,x,w,prev->left,nd->left);
	}
	else{
		nd->left=prev->left;
		nd->right=new struct node(NULL,NULL,0);
		mkUpgrade(mid+1,se,x,w,prev->right,nd->right);
	}
	nd->val=(nd->left->val)+(nd->right->val);
}
int mkQry(int ss,int se,int qs,int qe,struct node *nd){
	if(ss>qe||qs>se||ss>se)
		return 0;
	if(qs<=ss&&se<=qe)
		return (nd->val);
	int mid=getMidUtil(ss,se),x=0;
	if(nd->left!=NULL)
		x+=mkQry(ss,mid,qs,qe,nd->left);
	if(nd->right!=NULL)
		x+=mkQry(mid+1,se,qs,qe,nd->right);
	return x;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,q,x,y,z,l,r,mid;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		arr1[i]=arr[i];
	}
	sort(arr1+1,arr1+n+1);
	x=0;
	mp[arr1[1]]=x;
	mprev[x++]=arr1[1];
	for(int i=2;i<=n;i++)
		if(arr1[i]!=arr1[i-1]){
			mp[arr1[i]]=x;
			mprev[x++]=arr1[i];
		}
	version[0]=new struct node(NULL,NULL,0);
	mkBuild(0,n-1,version[0]);
	for(int i=1;i<=n;i++){
		version[i]=new struct node(NULL,NULL,0);
		mkUpgrade(0,n-1,mp[arr[i]],1,version[i-1],version[i]);
	}
	while(q--){
		cin>>x>>y>>z;
		l=0;
		r=n-1;
		mid=l+((r-l)/2);
		while(l<r){
			if((mkQry(0,n-1,0,mid,version[y])-mkQry(0,n-1,0,mid,version[x-1]))>=z)
				r=mid;
			else
				l=mid+1;
			mid=l+((r-l)/2);
		}
		cout<<mprev[mid]<<"\n";
	}
	return 0;
} 
