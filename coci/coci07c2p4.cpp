#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> bbst;
const int MAXN=1e5+4;
int N,A[MAXN],ind[MAXN];
bbst B;
int main() {
    scanf("%d",&N);
    for(int i=1;i<=N;++i) {
        scanf("%d",A+i);
        ind[A[i]]=i;
        B.insert(i);
    }
    for(int i=1,j=N,k=1;i<=j;k^=1) {
        if(k) {
            printf("%d\n", B.order_of_key(ind[i]));
            B.erase(B.find(ind[i]));
            i++;
        } else {
            printf("%d\n", B.size()-1-B.order_of_key(ind[j]));
            B.erase(B.find(ind[j]));
            j--;
        }
    }
}
