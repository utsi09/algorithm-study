#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> a_idx;
vector<int> b_idx;
int a_cnt = 0;
int b_cnt = 0;
int cnt = 98765432;
vector<int> flexity; //인구수
int visited[11];
vector<vector<int>> adj(11); //밀접한 지역

void db_team(){ //팀 디버깅
    cout << "< team a > \n";
    for(int t : a_idx){
        cout << t << " ";
    }
    cout << '\n';
    cout << "< team b > \n";
    for(int t : b_idx){
        cout << t << " ";
    }
    cout << '\n';
}

int check_adj(const vector<int>& v, int flag){
    int n=0;
    fill(&visited[0], &visited[0]+11, 0);
    int start = v[0];
    int ret=0;
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while(q.size()){
        int here = q.front();
        n++;
        //cout << here << " ";
        ret += flexity[here]; //인구수 더하기
        q.pop();
        for(int next : adj[here]){
            if(visited[next]) continue;
            bool checker = false;
            for(int tmp : v){ //팀이 아니면 안감
                if(tmp == next) checker = true;
                break;
            }
            if(checker == false) continue;
            visited[next] = 1;
            q.push(next);
        }
    }
    //cout <<'\n';
    //cout << n << " vs " << v.size() <<'\n';
    if(n != v.size()) return 0; //모두 인접하지않으면 
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int tmp;
    for(int i=0; i<n; i++){
        cin >> tmp;
        flexity.push_back(tmp);
    }
    for(int i=0; i<n; i++){
        int nn; cin >> nn;
        for(int j=0; j<nn; j++){
            cin >> tmp;
            adj[i].push_back(tmp-1);
        }
    }
    
    for(int i=(1<<n)-2; i>0; i--){
        int idx = 0;
        a_idx.clear();
        b_idx.clear();
        for(int j= 1<<(n-1); j>0; j/=2){
            bool tmp = (i & j);
            if(!tmp){
                a_idx.push_back(idx);
            } 
            else {
                b_idx.push_back(idx);
            }
            idx++;
        } //팀 선정 완료
        a_cnt = 0;
        b_cnt = 0;
        //db_team();
        a_cnt = check_adj(a_idx, 0);
        b_cnt = check_adj(b_idx, 1);

        //cout << a_cnt << " vs " << b_cnt <<'\n';
        if(a_cnt == 0 || b_cnt == 0) continue;
        cnt = min(cnt, abs(a_cnt - b_cnt));
        //cout << cnt <<'\n';
    }
    if(cnt == 98765432) cout << "-1\n";
    else cout << cnt << '\n';
    return 0;
}
