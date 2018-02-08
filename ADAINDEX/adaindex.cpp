//Simple problem on tries.
#include<bits/stdc++.h>
#define MAXN 26
using namespace std;
struct trieNode{
	int val;
	struct trieNode *chld[MAXN];
};
struct trieNode *mkNode(){
	struct trieNode *pNode=NULL;
	pNode=(struct trieNode*)malloc(sizeof(trieNode));
	if(pNode){
		pNode->val=0;
		for(int i=0;i<MAXN;i++)
			pNode->chld[i]=NULL;
	}
	return pNode;
}
void insertWord(struct trieNode *root,string str){
	struct trieNode *pNode=root;
	for(int i=0;i<str.size();i++){
		if(pNode->chld[str[i]-'a']==NULL)
			pNode->chld[str[i]-'a']=mkNode();
		pNode=pNode->chld[str[i]-'a'];		
	}
	pNode->val++;
}
int dfs(struct trieNode *root){
	for(int i=0;i<MAXN;i++)
		if(root->chld[i]!=NULL)
			root->val+=dfs(root->chld[i]);
	return root->val;
}
int prefQry(struct trieNode *root,string str){
	struct trieNode *pNode=root;
	for(int i=0;i<str.size();i++)
		if(pNode->chld[str[i]-'a']==NULL)
			return 0;
		else
			pNode=pNode->chld[str[i]-'a'];
	return pNode->val;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	string str;
	struct trieNode *root;
	cin>>n>>m;
	root=mkNode();
	for(int i=0;i<n;i++){
		cin>>str;
		insertWord(root,str);
	}
	dfs(root);
	for(int i=0;i<m;i++){
		cin>>str;
		cout<<prefQry(root,str)<<"\n";
	}
	return 0;
} 
