#include <bits/stdc++.h>
using namespace std;

string raw;
stack<char> st;
string boom;

int main(){
    cin >> raw;
    cin >> boom;
    char last_char = boom[boom.length()-1];
    string findit = boom;
    reverse(findit.begin(), findit.end());

    for(int i=0; i<raw.length(); i++){ //검사시작
        char here = raw[i]; //이번에 스택에 들어갈 문자
        st.push(here);
        if(here == last_char){ 
            string tmps="";
            for(int ii=0; ii<findit.length(); ii++){ //마지막 문자 동일할시 트리거 / 검사
                if(st.size()){
                    tmps.push_back(st.top());
                    st.pop();
                }
            }
            if(tmps != findit){ //불일치시 원위치
                reverse(tmps.begin(), tmps.end());
                for(char c: tmps){
                    st.push(c);
                }
            }
        }
    }

    //return
    string ret;
    if(!st.size()){
        cout << "FRULA";
        return 0;    
    }
    while(st.size()){
        ret.push_back(st.top());
        st.pop();
    }
    reverse(ret.begin(), ret.end());
    cout << ret;
    return 0;
}
