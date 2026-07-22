#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int adj[21][21];
int visited[21][21];
int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};
int score = 0;
vector<pair<int,int>> tails; //각 팀별 꼬리들 저장

void db_map(){
  cout <<"--- map --- \n";
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cout << adj[i][j] << " ";
    }
    cout << '\n';
  }

  cout <<"--- map --- \n";
}

pair<int,int> move_bfs(int tail_r, int tail_c){
  int value = adj[tail_r][tail_c];
  pair<int,int> tail_move;
  adj[tail_r][tail_c] = 4;
  visited[tail_r][tail_c] = 1;
  queue<pair<int,int>> q;
  int head_r = -1;
  int head_c = -1;
  bool is_ring = false;
  q.push({tail_r, tail_c});
  while(q.size()){
    int ii = q.front().first;
    int jj = q.front().second;
    q.pop();
    for(int dd=0; dd<4; dd++){
      int ny = ii + dy[dd];
      int nx = jj + dx[dd];
      if(ny<0 || nx<0 || ny>=n || nx>=n || visited[ny][nx] || adj[ny][nx] == 0) continue;
      if(ii == tail_r&& jj == tail_c && adj[ny][nx] == 1){ //첫 스타트인데 1과 연결돼있으면 링 형태
        is_ring = true;
        continue;
      }
      if(adj[ny][nx] == 4){ //이동하려는 곳이 4면 스킵
        head_r = ny; //헤드가 이동할 4 저장
        head_c = nx;
        continue;
      }
      if(value == 3){
        tail_move.first = ny;
        tail_move.second = nx;
      }
      visited[ny][nx] = 1; //방문
      int tmp = adj[ny][nx];
      adj[ny][nx] = value;
      value = tmp;
      q.push({ny,nx});
    }
  }
  if(!is_ring){
    adj[tail_r][tail_c] = 4;
    adj[head_r][head_c] = 1;
  }
  if(is_ring){
    adj[tail_r][tail_c] = 1;
  }
  return tail_move;
}

// ~ 구현 15분
void move_team(){
  
  for(pair<int,int>& tail : tails){
    memset(visited, 0, sizeof(visited)); //팀마다 초기화
    tail = move_bfs(tail.first, tail.second); //팀이동
  }


}

//공맞은게 어느팀 몇번째 사람인지, 어떤 
vector<pair<int,int>> find_team(int r, int c){
  visited[r][c] = 1;
  queue<pair<int,int>> q;
  int tail_r = -1;
  int tail_c = -1;
  int head_r = -1;
  int head_c = -1;
  q.push({r, c});
  while(q.size()){
    int ii = q.front().first;
    int jj = q.front().second;
    if(adj[ii][jj] == 1){
      head_r = ii;
      head_c = jj;
    }
    else if(adj[ii][jj] == 3){
      tail_r = ii;
      tail_c = jj;
    }
    q.pop();
    for(int dd=0; dd<4; dd++){
      int ny = ii + dy[dd];
      int nx = jj + dx[dd];
      if(ny<0 || nx<0 || ny>=n || nx>=n || visited[ny][nx] || adj[ny][nx] == 0 || adj[ny][nx] == 4) continue;
      visited[ny][nx] = visited[ii][jj] + 1;
      q.push({ny,nx});
    }
  }
  vector<pair<int,int>> ret;
  ret.push_back({head_r, head_c});
  ret.push_back({tail_r, tail_c});
  return ret;
}

int get_order(int hit_r, int hit_c, int head_r, int head_c){
    bool check[21][21] = {};
    
    int r = head_r;
    int c = head_c;
    int order = 1;

    while(true){
        if(r == hit_r && c == hit_c){
            return order;
        }
        check[r][c] = true;
        for(int d = 0; d < 4; d++){
            int nr = r + dy[d];
            int nc = c + dx[d];

            if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            if(check[nr][nc]) continue;

            // 머리 다음은 반드시 몸통
            if(adj[r][c] == 1 && adj[nr][nc] == 2){
                r = nr;
                c = nc;
                order++;
                break;
            }

            // 몸통 다음은 몸통 또는 꼬리
            if(adj[r][c] == 2 &&
               (adj[nr][nc] == 2 || adj[nr][nc] == 3)){
                r = nr;
                c = nc;
                order++;
                break;
            }
        }
    }
}

void move_ball(int t){
  int turn = ((t / n)%4);
  int ball_r = -1;
  int ball_c = -1;
  int i=0; int j=0;

  if(turn == 0){
    i = t % (n);
    for(j=0; j<n; j++){
      if(adj[i][j] != 0 && adj[i][j] < 4){ //사람이 공에 맞으면
        ball_r = i;
        ball_c = j;
        break;
      }
    }
  }
  
  else if(turn == 1){
    j = t % (n);
      for(int i=n-1; i>=0; i--){
        if(adj[i][j] != 0 && adj[i][j] < 4){ //사람이 공에 맞으면
          ball_r = i;
          ball_c = j;
          break;
      }
    }
  }
  
  else if(turn == 2){
    i = n-1-(t % (n));
    for(int j=n-1; j>=0; j--){
      if(adj[i][j] != 0 && adj[i][j] < 4){ //사람이 공에 맞으면
        ball_r = i;
        ball_c = j;
        break;
      }
    }
  }

  else if(turn == 3){
    j = n - 1 - (t % (n));
      for(int i=0; i<n; i++){
        if(adj[i][j] != 0 && adj[i][j] < 4){ //사람이 공에 맞으면
          ball_r = i;
          ball_c = j;
          break;
      }
    }
  }
  if(ball_r != -1 && ball_c != -1){
    memset(visited, 0, sizeof(visited));
    vector<pair<int,int>> ret = find_team(ball_r,ball_c);
    int order = get_order(ball_r, ball_c, ret[0].first, ret[0].second);
    score += order * order;

    for(pair<int,int>& tail : tails){ //벡터에 적용
      if(tail.first == ret[1].first && tail.second == ret[1].second){
        tail.first = ret[0].first;
        tail.second = ret[0].second;
        break;
      }
    }
    adj[ret[0].first][ret[0].second] = 3;
    adj[ret[1].first][ret[1].second] = 1; //머리와 꼬리 바뀜
  }
}

int main(){
  cin >> n >> m >> k;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> adj[i][j];
      if(adj[i][j] == 3){
        tails.push_back({i,j});
      }
    }
  }

  for(int t=0; t<k; t++){
    // 1. 각 팀의 이동
    move_team();
    move_ball(t);
  }
  cout <<score;

  return 0;
}