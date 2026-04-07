#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;

int n, t;
const int map_size = 51;
string food_map[map_size][map_size]; // T , C 등의 푸드 문자열
int love_map[map_size][map_size]; // 8, 13 등의 신앙심 
int group_map[map_size][map_size]; //group_id가 저장된 맵
int visited[map_size][map_size]; //visited
int is_loved[map_size][map_size];

int dy[4] = {-1,1,0,0}; //전파방향 위 아래 왼쪽 오른쪽
int dx[4] = {0,0,-1,1};
vector<pair<int,int>> group_king; //그룹의 king들-idx : 1부터 순차증가

int group_id=1;
int save_love=0;
bool is_block=false;
int check_mint=0; int check_choco=0; int check_milk=0;
int check_love[4][4][4]={0,};
vector<char> comp;

pair<int,int> BFS(int i, int j, string food){
    // cout << food << endl;
    group_map[i][j] = group_id;
    love_map[i][j] -= 1; //1빼기
    queue<pair<int,int>> q;
    q.push({i,j});
    pair<int,int> best_king = {i,j};
    int best_love = love_map[i][j];

    while(q.size()){
        int tmp_i = q.front().first;
        int tmp_j = q.front().second;
        q.pop();
        for(int k=0; k<4; k++){
            int ny = tmp_i + dy[k];
            int nx = tmp_j + dx[k];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(visited[ny][nx]!=0) continue;
            if(food_map[ny][nx] != food) continue; //음식이 같아야 세트
            if(group_map[ny][nx] != 0) continue; //그룹이 이미 있으면 패스
            group_map[ny][nx] = group_id;
            visited[ny][nx] = 1;
            save_love++;
            q.push({ny,nx});
            love_map[ny][nx] -= 1; //1빼기
            if(love_map[ny][nx] > best_love){ //신앙심 큰 값으로 업데이트
                best_king = {ny,nx};
                best_love = love_map[ny][nx];
            }
            if(love_map[ny][nx] == best_love){ //신앙심이 같을때 우선순위
                if(ny == best_king.first){
                    if(nx > best_king.second) continue;
                    else{
                        best_king = {ny,nx};
                        best_love = love_map[ny][nx];
                    }
                }
                if(ny < best_king.first){ 
                    best_king = {ny,nx};
                    best_love = love_map[ny][nx];
                }
            }
            

        }
    }

    return best_king;
}

bool size_cmp(pair<int,int> king1, pair<int,int> king2){
    //음식 종류 갯수 1 2 3 정렬
    if(food_map[king1.first][king1.second].size() < food_map[king2.first][king2.second].size()) return true;
    if (food_map[king1.first][king1.second].size() == food_map[king2.first][king2.second].size()){
        //cout <<"size same!!" << endl;
        if(love_map[king1.first][king1.second] > love_map[king2.first][king2.second]) return true; //size 같으면 love 크기 큰게 앞으로
        if(love_map[king1.first][king1.second] == love_map[king2.first][king2.second]){ //받고 신앙심 같으면
            if(king1.first < king2.first) return true; //행이 작은게 앞으로
            if(king1.first == king2.first){ //행같으면 열이 작은게 앞으로
                if(king1.second < king2.second) return true;
            }
        }
    }

    return false;

}



