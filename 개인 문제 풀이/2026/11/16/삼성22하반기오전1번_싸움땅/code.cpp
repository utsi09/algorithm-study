#include <bits/stdc++.h>
using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int n,m,k;
priority_queue<int> adj[21][21];

struct player
{
    int x,y,d,s;
    int gun=0;
    int score=0;
};
vector<player> players;

void db_map(){
    cout << "------- map -----\n";
    for(int i=0; i<players.size(); i++){
        cout << "player "<<i<<": " <<players[i].x << "," << players[i].y <<'\n';
    }
    cout << "------- map end -----\n";
}


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
        cin >> tmp.x >> tmp.y >> tmp.d >> tmp.s;
        tmp.x--; tmp.y--;
        players.push_back(tmp);
    }
}

void move_player(){
    for(int p=0; p<players.size(); p++){
        //cout << players[p].x <<","<<players[p].y <<">>>";
        int ny = players[p].y + dy[players[p].d];
        int nx = players[p].x + dx[players[p].d];
        if(ny<0 || nx<0 || ny>=n || nx>=n){ //격자 벗어나면 방향 반대로
            players[p].d = (players[p].d + 2)%4;
            ny = players[p].y + dy[players[p].d];
            nx = players[p].x + dx[players[p].d];
        }
        players[p].y = ny; //바로 이동
        players[p].x = nx;
        //cout << nx <<","<< ny <<'\n';
        int winner = p;
        int loser = -1;
        int prize = 0;
        // 플레이어와 조우
        for(int pp=0; pp<players.size(); pp++){
            if(pp == p) continue;
            if(ny == players[pp].y && nx == players[pp].x){ //충돌
                //cout << "boom\n";
                int my_power = players[p].s + players[p].gun;
                int your_power = players[pp].s + players[pp].gun;
                //cout << my_power << "vs" << your_power <<'\n';
                prize = abs(my_power - your_power);
                //승자 판정
                if(my_power > your_power){
                    winner = p;
                    loser = pp;
                }
                else if(my_power < your_power){
                    winner = pp;
                    loser = p;
                }
                else{
                    if(players[p].s > players[pp].s){
                        winner = p;
                        loser = pp;
                    }
                    else{
                        winner = pp;
                        loser = p;
                    }
                }
                break;
            }
        }
        // cout << "winner : " << winner <<'\n';
        // cout << "loser : " << loser <<'\n';
        players[winner].score += prize; 
        //cout << "prize = " << prize <<'\n';
        if(loser != -1){ //충돌이 있었으면
            //패자 : 총 내려놓고 방향대로 이동한후 충돌이나 격자밖일시 90도씩 회전하며 계속 이동
            adj[nx][ny].push(players[loser].gun); //내려놓고
            players[loser].gun = 0;
            for(int dd=0; dd<4; dd++){
                int tmpd = (players[loser].d + dd) % 4;
                int tmpx = players[loser].x + dx[tmpd];
                int tmpy = players[loser].y + dy[tmpd];
                if(tmpx<0 || tmpy<0 || tmpx>=n || tmpy>=n) continue; //오버플로우
                bool checker = true;
                for(int tmpp=0; tmpp<players.size(); tmpp++){
                    if(tmpp == loser) continue; //자기자신제외
                    if(players[tmpp].y == tmpy && players[tmpp].x == tmpx) checker = false; //충돌
                }
                if(checker){
                    players[loser].x = tmpx;
                    players[loser].y = tmpy;
                    players[loser].d = tmpd;
                    //cout << "loser " << loser << " : d >> " << tmpd << '\n';
                    if(adj[tmpx][tmpy].size()){ //총있으면
                        players[loser].gun = adj[tmpx][tmpy].top(); //들고
                        adj[tmpx][tmpy].pop(); //맵위에선 총 삭제
                    }
                    break;
                }
            }
        }
        
        //고정 : 승자는 총줍기
        if(adj[nx][ny].size()){
            adj[nx][ny].push(players[winner].gun); //내려놓고
            players[winner].gun = adj[nx][ny].top(); //들고
            adj[nx][ny].pop(); //맵위에선 총 삭제
        }
        
    }


}

int main(){
    init();

    for(int turn=0; turn<k; turn++){
        move_player();
        //db_map();
    }

    for(player p : players){
        cout << p.score << " ";
    }

    return 0;
}
