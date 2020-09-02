#include <bits/stdc++.h>
using namespace std;
#define N 1000005
struct Treap{
    int val[N],siz[N],num[N],son[N][2],rnd[N];
    int rt,cnt;
    Treap(int n){
        rt = 0;
        cnt = 0;
    }
    void insert(int x);
    void removeByRank(int r);
    int getSiz();
    void print();
private:
    void print(int rt);
    void insert(int x,int &rt);
    void remove(int &rt);
    void removeByRank(int r,int &rt);
    void rotate(int &rt,int t);
};
void Treap::print(){
    this->print(this->rt);
}
void Treap::print(int rt){
    if(!rt) return;
    this->print(son[rt][0]);
    printf("%d %d %d %d %d %d\n",val[rt],num[rt],siz[rt],rnd[rt],son[rt][0],son[rt][1]);
    this->print(son[rt][1]);
}
void Treap::insert(int x){
    this->insert(x,this->rt);
}
void Treap::insert(int x,int &rt){
    if(!rt) {
        rt = ++cnt;
        siz[rt]=1;
        val[rt]=x;
        num[rt]=1;
        rnd[rt] = rand();
        son[rt][0]=0;
        son[rt][1]=0;
        return;
    }
    siz[rt]++;
    if(val[rt]==x) {
        num[rt]++;
        return;
    }
    int t = val[rt]<x;
    insert(x,son[rt][t]);
    if(rnd[son[rt][t]]>rnd[rt]){
        rotate(rt,t);
    }
}
int Treap::getSiz(){
    return this->siz[this->rt];
}
void Treap::rotate(int &rt,int t){
    int s = son[rt][t];
    int p = son[s][t^1];
    son[rt][t] = p;
    son[s][t^1]=rt;
    siz[rt] = siz[son[rt][0]]+siz[son[rt][1]]+num[rt];
    rt=s;
    siz[rt] = siz[son[rt][0]]+siz[son[rt][1]]+num[rt];
}
void Treap::remove(int &rt){
    if(son[rt][0]==0||son[rt][1]==0){
        rt = son[rt][0]+son[rt][1];
        return;
    }
    if(rnd[son[rt][0]]<rnd[son[rt][1]]) {
        rotate(rt,0);
        remove(son[rt][1]);
    }
    else {
        rotate(rt,1);
        remove(son[rt][0]);
    }
}
void Treap::removeByRank(int r){
    this->removeByRank(r,this->rt);
}
void Treap::removeByRank(int r,int &rt){
    siz[rt]--;
    if(siz[son[rt][0]]>=r) {
        removeByRank(r,son[rt][0]);
        return;
    }
    r-=siz[son[rt][0]];
    if(num[rt]>=r){
        num[rt]--;
        if(num[rt]==0){
            remove(rt);
        }
        return;
    }
    removeByRank(r-num[rt],son[rt][1]);
}
int n,q;
int main()
{
    cin>>n>>q;
    Treap *tr = new Treap(n+q);
    for(int x,i=1;i<=n;i++){
        scanf("%d",&x);
        tr->insert(x);
        //tr->print();
    }
    for(int x,i=1;i<=q;i++){
        scanf("%d",&x);
        if(x>0) tr->insert(x);
        else tr->removeByRank(-x);
        //tr->print();
    }
    if(tr->getSiz()==0){
        puts("0");
    }else{
        printf("%d\n",tr->val[tr->rt]);
    }
}