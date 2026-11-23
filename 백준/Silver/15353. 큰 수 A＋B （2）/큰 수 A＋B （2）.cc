#include <bits/stdc++.h>
using namespace std;
string a,b;

vector<int> ret;

int main(){
    cin >> a >> b;

    int a_idx = a.size() - 1;
    int b_idx = b.size() - 1;

    int anow;
    int bnow;
    int checksum = 0;
    while(1){
        
        if(a_idx <0 && b_idx<0) break;
        if(a_idx >= 0) anow = a[a_idx] - '0';
        else anow = 0;

        if(b_idx >= 0) bnow = b[b_idx] - '0';
        else bnow = 0;

        
        int sum = anow + bnow + checksum;
        checksum = sum / 10; //올림수
        int out = sum % 10; //해당 자리수

        // if(a_idx == a.size() - 1){
        //     cout << anow << "," << bnow << '\n';
        //     cout << sum << checksum << out << '\n';
        // }
        ret.push_back(out);

        a_idx--;
        b_idx--;
        
    }
    if(checksum != 0) ret.push_back(checksum);


    reverse(ret.begin(), ret.end());
    for(int& tmp : ret){
        cout << tmp;
    }


    return 0;
}