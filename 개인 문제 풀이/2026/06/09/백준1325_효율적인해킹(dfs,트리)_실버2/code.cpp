#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> node[10001];
vector<int> cnt;
int best = 0;
int visited[5001];


int dfs(int here){
    visited[here] = 1;
    int ret=0;
    int child=0;
    for(int tmp : node[here]){
        if(visited[tmp]) continue;
        ret += dfs(tmp);
        child++;
    }
    if(child == 0) return 1;
    return ret+1; 
}

int main(){
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int child, parent;
        cin >> child >> parent;
        node[parent].push_back(child);
    }
    for(int i=1; i<=n; i++){
        fill(&visited[0],&visited[0]+5001,0);
        int ret = dfs(i);
        if(best < ret){
            best = ret;
            cnt.clear();
            cnt.push_back(i);
            //cout << "new!\n";
        }
        else if(best == ret){
            cnt.push_back(i);
            //cout << "same!\n";
        }
    }
    sort(cnt.begin(), cnt.end());
    for(int tmp : cnt){
        cout << tmp << " ";
    }
    
    return 0;
}

/*
a->b

a의 부모는 b다 , 트리문제

*/
