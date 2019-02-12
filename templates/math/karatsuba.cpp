#include<bits/stdc++.h>
typedef std::vector<int> vi;
vi add(vi &p1, vi &p2) {
    vi res(std::max(p1.size(), p2.size()));
    for(int i=0;i<p1.size();++i)
        res[i]+=p1[i];
    for(int i=0;i<p2.size();++i)
        res[i]+=p2[i];
    return res;
}
vi sub(vi &p1, vi &p2) {
    vi res(std::max(p1.size(), p2.size()));
    for(int i=0;i<p1.size();++i)
        res[i]+=p1[i];
    for(int i=0;i<p2.size();++i)
        res[i]-=p2[i];
    return res;
}
vi mul(vi &p1, vi &p2) {
    if(p1.size() < 50 || p2.size() < 50) {
        vi ret(p1.size()+p2.size()-1);
        for(int i=0;i<p1.size();++i)
            for(int j=0;j<p2.size();++j)
                ret[i+j]+=p1[i]*p2[j];
         return ret;
    }
    int sz=p1.size()/2;
    vi p3(p1.begin()+sz,p1.end()),p4(p2.begin()+sz,p2.end());
    p1.resize(sz);
    p2.resize(sz);
    vi AB = add(p3, p1), CD = add(p4, p2);
    vi AC = mul(p3,p4), MUL = mul(AB, CD), BD = mul(p1,p2);
    vi SUM = add(BD,AC);
    MUL = sub(MUL, SUM);
    vi res(AC.size()+2*sz);
    for(int i=0;i<BD.size();++i)
        res[i]+=BD[i];
    for(int i=0;i<MUL.size();++i)
        res[i+sz]+=MUL[i];
    for(int i=0;i<AC.size();++i)
        res[i+2*sz]+=AC[i];
    return res;
}
int main() {
    int N,M;
    scanf("%d%d",&N,&M);
    vi v1(std::max(N,M)+1),v2(std::max(N,M)+1);
    for(int i=0;i<=N;++i)
        scanf("%d",&v1[i]);
    for(int i=0;i<=M;++i)
        scanf("%d",&v2[i]);
    vi res=mul(v1,v2);
    for(int i=0;i<=N+M;++i)
        printf("%d ",res[i]);
    putchar('\n');
}
