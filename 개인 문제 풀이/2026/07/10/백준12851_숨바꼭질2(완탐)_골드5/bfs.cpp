#include <bits/stdc++.h>
using namespace std;
int visited[200001];
int cnt_t=0;

int main(){
    int n, k;
    cin >> n >> k;
    if(n == k){
        puts("0");
        puts("1");
        return 0;
    }
    //fill(&visited[0], &visited[0]+200001, -1);
    visited[n] = 1;
    queue<int> q;
    q.push(n);
    
    while(q.size()){
        int here = q.front(); q.pop();

        for(int next : {here-1, here+1, here*2}){
            if(next < 0 || next > 100000) continue;

            if(visited[next]){ //이전에 방문한 적 있음
                if(visited[here] + 1 > visited[next]){ //이전 방문이 더 최단
                    continue;
                }
            }

            if(next == k){ //목적지
                if(!visited[next] || visited[here] + 1 < visited[next]){ //새로운 최단 갱신
                    visited[next] = visited[here] + 1;
                    cnt_t = 1;
                }
                else if(visited[here] + 1 == visited[next]){ //이전과 같은 최단 거리
                    cnt_t++;
                }
                continue;
            }

            q.push(next);
            visited[next] = visited[here] + 1;
        }
    }

    cout << visited[k] - 1 <<'\n';
    cout << cnt_t;
    return 0;
}
