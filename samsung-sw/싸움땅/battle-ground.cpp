#include <bits/stdc++.h>
using namespace std;
int n,m,k,turn;
priority_queue<int> adj[21][21]; //총
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

struct player
{
  int x,y,d,s;
  int score=0;
  int gun=0;
};
vector<player> ps;


void init(){
  cin >> n >> m >> k;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      int tmp; cin >> tmp;
      adj[i][j].push(tmp); 
    }
  }
  for(int i=0; i<m; i++){
    player tmp;
    cin >> tmp.y >> tmp.x >> tmp.d >> tmp.s;
    tmp.x -= 1; tmp.y -= 1;
    ps.push_back(tmp);
  }
  return;
}


void search_grid(){
  for(int i=0; i<ps.size(); i++){
    int myi = ps[i].y + dy[ps[i].d];
    int myj = ps[i].x + dx[ps[i].d];
    if(myi<0 || myj<0 || myi>=n || myj>=n){
      ps[i].d = (ps[i].d+2) % 4; //정반대 방향으로
      myi = ps[i].y + dy[ps[i].d];
      myj = ps[i].x + dx[ps[i].d];
    }
    ps[i].y = myi;
    ps[i].x = myj; 
    int winner = i;
    int loser = -1;
    // 플레이어 있는지 확인
    for(int j=0; j<ps.size(); j++){
      if(i==j) continue;
      if(myi == ps[j].y && myj == ps[j].x){ //플레이어와 조우
        int my_ability = ps[i].s + ps[i].gun;  //해당 플레이어의 초기 능력치와 가지고 있는 총의 공격력의 합
        int your_ability = ps[j].s + ps[j].gun;
        int prize = abs(my_ability - your_ability);
        if(my_ability > your_ability){
          winner = i;
          loser = j;
        }
        else if(my_ability < your_ability){
          winner = j;
          loser = i;
        }
        else{ //같으면
          if(ps[i].s > ps[j].s){
            winner = i; loser = j;
          }
          else{
            winner = j; loser = i;
          }
        }
        ps[winner].score += prize;
      }
      if(loser != -1) break; //플레이어 조우는 한번만
    }
    //cout << winner << " : winner , loser :" << loser << '\n';
    if(loser != -1){ //진 플레이어가 있으면
      adj[myi][myj].push(ps[loser].gun); //총 내려놓기
      ps[loser].gun = 0;
      for(int dd=0; dd<4; dd++){ //방향바꾸면서 찾기
        int nd = (ps[loser].d + dd)%4;
        int ny = ps[loser].y + dy[nd];
        int nx = ps[loser].x + dx[nd];
        bool cant_move = false;
        if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
        for(int jj=0; jj<ps.size(); jj++){
          if(loser == jj) continue;
          if(ny == ps[jj].y && nx == ps[jj].x) cant_move = true;
        }    
        if(!cant_move){
          ps[loser].y = ny;
          ps[loser].x = nx;   
          ps[loser].d = nd;
          if(adj[ny][nx].size()){ //총있으면 총줍기
            ps[loser].gun = adj[ny][nx].top();
            adj[ny][nx].pop();
          }
          break;
        }
      }
    }
    //승자는 그 격자에서 가장 쎈 총 줍기
    if(adj[myi][myj].size()){
      adj[myi][myj].push(ps[winner].gun); 
      //ps[winner].gun = 0;
      ps[winner].gun = adj[myi][myj].top();
      adj[myi][myj].pop();
    }
  }
  return;
}

void db_player(){
  cout << "turn : " << turn << "\n";
  for(const player p : ps){
    cout << p.y << "," << p.x <<'\n';
  }
}

int main(){
  init();
  //db_player();
  for(turn=1; turn<=k; turn++){
    //1.플레이어는 각각 방향대로 1칸 이동
    //2.이동한 곳 탐색
    search_grid();
    //db_player();
  }
  for(player p : ps){
    cout << p.score << " ";
  }
  return 0;
}