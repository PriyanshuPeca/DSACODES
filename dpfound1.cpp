#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
int n;
int arr[100];

int save[100][100];
int savevalue[100][100];

int  rec(int i,int x){
     //pruning 
    if(x<0)return 0;

    //base case
    if(i==n){
        if(x==0)return 1;
        else return 0;
    }

    // cache check
    if(save[i][x]){
        return savevalue[i][x];
    }

    // calcucaltion
    int ans=rec(i+1,x)+rec(i+1,x-arr[i]);

    //sace and return
    savevalue[i][x]=ans;
    save[i][x]=1;
    
    return ans;
}
signed main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
cin>>n;
for(int i=0;i<n;i++){
    cin>>arr[i];
}
int x;
cin>>x;

memset(save,0,sizeof(save));
cout<<rec(0,x)<<endl;
}
