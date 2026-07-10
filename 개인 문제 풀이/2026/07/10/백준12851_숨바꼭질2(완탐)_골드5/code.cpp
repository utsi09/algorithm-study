#include <bits/stdc++.h>
using namespace std;
int cnt = 0;
int visited[100000]; //해당 칸에 방문한 시간
int cnt_t = 0;


void solve(int n, int k, int time){  
    //cout << "arrive : " << n << ", time : " << time <<'\n';
    if(n == k) {
        if(time == visited[k]){
            cnt++;
            //cout << "arrive k!! time: " << time << ", cnt : " << cnt <<'\n';
        }
        else if(time < visited[k]){
            cnt=1;
            //cout << "arrive k!! time: " << time << ", cnt : " << cnt <<'\n';
        }
        visited[n] = time;
        return;
    }
    visited[n] = time; //도달한 시간 - 방문배열에 저장
    for(int i=0; i<3; i++){
        if(i==0){
            if(n-1 < 0) continue;
            if(visited[n-1] < time + 1) continue; // 이전에 방문했으면 x - 사이클 안되게
            solve(n-1, k, time + 1);
        }
        else if(i == 1){
            if(n+1 > k) continue;
            if(visited[n+1] < time + 1) continue; // 이전에 방문했으면 x - 사이클 안되게
            solve(n+1, k, time + 1);
        }
        else if(i == 2){
            if(n*2 > k*2) continue;
            if(visited[n*2] < time + 1) continue; // 이전에 방문했으면 x - 사이클 안되게
            solve(n*2, k, time + 1);
        }
    }
    return; //
}


int main(){
    int n, k;
    cin >> n >> k;
    memset(visited, 98765432, sizeof(visited));
    solve(n, k, 0);
    cout << visited[k] << '\n';
    cout << cnt;
    return 0;
}
