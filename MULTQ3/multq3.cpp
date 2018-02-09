//Neat problem on segment trees
#include<bits/stdc++.h>
using namespace std;
int st0[500000],st1[500000],st2[500000],lazy[500000],x,y,z;
int getmidutil(int x,int y){
    return (x+((y-x)/2));
}
void init(int ss,int se,int si){
    if(ss>se)
        return;
    int mid=getmidutil(ss,se);
    if(ss==se){
        st0[si]=1;
        return;
    }
    st0[si]=(se-ss+1);
    init(ss,mid,(2*si)+1);
    init(mid+1,se,(2*si)+2);
}
void updateutil(int ss,int se,int qs,int qe,int si){
    lazy[si]%=3;
    if(lazy[si]==1){
        x=st0[si];
        y=st1[si];
        z=st2[si];
        st0[si]=z;
        st1[si]=x;
        st2[si]=y;
        if(ss!=se){
            lazy[(2*si)+1]++;
            lazy[(2*si)+2]++;
        }
        lazy[si]=0;
    }
    else if(lazy[si]==2){
        x=st0[si];
        y=st1[si];
        z=st2[si];
        st0[si]=y;
        st1[si]=z;
        st2[si]=x;
        if(ss!=se){
            lazy[(2*si)+1]+=2;
            lazy[(2*si)+2]+=2;
        }
        lazy[si]=0;
    }
    if(ss>qe||se<qs||ss>se)
        return;
    if(qs<=ss&&se<=qe){
        x=st0[si];
        y=st1[si];
        z=st2[si];
        st0[si]=z;
        st1[si]=x;
        st2[si]=y;
        if(ss!=se){
            lazy[(2*si)+1]++;
            lazy[(2*si)+2]++;
        }
        return;
    }
    int mid=getmidutil(ss,se);
    updateutil(ss,mid,qs,qe,(2*si)+1);
    updateutil(mid+1,se,qs,qe,(2*si)+2);
    st0[si]=st0[(2*si)+1]+st0[(2*si)+2];
    st1[si]=st1[(2*si)+1]+st1[(2*si)+2];
    st2[si]=st2[(2*si)+1]+st2[(2*si)+2];
}
int getsumutil(int ss,int se,int qs,int qe,int si){
    lazy[si]%=3;
    if(lazy[si]==1){
        x=st0[si];
        y=st1[si];
        z=st2[si];
        st0[si]=z;
        st1[si]=x;
        st2[si]=y;
        if(ss!=se){
            lazy[(2*si)+1]++;
            lazy[(2*si)+2]++;
        }
        lazy[si]=0;
    }
    else if(lazy[si]==2){
        x=st0[si];
        y=st1[si];
        z=st2[si];
        st0[si]=y;
        st1[si]=z;
        st2[si]=x;
        if(ss!=se){
            lazy[(2*si)+1]+=2;
            lazy[(2*si)+2]+=2;
        }
        lazy[si]=0;
    }
    if(ss>se||qs>se||qe<ss)
        return 0;
    if(qs<=ss&&se<=qe)
        return st0[si];
    int mid=getmidutil(ss,se);
    return (getsumutil(ss,mid,qs,qe,(2*si)+1)+getsumutil(mid+1,se,qs,qe,(2*si)+2));
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q,flag,x,y;
    cin>>n>>q;
    init(0,n-1,0);
    while(q--){
        cin>>flag>>x>>y;
        if(!flag)
            updateutil(0,n-1,x,y,0);
        else
            cout<<getsumutil(0,n-1,x,y,0)<<"\n";
    }
    return 0;
} 
