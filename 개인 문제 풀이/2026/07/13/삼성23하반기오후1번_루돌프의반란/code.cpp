#include <bits/stdc++.h>
using namespace std;
int n, m, p, c, d;
int rr, rc;
int adj[51][51];
int visited[51][51];

int dy[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; //상하좌우 위왼, 위오, 아오, 아왼
int dx[8] = {0, 0, -1, 1, -1, 1, 1, -1};
int t; //현재 턴
int check_die = 0;

int dy2[4] = {-1, 0, 1, 0}; //상우하좌
int dx2[4] = {0,1,0,-1};

struct santa{
  int sr, sc;
  int score = 0;  
  int is_stune = 0;
  bool is_die = false;
};
vector<santa> santas(31);

void draw_map(){
  cout << "------- map -------\n";
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(i == rr && j == rc){
        cout << "R ";
        adj[i][j] = 1;
        continue;
      }
      bool checker = false;
      for(int ii=0; ii<p; ii++){
        if(i == santas[ii].sr && j == santas[ii].sc){
          cout << "S ";
          adj[i][j] = 2;
          checker = true;
          break;
        }
      }
      if(checker == false) cout << "0 ";
    }
    cout << '\n';
  }

  cout << "------- map -------\n";
}

//가장 가까운 산타의 idx 반환
int get_idx(){ 
  int best_idx = -1;
  int best_ret = 98765432;
  int best_r, best_c;
  for(int idx=0; idx<p; idx++){
    santa& s = santas[idx];
    if(s.is_die == true) continue;
    int this_dis = (rr - s.sr)*(rr - s.sr) + (rc - s.sc)*(rc - s.sc);
    if(best_ret > this_dis){
      best_ret = this_dis;
      best_idx = idx;
      best_r = s.sr;
      best_c = s.sc;
      //cout << s.sr << "," << s.sc << ": changed target santa & " << best_ret << " is distance \n";
      continue;
    }
    else if(best_ret == this_dis){
      if(best_r > s.sr) continue;
      if(best_r == s.sr && best_c > s.sc) continue;
      best_ret = this_dis;
      best_idx = idx;
      best_r = s.sr;
      best_c = s.sc;
      //cout << s.sr << "vs" << s.sc << ": changed target santa & " << best_ret << " is distance \n";
    }
  }
  return best_idx;
}

int get_d(int ny, int nx, int idx){
  santa& s = santas[idx];
  return (ny - s.sr)*(ny - s.sr) + (nx - s.sc)*(nx - s.sc);
}

int get_d_from_s(int ny, int nx){
    // cout << rr << "," << rc << " vs " << ny << "," << nx <<'\n';
    // cout << (rr - ny)*(rr - ny) << "+" << (rc - nx)*(rc - nx) << '\n';
    return (rr - ny)*(rr - ny) + (rc - nx)*(rc - nx);
}

//루돌프가 산타한테 부딪힘 처리
void rtos_boom(int dd, int idx, int flag){
  santa& s = santas[idx];
  if(flag == 0){ //루돌프 직격
    s.sr += dy[dd]*c;
    s.sc += dx[dd]*c;
    s.is_stune = t + 2;
    s.score += c;
  }
  if(flag == 1){ //이동처리만
    s.sr += dy[dd];
    s.sc += dx[dd];
  }
  if(s.sr < 0 || s.sc <0 || s.sr >= n || s.sc >= n){
    s.is_die = true;
    check_die++;
    //cout<< check_die << " : died \n";
    return;
  }
  for(int i=0; i<p; i++){
    if(i == idx) continue;
    santa& ss = santas[i];
    if(s.sr == ss.sr && s.sc == ss.sc){
      rtos_boom(dd, i, 1); //연쇄충돌
    }
  }
}

void move_r(){
  int idx = get_idx();
  int best_dd = -1;
  int best_dis = 98765432;
  for(int dd=0; dd<8; dd++){ //각 방향별로 가장 가까운 방향 고르기
    int ny = rr + dy[dd];
    int nx = rc + dx[dd];
    if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
    int this_d = get_d(ny, nx, idx);

    if(best_dis > this_d){
      //cout << this_d << " : this distance \n";
      best_dis = this_d;
      best_dd = dd;
    }
    // if(best_dis == this_d){
    //     if(dy[best_dd] > dy[dd]) continue; //행이 더 크면 무시
    //     if(dy[best_dd] == dy[dd] && dx[best_dd] > dx[dd]) continue;
    //     best_dis = this_d;
    //     best_dd = dd;
    // }
  }
  if(best_dd != -1){ //실제 이동
    rr += dy[best_dd];
    rc += dx[best_dd];
  }
  for(int idx=0; idx<p; idx++){
    santa& s = santas[idx];
    if(s.is_die == true) continue;
    if(s.sr == rr && s.sc == rc){
      rtos_boom(best_dd, idx, 0);
    }
  }

}

