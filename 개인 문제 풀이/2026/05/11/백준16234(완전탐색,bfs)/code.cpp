#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int n, l ,r;
int adj[51][51];
int visited[51][51];
bool is_moved = false;
int country = 1; //visited에 인접 나라 체크용
int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};
int day = 0;

void db_map(){
    cout <<"----------"<< day <<":day\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << adj[i][j] << " ";
        }
        cout <<"\n";
    }
    cout <<"----------\n";
}

pair<int,int> bfs(int i, int j){
    pair<int,int> country_info; //총인구수 , 칸의 수
    int people=adj[i][j]; int cell=1;
    visited[i][j] = country;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(q.size()){
        int yy = q.front().first; int xx = q.front().second; q.pop();
        for(int d=0; d<4; d++){
            int ny = yy + dy[d];
            int nx = xx + dx[d];
            if(ny <0||nx<0 || ny>=n || nx>=n) continue;
            if(visited[ny][nx]) continue;
            if(abs(adj[yy][xx] - adj[ny][nx]) < l || abs(adj[yy][xx] - adj[ny][nx]) > r) continue; //인구차이
            //cout << abs(adj[yy][xx] - adj[ny][nx]) << "\n";
            people += adj[ny][nx]; cell++;
            q.push({ny,nx});
            visited[ny][nx] = country;
        }
    }
    country_info.first = people;
    country_info.second = cell;
    return country_info;
}

void move_people(pair<int,int> c_info){ //현재 인접 나라들 이동
    int people = c_info.first; int cell = c_info.second;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j] == country){
                if(adj[i][j] != people / cell) is_moved = true; //이동하면
                adj[i][j] = people / cell;
            }
        }
    }
}

void move(){
    //부울이 1(이동없음)이면 while 종료
    while(1){
        is_moved = false;
        country = 1;
        fill(&visited[0][0], &visited[0][0]+51*51, 0); //다음날되면 초기화
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(visited[i][j]) continue;
                pair<int,int> c_info = bfs(i,j);
                move_people(c_info); //현재 country 이동
                country++;
            }
        }
        if(!is_moved) break;
        //db_map();
        day++;
    }
}

int main() {
    cin >> n >> l >> r;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }

    
    move();
    cout << day;
    return 0;
}
