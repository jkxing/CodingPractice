#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int n;
int a[N],num[2][N][N];
int main()
{
    int t;
    for(cin>>t;t--;)
    {
        cin>>n;
        for(int i=1;i<=n;i++){
            scanf("%d",a+i);
            memcpy(num[0][i],num[0][i-1],sizeof(num[0][i]));
            num[0][i][a[i]]++;
        }
        for(int i=n;i;i--){
            memcpy(num[1][i],num[1][i+1],sizeof(num[1][i]));
            num[1][i][a[i]]++;
        }
        long long ans=0;
        for(int j=2;j<n-1;j++)
        for(int k=j+1;k<n;k++)
        {
            ans+=num[1][k+1][a[j]]*num[0][j-1][a[k]];
        }
        cout<<ans<<endl;
    }
}