#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9;
const int INF=1e9;
int binpow(int a, int b) {
    if (b == 0)
        return 1;
    if (b % 2) {
        return a * binpow(a, b - 1) ;
    } else {
        int temp = binpow(a, b / 2);
        return temp * temp;
    }
}

signed main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    int ans=0;
    bool flag=1;
    for(int i=0;i<=m;i++){
        ans+=binpow(n,i);
if(ans>INF){
    cout<<"inf"<<endl;
    flag=0;
    break;
    }
   
}
if(flag){
    cout<<ans<<endl;
}
}
