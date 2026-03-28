#include <bits/stdc++.h>
#include <iostream>
using namespace std;

string passwd;

bool check_aeiou(char& pt){
    if(pt == 'a' || pt == 'e' || pt == 'i' || pt == 'o' || pt == 'u') return true;
    return false;
}

int main() {
    while(cin >> passwd && passwd != "end"){
        bool aeiou_checker = false;
        bool aceptor = true;
        vector<char> stacker;
        int v_cnt = 0; //모음
        int c_cnt = 0; // 자음

        for(int i=0; i<passwd.length();i++){
            char curr = passwd[i];
            if(check_aeiou(curr)){
                aeiou_checker = true;
                v_cnt++;
                c_cnt = 0;
            } else {
                c_cnt++;
                v_cnt = 0;
            }
            if (c_cnt>=3 || v_cnt>=3) aceptor = false;
            if (i>0 && curr==passwd[i-1]){
                if (!(curr=='e' || curr=='o')) aceptor = false;
            }
            
            
        }
        if (aeiou_checker == true && aceptor == true) printf("<%s> is acceptable.\n", passwd.c_str());
        else printf("<%s> is not acceptable.\n", passwd.c_str());
    };
    return 0;
}
