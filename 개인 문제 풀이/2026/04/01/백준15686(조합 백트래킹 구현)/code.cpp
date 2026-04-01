#include <bits/stdc++.h>
using namespace std;
int n,m;
int num;
vector<vector<int>> ch_combi;
vector<pair<int,int>> _home, _chicken;
int ans=1e8;

void combi(int start, vector<int> v){
    if(v.size() == m){
        ch_combi.push_back(v);
        return;
    }
    for(int i=start+1; i < _chicken.size();i++){
        v.push_back(i);
        combi(i,v);
        v.pop_back();
    }
}

int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> num;
            if(num == 1) _home.push_back(make_pair(i,j));
            if(num == 2) _chicken.push_back(make_pair(i,j));
        }
    }
    vector<int> v;
    combi(-1,v);


    for(vector<int> i : ch_combi){
        
        int ret= 0;
        for(pair<int,int> home : _home){
            int _dis = 987654;
            for(int idx : i){
                int dis = abs(home.first - _chicken[idx].first) + abs(home.second - _chicken[idx].second);
                _dis = min(dis, _dis);
            }
            ret += _dis;
        }
        ans = min(ans, ret);
    }
    cout << ans;

    return 0;
}

// '''

// 1. 모든 맵 입력 받기
// 2. 모든 조합 인덱스 만들어놓기 이중벡터 
// 3. for로 치킨집 조합들마다 돌리기 
// 4. for로 모든 집들 좌표 뽑기
// 5. for로 조합에 있는 치킨집들마다 집들이랑 비교해서 거리 구하기, ret에 모두 합산
// 6. 모두 더한거 ans와 비교 작은거로 갱신 min

// '''

// '''
// combi 함수
// 기저 사례 = 뽑아야하는 개수가 될때 = m
// i 에 1 더하고 반복문 - v size만큼 
// start 에 1 더하고 v는 그대로
// '''
