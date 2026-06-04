#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


vector<int> devel;
int cnt=0;

void make_table(int n){
    while(1){
        if(devel.size() == n) break;
        cnt++;
        string tmp = to_string(cnt);
        int tmp_cnt = 0;
        bool is_devel = false;
        for(int i=0; i<tmp.size(); i++){
            if(tmp[i] == '6') tmp_cnt++;
            else if(tmp[i] != '6') tmp_cnt = 0;
            if(tmp_cnt == 3) is_devel = true;
        }
        if(is_devel) devel.push_back(cnt);
    }
}



int main(){
    
    int n;
    cin >> n;
    make_table(n);
    cout << devel[n-1];

    return 0;
}