int main(){
    cin >> n >> t;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            char tmp;
            scanf("%1s",&tmp);
            string tmp_s(1,tmp);
            food_map[i][j] = tmp_s;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int love;
            cin >> love;
            love_map[i][j] = love;
        }
    }
    
    for(int turn=0; turn<t; turn++){
        int check_love[4][4][4]={0,};
        fill(&is_loved[0][0], &is_loved[0][0]+51*51, 0); //전파받음상태 초기화
        fill(&group_map[0][0], &group_map[0][0]+51*51, 0); //전파받음상태 초기화
        group_king.erase(group_king.begin(),group_king.end());

        // 아침 시작
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                love_map[i][j]++;
            }
        }

    //     for(int i=0; i<n; i++){ //신앙심맵
    //     for(int j=0; j<n; j++){
    //         cout << love_map[i][j] << " ";
    //     }
    //     cout <<endl;
    // }
        // 모든 신앙심 +1
        // 아침 끝
        group_id = 1; //1부터 시작
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(group_map[i][j] != 0) continue; //그룹이 이미 있으면 패스
                save_love = 0;
                string f_this = food_map[i][j];
                //cout <<f_this<<endl;
                fill(&visited[0][0], &visited[0][0]+51*51, 0);
                pair<int,int> best_king = BFS(i, j ,f_this);
                group_king.push_back(best_king);
                love_map[best_king.first][best_king.second] += save_love+1; //모은만큼 대표자 love에 +
                group_id++;
            }
        }
        
    //      for(pair<int,int> p : group_king){
    //         cout << p.first+1 << "," << p.second+1;
    //         cout <<endl;
    //     }

    //     for(int i=0; i<n; i++){ //신앙심맵
    //     for(int j=0; j<n; j++){
    //         cout << love_map[i][j] << " ";
    //     }
    //     cout <<endl;
    // }
        //저녁 시간
        sort(group_king.begin(), group_king.end(), size_cmp); //size 1 1 1 2 2 2 3

        // for(int i=0; i<n; i++){ //신앙심맵
        //     for(int j=0; j<n; j++){
        //         cout << setw(4)<< food_map[i][j] << " ";
        //     }
        //     cout <<endl;
        // }

        // for(pair<int,int> p : group_king){
        //     //cout << food_map[p.first][p.second].size() <<"food size" << endl;
        //     cout << love_map[p.first][p.second] << "love size"<< endl;
        //     cout << p.first+1 << "," << p.second+1;
        //     cout <<endl;
        // }
        //2번째도 문제없음 여기까지
        //group_king 순서대로 전파 시작
        for(pair<int,int>& king : group_king){
            
            if(is_loved[king.first][king.second]==1) {
                //cout << "im loved\n";
                continue; //전파받으면 전파 불가
            }
            int mod4 = love_map[king.first][king.second] % 4;
            is_block = false;
            queue<pair<int,int>> q;
            q.push({king.first, king.second});
            int love_cost = love_map[king.first][king.second] - 1; //신앙심 - 1 을 보내기
            //cout << "start cast" <<  love_cost << ":cost \n" << mod4 << ":mod4 \n";
            love_map[king.first][king.second] = 1; //1로 
            while(1){
                //cout <<"hi\n";
                if(is_block==true){
                    //cout << "is break" << endl;
                    break;
                } 

                int tmp_i = q.front().first;
                int tmp_j = q.front().second;
                if(tmp_i<0 || tmp_j<0 || tmp_i>= n | tmp_i>=n) break;
                //cout << tmp_i+1 << "," << tmp_j+1 << endl;
                q.pop();
                int ny = tmp_i + dy[mod4];
                int nx = tmp_j + dx[mod4];
                if(ny<0 || nx<0 || ny>=n || nx>=n){
                    //cout <<"break ch\n"; 
                    is_block = true;
                    continue;
                }
                if(food_map[ny][nx] == food_map[tmp_i][tmp_j]){ //음식이 같으면 바로 다음칸
                    //cout << "same food" << endl;
                    q.push({ny,nx});
                    continue;    
                }
                if(love_cost > love_map[ny][nx]){ //강한 전파 성공
                    //cout <<"strong love"<<endl;
                    food_map[ny][nx] = food_map[king.first][king.second]; //같은 음식 신봉
                    love_cost -= (love_map[ny][nx]+1); //코스트 소비
                    q.push({ny,nx});
                    love_map[ny][nx]++;
                    if(love_cost <= 0) is_block=true; //종료
                    is_loved[ny][nx] = true; //이번턴 전파 불가능
                    continue;
                }
                if(love_cost <= love_map[ny][nx]){ //약한 전파 성공
                    //cout <<"weak love"<<endl;
                    for(char c1 : food_map[tmp_i][tmp_j]){ //재료 하나씩 꺼내서
                        for(char c2 : food_map[ny][nx]){
                            if(c1 != c2){ //없는재료면 추가
                                food_map[ny][nx] += c1;
                            }
                        }

                    }
                    for(int i=0; i<n; i++){
                        for(int j=0; j<n; j++){

                            //압축기(같은 규칙 중복 제거)
                            comp.erase(comp.begin(), comp.end()); //초기화

                            for(char c : food_map[i][j]){
                                comp.push_back(c);
                            }
                            // for(char c:comp){
                            //     cout << setw(4) << c ;
                            // }
                            
                            sort(comp.begin(), comp.end());
                            comp.erase(unique(comp.begin(), comp.end()),comp.end());

                            // for(char c:comp){
                            //     cout << setw(4) << c ;
                            // }
                            food_map[i][j] = "";
                            for(char c : comp){
                                food_map[i][j] += c;
                            }
                            //cout << setw(4) << food_map[i][j];
                        }
                        //cout <<"\n";
                    }
                    love_map[ny][nx] += love_cost; //코스트만큼 증가
                    love_cost = 0;
                    is_block = true;
                    is_loved[ny][nx] = true; //이번턴 전파 불가능
                    continue;
                }

            }

               

        }

        // for(int i=0; i<n; i++){ //신앙심맵
        //     for(int j=0; j<n; j++){
        //         cout << setw(4)<< love_map[i][j] << " ";
        //     }
        //     cout <<endl;
        // }

        // cout << "bf end" << endl;
        

        //(민트초코우유, 민트초코, 민트우유, 초코우유, 우유, 초코, 민트 )
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){

                //압축기(같은 규칙 중복 제거)
                comp.erase(comp.begin(), comp.end()); //초기화

                for(char c : food_map[i][j]){
                    comp.push_back(c);
                }
                // for(char c:comp){
                //     cout << setw(4) << c ;
                // }
                
                sort(comp.begin(), comp.end());
                comp.erase(unique(comp.begin(), comp.end()),comp.end());

                // for(char c:comp){
                //     cout << setw(4) << c ;
                // }
                food_map[i][j] = "";
                for(char c : comp){
                    food_map[i][j] += c;
                }
                //cout << setw(4) << food_map[i][j];
            }
            //cout <<"\n";
        }

        
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                check_mint=0;
                check_choco=0;
                check_milk=0;
                for(char c : food_map[i][j]){
                    if(c == 'T') {
                        //cout <<"catch mint"<< endl;
                        check_mint=1; //민트있으면
                    }
                    if(c == 'C') check_choco=1; //초코있으면
                    if(c == 'M') check_milk=1; //우유있으면
                }
                check_love[check_mint][check_choco][check_milk]+=love_map[i][j];
                //cout << check_love[check_mint][check_choco][check_milk] << endl;
            }
        }

        // for(int i=0; i<n; i++){ //신앙심맵
        //     for(int j=0; j<n; j++){
        //         cout << setw(4)<< food_map[i][j] << " ";
        //     }
        //     cout <<endl;
        // }
        // for(int i=0; i<n; i++){ //신앙심맵
        //     for(int j=0; j<n; j++){
        //         cout << setw(4)<< love_map[i][j] << " ";
        //     }
        //     cout <<endl;
        // }
        cout << check_love[1][1][1] << " "; 
        cout << check_love[1][1][0] << " "; 
        cout << check_love[1][0][1] << " "; 
        cout << check_love[0][1][1] << " "; 
        cout << check_love[0][0][1] << " "; 
        cout << check_love[0][1][0] << " "; 
        cout << check_love[1][0][0] << " "; 
        cout << "\n";

        

    }


    return 0;
}

/*
디버깅용 복붙 - 맵 (문자열맵)

for(int i=0; i<n; i++){ //푸드맵
        for(int j=0; j<n; j++){
            cout << food_map[i][j] << " ";
        }
        cout <<endl;
    }

for(int i=0; i<n; i++){ //신앙심맵
        for(int j=0; j<n; j++){
            cout << love_map[i][j] << " ";
        }
        cout <<endl;
    }

for(int i=0; i<n; i++){ //그룹맵
        for(int j=0; j<n; j++){
            cout << group_map[i][j] << " ";
        }
        cout <<endl;
    }

*/
