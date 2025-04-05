#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
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
  int n;
  cin>>n;
  int cnt=0;
  int ans=0;

  for(int i=1;i<=n;i++){
        for(int b=0;b*b<=n;b++){
            for(int a=0;a*a<=n;a++){
               if(i==binpow(2,a)*(b*b)){
                cnt++;
               }
            }
        }

    //     for(int a=0;a<=n;a++){
    //       if(binpow(2,a)<i){
    //         cnt++;
    //       }
    //  }
    
  }  



  cout<<cnt<<endl;

    return 0;
}
