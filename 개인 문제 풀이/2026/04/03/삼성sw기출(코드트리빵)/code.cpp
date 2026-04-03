#include <bits/stdc++.h>
using namespace std;
int n,m;
const int map_size = 30;
int adj[map_size][map_size];
int visited[map_size][map_size];
vector<pair<int,int>> stores;
int block_map[map_size][map_size];
vector<pair<int,int>> persons; //idx순서대로 사람들의 위치
int arrive_check[30];

int ans;
int dx[4] = {0,-1,1,0};
int dy[4] = {-1,0,0,1};
int dis=1e8; //3번로직을 위해 최단 베이스캠프까지의 거리 저장
int cnt; //점거된 편의점 갯수 모든 도착 확인용

int BFS(int i, int j, int goal_i, int goal_j){ //거리를 주는 BFS
    //fill(&visited[0][0], &visited[0][0]+30*30, 0);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            // step[i][j] = INF;
        }
    }
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push(make_pair(i,j));
    while(q.size()){
        pair<int,int> curr_i = q.front(); q.pop();
        int y = curr_i.first;
        int x = curr_i.second;
        //기저사례
        if(y == goal_i && x==goal_j){
            return visited[y][x]; //거리값 리턴
            //cout << "goal arrive!" << i << j <<endl;
        }
        for(int k=0; k<4; k++){
            int ny = y + dy[k];
            int nx = x + dx[k];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(visited[ny][nx]!=0) continue;
            if(block_map[ny][nx]) continue;
            visited[ny][nx] = visited[y][x]+1;
            q.push(make_pair(ny,nx));
        }
    }
    return 1e8;
}
    
int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++){ //맵 입력
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }
    for(int i=0; i<m; i++){ //편의점 위치 벡터에 입력
        int tmp_i, tmp_j;
        cin >> tmp_i >> tmp_j;
        stores.push_back(make_pair(tmp_i-1, tmp_j-1));
    }
    
    int now_t = 0;
    //cout << now_t << endl;
    persons.resize(m + 1);
    while(1){
        if(cnt == m) break; //모두 도착하면 루프 종료
        // 1. 사람들을 편의점을 향해 움직이는 로직
        
        // 1.1 그리드에 사람이 있는지 검사하는 로직 없으면 다음 단계로
        int now_y = 0;
        int now_x = 0;
        if(now_t != 0) { 
            for(int i=0; i<now_t && i<m; i++){
                if(arrive_check[i]) continue; //이미 도착했으면 스킵하는 로직 
                int tmp_dis=1e8;
                int tmp_ret=1e8;
                // i의 위치(베이스캠프나 실제 이동된 위치) 로딩
                for(int j=0; j<4; j++){
                    int ny = persons[i].first + dy[j];
                    int nx = persons[i].second + dx[j];
                    if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
                    if(block_map[ny][nx]) continue;
                    tmp_ret = BFS(ny, nx, stores[i].first, stores[i].second); //4방위중 1곳에서 편의점까지의 거리 리턴
                    if(tmp_dis > tmp_ret){ //4방위중 이번에 간 곳이 제일 짧으면 dis, 사람 위치 업데이트
                        tmp_dis = tmp_ret;
                        now_y = ny;
                        now_x = nx;
                    }
                }
                persons[i].first = now_y;
                persons[i].second = now_x;
            }
        }

        // 2. 편의점에 도착하면 그 편의점은 블록맵에 추가하는 로직
        for(int i=0; i<now_t && i<m; i++){
            if(!arrive_check[i]){ //도착 체크 안되어있으면 검사
                if(persons[i].first == stores[i].first && persons[i].second == stores[i].second){
                    block_map[stores[i].first][stores[i].second] = 1; //사람 위치와 블록 위치가 같으면 점거 하기
                    arrive_check[i] = 1; //도착 체크
                    cnt++;
            }
            }
            
        }

        // 3. now_t 가 m보다 작거나 같을때 m사람이 편의점과 가장 가까운 베이스캠프로 들어가는 로직
        if(now_t < m){
            //편의점에서 시작해서 모든 베이스캠프까지의 거리 검사
            // 그 검사는 현재 전역맵을 기준으로
            pair<int,int> target_base;
            dis = 1e8; // 거리값 초기화
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    if(adj[i][j]==1 && !block_map[i][j]){ //맵의 모든 베이스캠프 검사, 점거 안됐을때, 
                        int store_i = stores[now_t].first;
                        int store_j = stores[now_t].second;
                        int now_dis = BFS(store_i, store_j, i, j);
                        if(now_dis < dis){ //시간 자체가 새로운 베이스가 짧으면 교체
                            dis = now_dis;
                            target_base = make_pair(i,j); //최단거리 갱신된 베이스는 타겟베이스로 지정
                        }
                        if(now_dis == dis){ //시간이 만약 같으면
                            if(target_base.first < i) continue; //원래베이스 행이 더 작으면 유지
                            if(target_base.first > i){ //새로운 베이스 행이 더 작으면 교체
                                dis = now_dis;
                                target_base = make_pair(i,j); 
                            }
                            if(target_base.first == i){ //행이 같으면 열 비교
                                if(target_base.second < j) continue; //원래 베이스 열이 더 작으면 유지
                                if(target_base.second > j){ //새로운 베이스 열이 더 작으면 교체
                                    dis = now_dis;
                                    target_base = make_pair(i,j); 
                                }
                            }
                        }
                    }
                }
            }
            //검사 끝남
            block_map[target_base.first][target_base.second] = 1; //해당 베이스캠프 점거
            persons[now_t] = make_pair(target_base.first, target_base.second); //베이스캠프로 위치 설정
        }
        // 3.1 들어가자마자 그 베이스캠프는 블록맵에 추가

        now_t++;
        //cout << now_t << endl;
    }

    cout << now_t;
    return 0;
}
