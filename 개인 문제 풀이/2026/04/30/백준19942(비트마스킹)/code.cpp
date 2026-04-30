#include <bits/stdc++.h>
using namespace std;
#define INF 987654321
int n, ret = INF;

vector<vector<int>> list_f;
map<int, vector<vector<int>>> ret_v; //가격 - 조합

struct food{
    int p, g, t, v, m;
}a[16]; //바로 구조체 배열 선언
int mp = 100; int mg = 70; int mt = 90; int mv = 10; //min

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> mp >> mg >> mt >> mv;
    for(int i=0; i<n; i++){
        cin >> a[i].p >> a[i].g >> a[i].t >> a[i].v >> a[i].m;
    }
    
    int num = (1<<n); // 63 (1 1 1 1 1 1)
    
    for(int i=0; i<num; i++){
        int tp=0; int tg=0; int tt=0; int tv=0; int tm=0;
        vector<int> idx;
        for(int j=0; j<n; j++){
            if(i & 1<<j){
                idx.push_back(j+1);
                tp += a[j].p;
                tg += a[j].g;
                tt += a[j].t;
                tv += a[j].v;
                tm += a[j].m;
            }
        }
        if(tp>=mp && tg >=mg && tt >= mt && tv >= mv){ //min 충족시
            if(ret >= tm){
                ret = tm;
                ret_v[tm].push_back(idx);
            }
        }
    }
    if(ret == INF) {cout << "-1\n"; return 0;}

    sort(ret_v[ret].begin(), ret_v[ret].end());
    cout << ret << "\n";

    for(int tmp : ret_v[ret][0]){
        cout << tmp << " ";
    }


    return 0;
}
