#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> num;
vector<char> oper;

int ret = -98765432;

int operate(int here, int a, int b){
    if(oper[here] == '+') return a + b;
    if(oper[here] == '*') return a * b;
    if(oper[here] == '-') return a - b;
}

void solve(int here, int _num){
    //cout << here << ":" << _num << '\n';
    if(here >= num.size() - 1){
        ret = max(ret, _num);
        return;
    }
    solve(here+1, operate(here, _num, num[here+1]));
    if(here+2 <= num.size()-1){
        int temp = operate(here+1, num[here+1], num[here+2]);
        solve(here+2, operate(here, _num, temp));
    }
    return;
}


int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        if(i % 2 == 0){
            int tmp; cin >> tmp;
            num.push_back(tmp);
        }
        else {
            char tmpc; cin >> tmpc;
            oper.push_back(tmpc);
        }
    }
    solve(0, num[0]);
    cout << ret;
    return 0;
}
