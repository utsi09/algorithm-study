#include <bits/stdc++.h>
using namespace std;
int n;
struct quest{
    int s,i,p;
};
vector<quest> v;
int visited[51];
int dp[1000][1000];
int ret = -98765432;



int solve(int i, int j){
    int& here = dp[i][j];
    if(here != -1) return here;
    here = 0;
    int pnt = 0; //누적된 포인트
    vector<int> idx;
    for(int q=0; q<v.size(); q++){ // 모든 퀘스트 순회
        //cout << q << " : idx\n";
        int ss = v[q].s;
        int ii = v[q].i;
        int pp = v[q].p;
        if(i < ss && j < ii) continue;
        here++;
        if(!visited[q]){
            pnt += pp;
            visited[q] = 1;
            idx.push_back(q);
        }
    }

    for(int d=0; d<=pnt; d++){
        int this_s = min(1000, i+ d);
        int this_i = min(1000, j+pnt - d);
        here= max(here, solve(this_s, this_i)); 
    }     

    for(int tmp : idx){
        visited[tmp] = 0;
    }

    return here;
}

int main(){
    cin >> n;
    for(int t=0; t<n; t++){
        quest tmp;
        cin >> tmp.s >> tmp.i >> tmp.p;
        v.push_back(tmp);
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(1,1);
    return 0;
}

/*

dp[int][pnt]

*/
