#include <bits/stdc++.h>
using namespace std;

int n,m,k;
int dy[4] = {-1,0,1,0}; //상우하좌
int dx[4] = {0,1,0,-1};
priority_queue<int> adj[21][21];

struct player{
  int r,c;
  int score = 0;
  int d;//방향
  int power;
  int gun = 0;
};
vector<player> players;


void losers_move(int loser_idx){
  player& loser = players[loser_idx];
  adj[loser.r][loser.c].push(loser.gun);
  loser.gun = 0; //총 내려놓기
  int ny = loser.r + dy[loser.d];
  int nx = loser.c + dx[loser.d];
  while(1){
    bool danger_checker = false;
    // 다른 플레이어와 만나는지 검사
    for(int j=0; j<players.size(); j++){
      if(loser_idx==j) continue;
      player& other = players[j];
      if(ny == other.r && nx == other.c){ //이동할곳에 겹치는지
        danger_checker = true;
      }
    }
    //격자를 벗어나거나 다른 플레이어있으면 90도로 방향을 틀어서 1칸 이동
    if(ny<0 || nx<0 || ny>=n || nx>=n || danger_checker == true){ 
      loser.d = (loser.d + 1) % 4;
      ny = loser.r + dy[loser.d];
      nx = loser.c + dx[loser.d];
    }
    else break;
  }
  loser.r = ny;
  loser.c = nx;
  if(adj[ny][nx].top() > loser.gun){ //내총보다 더 쎈총있으면 교체
      int my_gun = loser.gun;
      adj[ny][nx].push(my_gun);
      loser.gun = adj[ny][nx].top();
      adj[ny][nx].pop();
  }
}

void move_player(){
  for(int i=0; i<players.size(); i++){ //각 플레이어 이동
    player& me = players[i];
    int ny = me.r + dy[me.d];
    int nx = me.c + dx[me.d];
    
    if(ny<0 || nx<0 || ny>=n || nx>=n){ //격자를 벗어날경우 정반대로 방향을 틀어서 1칸 이동
      me.d = (me.d + 2) % 4;
      ny = me.r + dy[me.d];
      nx = me.c + dx[me.d];
    }

    
    me.r = ny;
    me.c = nx;
    //이동 상호작용
    int winner_idx = -1;
    int loser_idx = -1;
    bool other_checker = false;
    for(int j=0; j<players.size(); j++){
      if(i==j) continue;
      player& other = players[j];
      if(me.r == other.r && me.c == other.c){ // 다른 플레이어와 만나면
        other_checker = true;
        if(me.power + me.gun > other.power + other.gun){ //내가 더 쎄면
          winner_idx = i;
          loser_idx = j;
        }
        else if(me.power + me.gun < other.power + other.gun){ //상대가 더 쎄면
          winner_idx = j;
          loser_idx = i;
        }
        else{//같으면
          if(me.power > other.power){ //내 재능 더 세면
            winner_idx = i;
            loser_idx = j;
          }
          else{  //상대 재능 더 세면
            winner_idx = j;
            loser_idx = i;
          }
        }
        players[winner_idx].score += abs((players[winner_idx].power+players[winner_idx].gun) - (players[loser_idx].power+players[loser_idx].gun)); 
        losers_move(loser_idx);
      }
    }
    int win_r = players[winner_idx].r;
    int win_c = players[winner_idx].c;

    if(other_checker && adj[win_r][win_c].top() > 0){ //내총보다 더 쎈총있으면 교체
      if(players[winner_idx].gun < adj[win_r][win_c].top()){
        int my_gun = players[winner_idx].gun;
        adj[win_r][win_c].push(players[winner_idx].gun);
        players[winner_idx].gun = adj[win_r][win_c].top();
        adj[win_r][win_c].pop();
      }
    }
    if(other_checker == false && me.gun < adj[ny][nx].top()){
      int my_gun = me.gun;
      adj[ny][nx].push(me.gun);
      me.gun = adj[ny][nx].top();
      adj[ny][nx].pop();
    }
  }
  return;
}


int main(){
  cin >> n >> m >> k;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      int tmp; cin >> tmp;
      adj[i][j].push(tmp);
    }
  }
  for(int i=0; i<m; i++){
    player tmp;
    cin >> tmp.r >> tmp.c >> tmp.d >> tmp.power;
    tmp.r--;
    tmp.c--;
    players.push_back(tmp);
  }

  for(int t=0; t<k; t++){
    move_player();
  }
  for(int i=0; i<players.size(); i++){
    cout <<players[i].score << " ";
  }
  
  return 0;
}