// void bfs(){
//     fill(&visited[0][0], &visited[0][0] + 51*51, 0);
//     visited[rr][rc] = 1;
//     queue<pair<int,int>> q;
//     q.push({rr,rc});
//     while(q.size()){
//         int ii = q.front().first;
//         int jj = q.front().second;
//         q.pop();
//         for(int dd=0; dd<4; dd++){
//             int ny = ii + dy2[dd];
//             int nx = jj + dx2[dd];
//             if(ny<0 || nx<0 || ny>=n || nx>=n) continue;

//             if(visited[ny][nx]) {
//                 //cout << ny <<"," <<nx<< "is cut!\n";
//                 continue;
//             }
//             bool checker = false;
//             for(int idx=0; idx<p; idx++){
//                 if(santas[idx].sr == ny && santas[idx].sc == nx) {
//                     //cout << "is santa seat!! :" << santas[idx].sr <<"," << santas[idx].sc <<'\n';
//                     checker = true; 
//                     continue;
//                 }
//             }
//             if(checker) {continue;} //그곳에 산타 있으면
//             q.push({ny,nx});
//             visited[ny][nx] = visited[ii][jj] + 1;
//         }
//     }
//     return;
// }

//산타가 루돌프한테 부딪힘 처리
void stor_boom(int dd, int idx, int flag){
  santa& s = santas[idx];
  if(flag == 0){ //산타 직격
    //cout << "santa boom!\n";
    //cout << s.sr << "," << s.sc << " >> ";
    s.sr -= dy2[dd]*d;
    s.sc -= dx2[dd]*d;
    //cout << s.sr << "," << s.sc << "\n";
    s.is_stune = t + 2;
    s.score += d;
  }
  if(flag == 1){ //이동처리만
    s.sr -= dy2[dd];
    s.sc -= dx2[dd];
  }
  if(s.sr < 0 || s.sc < 0 || s.sr >= n || s.sc >= n){
    s.is_die = true;
    check_die++;
    //cout<< check_die << " : died \n";
    return;
  }
  for(int i=0; i<p; i++){
    if(i == idx) continue;
    santa& ss = santas[i];
    if(ss.is_die == true) continue;
    if(s.sr == ss.sr && s.sc == ss.sc){
      stor_boom(dd, i, 1); //연쇄충돌
    }
  }
}

void db_visited(){
    cout << "------- visited map -------\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << visited[i][j] <<" ";
        }
        cout << '\n';
    }
    cout << "------- visited map -------\n";
    return;
}

void move_s(){
    for(int i=0; i<p; i++){
        santa& s = santas[i];
        //cout << i << " : santa idx, start!\n";
        if(s.is_die == true || s.is_stune > 0){
            continue;
        }
        //bfs(); //코스트맵만 생성
       // db_visited();
        int best_dd = -1;
        int men_d = get_d_from_s(s.sr, s.sc); //맨허튼 거리 가만히 있을때
        for(int dd=0; dd<4; dd++){
            int ny = s.sr + dy2[dd];
            int nx = s.sc + dx2[dd];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;

            // int ret = visited[ny][nx];
            // if(ret == 0) continue;
            //cout << ny << "," << nx << " : " << ret << "but best_d is "<< best_d <<'\n';
            bool checker = false;
            for(int idx=0; idx<p; idx++){
                if(santas[idx].sr == ny && santas[idx].sc == nx) {
                    checker = true; 
                    continue;
                }
            }
            if(checker) continue; //그곳에 산타 있으면
            int tmp_men_d = get_d_from_s(ny, nx);
            if(tmp_men_d < men_d){ 
                best_dd = dd; //베스트 방향
                men_d = tmp_men_d;
            } 
        }
        if(best_dd == -1) continue; //움직일수없으면
        //cout << s.sr << "," << s.sc << " >> " << best_dd << " : best_dd & >> ";
        s.sr += dy2[best_dd];
        s.sc += dx2[best_dd];
        //cout << s.sr << "," << s.sc << "\n";
        if(s.sr == rr && s.sc == rc) stor_boom(best_dd, i, 0); 
    }
    return;
}

int main(){
  cin >> n >> m >> p >> c >> d;
  cin >> rr >> rc;
  rr--; rc--;
  int num = 0;
  santa tmp_santa;

  for(int i=0; i<p; i++){
    cin >> num; num--;
    cin >> santas[num].sr >> santas[num].sc;
    santas[num].sr--; santas[num].sc--;
    //cout << num << " : idx & " << santas[num].sr << "," << santas[num].sc << '\n';
  }


  for(t=0; t<m; t++){
 
    //draw_map();
    // 1. 루돌프의 움직임 & 
    move_r();
    if(check_die >= p) break; //종료
    // 2. 
    //draw_map();
    //2. 산타의 움직임
    move_s();
    
    if(check_die >= p) break; //종료

    for(int i=0; i<p; i++){ //스턴 상태 확인
        if(santas[i].is_die == false) santas[i].score++;
        if(santas[i].is_stune <= t+1){
            santas[i].is_stune = 0;
        }
    }

  }
  
  for(int i=0; i<p; i++){
    cout << santas[i].score << " ";
  }
  return 0;
}

