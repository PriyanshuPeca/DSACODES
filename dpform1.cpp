// #include<bits/stdc++.h>
// using namespace std;

// #define int long long
// #define endl '\n'

// const int MOD=1e9+7;
// const int INF=LLONG_MAX>>1;
// int n;
// string s;
// int dp[100100][4];
// int rec(int i,int prev){
// //pruning 

// //base case
// if(i==n){
// return 1;
// }

// //cache check
// if(prev!=-1 && dp[i][prev]!=-1){
//     return dp[i][prev];
// }


// //compute
// int ans=0;
// if(s[i]=='?'){
//     for(int ch=0;ch<4;ch++){
//         if(ch==prev)continue;
//         ans+=rec(i+1,ch);
//     }
// }
// else{
//     if((s[i]-'A')==prev){
//         return 0;
//     }
//     else{
//         ans=rec(i+1,(s[i]-'A'));
//     }
// }


// //save and return
// if(prev!=-1) dp[i][prev]=ans;
// return ans;
// }
// signed main(){

//     ios_base::sync_with_stdio(0);
//     cin.tie(0),cout.tie(0);
//     int t;
//     cin>>n>>s;
//     memset(dp,-1,sizeof(dp));
//     cout<<rec(0,-1);
//     return 0;
// }


//
// 4N(1+AVG TRANSTION 3)==0(N)
//circular/////////////////////////////////////////
// #include<bits/stdc++.h>
// using namespace std;

// #define int long long
// #define endl '\n'

// const int MOD=1e9+7;
// const int INF=LLONG_MAX>>1;
// int n;
// string s;
// int dp[100100][4][4];
// int rec(int i,int prev,int first){
// //pruning 

// //base case

// if(i==n){
// if(prev==first && n!=1)return 0;
//     return 1;
// }

// //cache check
// if(prev!=-1 && dp[i][prev][first]!=-1){
//     return dp[i][prev][first];
// }


// //compute
// int ans=0;
// if(s[i]=='?'){
//     for(int ch=0;ch<4;ch++){
//         if(ch==prev)continue;
//         if(i==0)
//         ans+=rec(i+1,ch,ch);
//         else
//         ans+=rec(i+1,ch,first);
//     }
// }
// else{
//     if((s[i]-'A')==prev){
//         return 0;
//     }
//     else{
//         if(i==0)
//         ans=rec(i+1,(s[i]-'A'),s[i]-'A');
//         else{
//         ans=rec(i+1,(s[i]-'A'),first);
//         }
//     }
// }


// //save and return
// if(prev!=-1) dp[i][prev][first]=ans;
// return ans;
// }
// signed main(){

//     ios_base::sync_with_stdio(0);
//     cin.tie(0),cout.tie(0);
//     int t;
//     cin>>n>>s;
//     // if(n==1){
//     //     if(s[0]=='?')cout<<4<<endl;
//     //     else
//     //     cout<<1<<endl;
//     // }
//     memset(dp,-1,sizeof(dp));
//     cout<<rec(0,-1,-1);
//     return 0;
// }



//////////lexi 



#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int MOD=1e9+7;
const int INF=LLONG_MAX>>1;
int n;
string s;
int dp[100100][4][4];
int rec(int i,int prev,int first){
//pruning 

//base case

if(i==n){
if(prev==first && n!=1)return 0;
    return 1;
}

//cache check
if(prev!=-1 && dp[i][prev][first]!=-1){
    return dp[i][prev][first];
}


//compute
int ans=0;
if(s[i]=='?'){
    for(int ch=0;ch<4;ch++){
        if(ch==prev)continue;
        if(i==0)
        ans+=rec(i+1,ch,ch);
        else
        ans+=rec(i+1,ch,first);
    }
}
else{
    if((s[i]-'A')==prev){
        return 0;
    }
    else{
        if(i==0)
        ans=rec(i+1,(s[i]-'A'),s[i]-'A');
        else{
        ans=rec(i+1,(s[i]-'A'),first);
        }
    }
}


//save and return
if(prev!=-1) dp[i][prev][first]=ans;
return ans;
}
string temp;
void generatei(int i,int prev,int first)
{
cout<<i<<" "<<prev<<" "<<first<<endl;
   // pruning 

//base case

if(i==n){
return;
}

//cache check
// if(prev!=-1 && dp[i][prev][first]!=-1){
//     return dp[i][prev][first];
// }


//compute

if(s[i]=='?'){
    for(int ch=0;ch<4;ch++){
        cout<<ch<<" "<<prev<<" "<<endl;
        if(ch==prev)continue;
        if(i==0){
        if(rec(i+1,ch,ch)>0){
         temp+=char(ch+'A');
         generatei(i+1,ch,ch);
         return;
        }

        }
        else{
            cout<<ch<<endl;
            if(rec(i+1,ch,first)>0){
                temp+=char(ch+'A');
                generatei(i+1,ch,first);
                return;
            }
    }
    }
}
else{
    if((s[i]-'A')==prev){
        return ;
    }
    else{
        if(i==0){
        if(rec(i+1,(s[i]-'A'),s[i]-'A')>0){
temp+=char(s[i]);
generatei(i+1,(s[i]-'A'),s[i]-'A');
return;
        }
        }
        else{
        if(rec(i+1,(s[i]-'A'),first)>0){
            temp+=(s[i]);
            generatei(i+1,(s[i]-'A'),first);
            return;
        }
        }
    }

}
}

signed main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>n>>s;
    // if(n==1){
    //     if(s[0]=='?')cout<<4<<endl;
    //     else
    //     cout<<1<<endl;
    // }
    
    memset(dp,-1,sizeof(dp));
    int ans=rec(0,-1,-1);
    cout<<ans<<endl;
    if(ans>0){
       generatei(0,-1,-1); 
    }
    cout<<temp<<endl;
    return 0;
}