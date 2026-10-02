#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<int>> adj(4, vector<int>(100002));
int n;
vector<vector<int>> final(4, vector<int>(100002));



int main(int argc, char** argv)
{
    cin >> n;
    for(int i=0; i<3; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }
    for(int i=0; i<n; i++){
        adj[3][i] = adj[0][i] + adj[1][i] + adj[2][i]; //모든 점수 합한걸 추가
    }
    
    for(int i=0; i<4; i++){ //시험별
        vector<vector<int>> tmp(100002);
        for(int j=0; j<n; j++){ //10만
            tmp[j].push_back(adj[i][j]); //점수
            tmp[j].push_back(j); //인덱스
        }
        sort(tmp.begin(), tmp.end(), greater<vector<int>>()); //점수로 내림차순
        int _last = 1e8;
        int prize = 0;
        int cnt = 1;
        for(int j=0; j<n; j++){ //등수 주기
            if(_last != tmp[j][0]){
                prize+=cnt;
                cnt = 1;
            }
            else{
                cnt++;
            }
            tmp[j].push_back(prize); //이전과 점수가 동일하면 이전과 등수 동일
            _last = tmp[j][0]; //마지막 점수 갱신
        }
        sort(tmp.begin(), tmp.begin()+n, [](auto& a, auto& b){
            return a[1] < b[1];
        }); //idx 오름차순

        for(int ii=0; ii<n; ii++){
            final[i][ii] = tmp[ii][2]; 
        }
    }

    for(int i=0; i<4; i++){
        for(int j=0; j<n; j++){
            cout << final[i][j] << " ";
        }
        cout << '\n';
    }

   return 0;
}
