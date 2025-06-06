#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
void solve(){
int a,b,xk,xy,qx,qy;
cin>>a>>b;cin>>xk>>xy;cin>>qx>>qy;
int ans=0;
if(a==b){
    int dx[8]={a,a,-a,-a};
    int dy[8]={b,-b,b,-b};
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
int kingx=xk+dx[i];
int kingy=xy+dy[i];
int queenx=qx+dx[j];
int queeny=qy+dy[j];
if(kingx==queenx && queeny==kingy){
    ans++;
}

        }
    }
}
else{
    int dx[8]={a,a,-a,-a,b,b,-b,-b};
    int dy[8]={b,-b,b,-b,-a,a,a,-a};
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
int kingx=xk+dx[i];
int kingy=xy+dy[i];
int queenx=qx+dx[j];
int queeny=qy+dy[j];
if(kingx==queenx && queeny==kingy){
    ans++;
}

        }
    }
}
cout<<ans<<endl;

}
signed main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    //t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
