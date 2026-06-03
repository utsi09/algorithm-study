#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define INF 98765432
int Q;
int tmp;
int dp[3004];

struct perfume{
    int strength;
    bool is_alive = true;
};
vector<perfume> v;
vector<int> p;//순열저장용
vector<int> pp;
int cnt[3005];
int n, r=3;
int ans=0;
int cnt_suffix[3005];

int solve(int here){
    if(here == 0){
        return 0;
    }
    if(here < 0){
        return INF;
    }
    int& ret = dp[here];
    if(ret != -1) return ret;
    ret = INF;
    for(int i=0; i<3005; i++){
        if(cnt[i] <= 0) continue;
        ret = min(ret, solve(here-i) + 1);
    }
    return ret;
}

int permutation(int depth, int goal){
    int add = 0;
    for(int i=3004; i>=1; i--){
        cnt_suffix[i] = cnt_suffix[i+1] + cnt[i]; //역누적합 테이블 만들기
    }
    for(int i=0; i<n; i++){
        int first = p[i];
        for(int j=0; j<n; j++){
            int second = p[j];
            int need = goal - first - second;
            if(need <= 0){
                add+=n;
                continue;
            }
            add += cnt_suffix[need];
            //cout << first <<"+" << second << " and is possible case is " << cnt_suffix[need] << " < current answer\n";
        }
    }

    return add;
}

int main(){
    cin >> Q;
    for(int i=0; i<Q; i++){
        if(i==0){ //첫입력은 1번 고정
            int n;
            cin >> tmp;
            cin >> n;
            for(int j=0; j<n; j++){
                perfume tmp_p;
                cin >> tmp_p.strength;
                cnt[tmp_p.strength]++;
                v.push_back(tmp_p);
            }
            continue;
        }
        int select;
        cin >> select;
        if(select == 2){ //향료 추가
            perfume tmp_p;
            cin >> tmp_p.strength;
            cnt[tmp_p.strength]++;
            v.push_back(tmp_p);
            continue;
        }
        if(select == 3){ //idx 번째 향료 폐기
            cin >> tmp;
            if(tmp <= 0 || tmp > (int)v.size()){
                cout << "-1\n";
                continue;
            } 
            tmp--;
            if(v[tmp].is_alive == false || cnt[v[tmp].strength]==0){
                cout << "-1\n";
                continue;
            }
            v[tmp].is_alive = false;
            cnt[v[tmp].strength]--;
            cout << v[tmp].strength <<'\n';
            continue;
        }               
        if(select == 4){
            cin >> tmp;
            memset(dp,-1,sizeof(dp));
            if(solve(tmp) < INF) cout << solve(tmp) <<'\n'; //dp함수
            else cout << "-1\n";
            continue;
        }
        if(select == 5){
            cin >> tmp;
            p.erase(p.begin(), p.end());
            for(int i=0; i<3005; i++){
                if(cnt[i] <= 0) continue;
                int tmp_n = cnt[i];
                for(int j=0; j<tmp_n; j++){
                    p.push_back(i); //cnt 개수만큼 넣기
                }
                //cout << i << endl; 
            }
            n = p.size();
            //cout << n << " is p's size" << '\n';
            cout << permutation(0, tmp) << '\n';
        }
    }



    return 0;
}
