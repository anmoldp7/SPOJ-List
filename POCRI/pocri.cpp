//A problem on Josephus Algorithm.
#include<bits/stdc++.h>
using namespace std;
int josephus(int n,int k){
    if(n==1)
        return 1;
    else
        return ((josephus(n-1,k)+k-1)%n+1);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int arr[101],n;
    for(int i=0;i<13;i++)
        arr[i]=1;
    for(int n=13;n<=100;n++){
        int flag=1,c;
        for(int i=1;flag;i++){
            c=josephus(n,i)-i+1;
            while(c<=0)
                c+=n;
            if(c==13){
                flag=0;
                arr[n]=i;
            }
        }
    }
    cin>>n;
    while(n!=0){
        cout<<arr[n]<<"\n";
        cin>>n;
    }
    return 0;
}

