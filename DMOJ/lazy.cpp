#include<bits/stdc++.h>
namespace IO {
    constexpr const int _bufsz = 1<<16;
    char _inbuf[_bufsz+1];
    char *_inptr=_inbuf;
    char _sign,_c;
    static inline char getchar() {
        return *_inptr?*_inptr++:(_inbuf[fread_unlocked(_inptr=_inbuf,1,_bufsz,stdin)]='\0',*_inptr);
    }
    template<typename T>static inline void readInt(T &t) {
        while((_c=::getchar())<=' ');
        if((_sign=_c=='-')) _c=::getchar();
        for(t=_c-'0';(_c=::getchar())>='0';t=t*10+_c-'0');
        if(_sign) t=-t;
    }
    template<typename T>static inline void readUInt(T &t) {
        while((_c=::getchar())<=' ');
        for(t=_c-'0';(_c=::getchar())>='0';t=t*10+_c-'0');
    }
};
typedef long long ll;
const int MN=1e5+4;
const ll INF=0x3f3f3f3f3f3f3f3f;
int N,Q,H;
bool lz1[MN];
ll st[MN*2],lz2[MN];
inline void build() {
    H = std::__lg(N) + 1;
    for(int i=N-1;~i;--i) {
        st[i] = std::min(st[i*2],st[i*2+1]);
        lz1[i] = 1, lz2[i] = 0;
    }
}
inline void _mod(int i, bool l1, ll l2) {
    if(i < N) lz1[i] &= l1, lz2[i] = lz2[i] * l1 + l2;
    st[i] = st[i] * l1 + l2;
}
inline void psh(int i) {
    for(int h=H;h;--h) {
        int k = i>>h;
        if(k >= N) continue;
        if(!lz1[k]||lz2[k]) {
            _mod(k*2,lz1[k],lz2[k]);
            _mod(k*2+1,lz1[k],lz2[k]);
            lz1[k]=1,lz2[k]=0;
        }
    }
}
inline void upd(int i) {
    st[i] = std::min(st[i*2],st[i*2+1])*lz1[i]+lz2[i];
}
inline void mod(int l,int r,bool l1,ll l2) {
    psh(l+=N),psh(r+=N);
    for(bool bl=0,br=0;l<=r;l/=2,r/=2) {
        if(bl) upd(l-1);
        if(br) upd(r+1);
        if(l&1) _mod(l++,l1,l2), bl=1;
        if(!(r&1)) _mod(r--,l1,l2), br=1;
    }
    for(l--,r++;r;l/=2,r/=2) {
        upd(l),upd(r);
    }
}
inline ll qry(int l,int r) {
    psh(l+=N),psh(r+=N);
    ll ret=INF;
    for(;l<=r;l/=2,r/=2) {
        if(l&1) ret=std::min(ret,st[l++]);
        if(!(r&1)) ret=std::min(ret,st[r--]);
    }
    return ret;
}
int main() {
    IO::readUInt(N);
    IO::readUInt(Q);
    for(int i=1;i<=N;++i)
        IO::readInt(st[i+N]);
    build();
    for(int i=0,a,b,c,d;i<Q;++i) {
        IO::readUInt(a);
        IO::readUInt(b);
        IO::readUInt(c);
        if(a < 3) {
            IO::readInt(d);
            mod(b,c,2-a,d);
        } else {
            printf("%lld\n", qry(b,c));
        }
    }
}
