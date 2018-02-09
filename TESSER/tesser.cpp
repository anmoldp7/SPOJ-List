//A nice variation of classic Knuth Morris Pratt Algorithm for finding occurences of pattern in text.
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int lps[100000],n,arr[100000],t,i,j,flag;
    string str;
    cin>>t;
    while(t--){
        flag=0;
        cin>>n;
        for(i=0;i<n;i++)
            cin>>arr[i];
        cin>>str;
        lps[0]=0;
        j=0;
        for(i=1;i<str.size();i++){
            while(j!=0&&str[i]!=str[j])
                j=lps[j-1];
            if(str[i]==str[j])
                j++;
            lps[i]=j;
        }
        j=0;
        for(i=0;i<(n-1)&&!flag;i++){
            while((!((str[j]=='G'&&arr[i]<arr[i+1])||(str[j]=='L'&&arr[i]>arr[i+1])||(str[j]=='E'&&arr[i]==arr[i+1])))&&j!=0)
                j=lps[j-1];
            if(((str[j]=='G'&&arr[i]<arr[i+1])||(str[j]=='L'&&arr[i]>arr[i+1])||(str[j]=='E'&&arr[i]==arr[i+1])))
                j++;
            if(j==str.size())
                flag=1;
        }
        if(flag)
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}
 
