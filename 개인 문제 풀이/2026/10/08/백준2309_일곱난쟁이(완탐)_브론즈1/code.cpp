#include <bits/stdc++.h>
using namespace std;

vector<int> njs(9);
vector<int> visited(9);
bool is_find = false;


void find_njs(int sum, int cnt){
    if(cnt == 7){
        if(sum == 100){ //조건 충족시 정렬후 출력
            vector<int> ret;
            for(int i=0; i<9; i++){ //방문했던 노드 인덱스에 해당하는 난쟁이 저장
                if(visited[i]){
                    ret.push_back(njs[i]);
                }
            }
            sort(ret.begin(), ret.end());
            for(int i : ret){
                cout << i << '\n';
            }
            is_find = true;
        }
        return;
    }

    for(int i=0; i<9; i++){
        if(visited[i] || sum + njs[i] > 100) continue;
        visited[i] = 1;
        find_njs(sum + njs[i], cnt+1);
        if(is_find) return;
        visited[i] = 0;
    }
    return;
}


int main(){
    for(int i=0; i<9; i++){
        cin >> njs[i];
    }

    find_njs(0, 0); //현재 키 합계, 목록 비트

    return 0;
}
