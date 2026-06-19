#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> tree;

void update(int i, int v){
    while(i < tree.size()){
        tree[i] += v;
        i += (i & -i);
    }
}

int sum(int i){
    int ret=0;
    while(i > 0){
        ret += tree[i];
        i -= (i & -i);
    }
    return ret;
}

int query(int l, int r){
    return (sum(r) - sum(l-1));
}

int main() {
    vector<int> data = {3, 4, 10, 11};
    n = data.size(); // 4
    tree.resize(n+1, 0);

    for(int i=0; i<n; i++){
        update(i+1, data[i]);
    }   

    cout << query(1,4) <<'\n';
    cout << query(1,3) << '\n';

    return 0;
}
