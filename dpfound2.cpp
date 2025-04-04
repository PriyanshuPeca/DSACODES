

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
int n;
int arr[100];

int dp[100][100];

int  rec(int i,int x){
    //minimul lement ot make the sum=x form [ito n]
     //pruning 
    if(x<0)return INF;

    //base case
    if(i==n){
        if(x==0)return 0;
        else return INF;
    }

    // cache check
    if(dp[i][x]!=-1){
        return dp[i][x];
    }

    // calcucaltion
    int ans=min(rec(i+1,x),1+rec(i+1,x-arr[i]));

    //sace and return
 dp[i][x]=ans;
    
    return  dp[i][x]=ans;
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

memset(dp,-1,sizeof(dp));
cout<<rec(0,x)<<endl;
}
msddmssss