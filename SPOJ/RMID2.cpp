    #include<bits/stdc++.h>
    #include<bits/extc++.h>
    using namespace __gnu_pbds;
    int T;
    tree<std::pair<int,int>,null_type,std::less<std::pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>B;
    int main() {
        for(scanf("%d",&T);T--;) {
            B.clear();
            for(int i=0,a;;i++) {
                scanf("%d",&a);
                if(!a) break;
                if(~a) {
                    B.insert({a,i});
                } else if(a){
                    auto it = B.find_by_order(B.size()-1>>1);
                    printf("%d\n",it->first);
                    B.erase(it);
                }
            }
        }
    }
