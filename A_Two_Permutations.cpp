#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
void solve(){
int n,a,b;
cin>>n>>a>>b;
if(a==n && b==n){
    cout<<"Yes"<<endl;
}
else if(a+b+2<=n){
    cout<<"Yes"<<endl;
}
else{
    cout<<"No"<<endl;
}
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
