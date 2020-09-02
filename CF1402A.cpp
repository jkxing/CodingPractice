#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100000+5;
const int mod = 1000000007;
int n;
int h[N],w[N];
ll sw[N];
int st[N],top;
ll ans;
ll C1(ll k,ll n){
    return (n+n-k+1)*k/2%mod;
}
ll C2(ll x){
    x=(x+mod)%mod;
    return (x*(x-1)/2)%mod;
}
ll getAns(int pos){
    int H = h[st[top]]-max(h[pos],h[st[top-1]]);
    int W = sw[pos-1]-sw[st[top-1]]+1;
    return C1(H,h[st[top]])*C2(W)%mod;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",h+i);
    for(int i=1;i<=n;i++) {
        scanf("%d",w+i);
        sw[i] = (sw[i-1]+w[i])%mod;
    }
    for(int i=1;i<=n;i++){
        while(top>0&&h[st[top]]>=h[i]){
            ans=(ans+getAns(i))%mod;
            top--;
        }
        st[++top]=i;
    }
    while(top>0){
        ans=(ans+getAns(n+1))%mod;
        top--;
    }
    printf("%lld\n",ans);
}