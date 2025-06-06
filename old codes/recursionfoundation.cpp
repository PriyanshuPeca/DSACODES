#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
int fact(int x){
    if(x==0){
        return 1;
    }
    return x*fact(x-1);
}
void solve(){
cout<<fact(3);
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

f