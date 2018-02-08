//A variation of KQUERY supposed to be solved via online processing. Achieved through persistent segment tree.
#include<bits/stdc++.h>
#define MAXN 30010
#define MAXQ 200010
using namespace std;
int arr[MAXN+1],arr1[MAXN+1];
unordered_map<int,int> mp,mprev;
int getMidUtil(int x,int y){
	return (x+((y-x)/2));
}
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
struct node *version[MAXQ+1];
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
	if(x>se||x<ss||ss>se)
		return;
	if(x==ss&&x==se){
		nd->val=(prev->val)+w;
		return;
	}
	int mid=getMidUtil(ss,se);
	if(x<=mid){
		nd->right=prev->right;
		nd->left=new struct node(NULL,NULL,0);
		mkUpgrade(ss,mid,x,w,prev->left,nd->left);
		nd->val=(nd->left->val)+(nd->right->val);
	}
	else{
		nd->left=prev->left;
		nd->right=new struct node(NULL,NULL,0);
		mkUpgrade(mid+1,se,x,w,prev->right,nd->right);
		nd->val=(nd->left->val)+(nd->right->val);
	}
}
int mkQry(int ss,int se,int qs,int qe,struct node *nd){
	if(qs>se||qe<ss)
		return 0;
	if(qs<=ss&&se<=qe)
		return (nd->val);
	int mid=getMidUtil(ss,se),x=0;
	if(nd->left!=NULL)
		x+=mkQry(ss,mid,qs,qe,nd->left);
	if(nd->right!=NULL)
		x+=(mkQry(mid+1,se,qs,qe,nd->right));
	return x;
}
int main(){
 
	int n,q,x=0,y,z,l,r,mid,sol=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",(arr+i));
		arr1[i]=arr[i];
	}
	sort(arr1+1,arr1+n+1);
	for(int i=1;i<=n;i++)
		if(arr1[i]!=arr1[i-1])
			mp[arr1[i]]=x++;
	version[0]=new struct node(NULL,NULL,0);
	mkBuild(0,n-1,version[0]);
	for(int i=1;i<=n;i++){
		version[i]=new struct node(NULL,NULL,0);
		mkUpgrade(0,n-1,mp[arr[i]],1,version[i-1],version[i]);
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d%d%d",&x,&y,&z);
		x^=sol;
		y^=sol;
		z^=sol;
		x=max(1,x);
		y=min(n,y);
		if(z>arr1[n]||x>y){
			printf("%d\n",0);
			sol=0;
		}
		else if(z<arr1[1]){
			printf("%d\n",(y-x+1));
			sol=(y-x+1);	
		}
		else{
			l=1;
			r=n;
			mid=l+((r-l+1)/2);
			while(l<r){
				if(arr1[mid]<=z)
					l=mid;
				else	
					r=mid-1;
				mid=l+((r-l+1)/2);
			}
			z=mp[arr1[mid]];
			sol=mkQry(0,n-1,z+1,n-1,version[y])-mkQry(0,n-1,z+1,n-1,version[x-1]);
			printf("%d\n",sol);
		}
	}
	return 0;
}  
