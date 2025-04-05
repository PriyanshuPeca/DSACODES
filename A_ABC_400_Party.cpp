
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
void solve(){

}
signed main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    long double a;
    //t=1;
    cin>>a;
    if(ceil(400/a)==floor(400/a)){
        cout<<(400*1LL/a) <<endl;
    }
    else{
        cout<<-1<<endl;
    }
  
    return 0;
}
