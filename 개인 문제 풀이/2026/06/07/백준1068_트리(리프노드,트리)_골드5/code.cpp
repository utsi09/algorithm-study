#include <bits/stdc++.h>
using namespace std;
int n;
int cut;
vector<int> adj[51];

int dfs(int here){
    //cout << "iunw";
    int ret=0;
    int child=0;
    for(int tmp : adj[here]){
        if(tmp == cut) continue;
        ret += dfs(tmp);
        child++;
    }
    if(child == 0) return 1;
    return ret;
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        int tmp;
        cin >> tmp;
        if(tmp == -1) continue;
        //cout << "push " << tmp <<'\n';
        adj[tmp].push_back(i);
        //cout << "push comp" << tmp <<'\n';
    }
    //cout << "Awd";
    cin >> cut;
    //cout << "Awd";
    if(cut == 0) cout << "0";
    else cout << dfs(0);
    return 0;
}
