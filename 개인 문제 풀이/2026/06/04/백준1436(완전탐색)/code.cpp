#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
vector<int> devel;

int cnt=0;

void make_table(int n){
    for(;;cnt++){
        if(devel.size() == n) break;
        string tmp = to_string(cnt);
        if(tmp.find("666") != string::npos){
            devel.push_back(cnt);
        }
    }
}

int main(){
    int n;
    cin >> n;
    make_table(n);
    cout << devel[n-1];
    return 0;
}
