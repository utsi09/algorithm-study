#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int n;
int open, closed;
#include <stack>
int small, big;

bool check_closed(string s){
    small=0; big = 0;
    stack<char> stk;
    for(int i=0; i<s.size(); i++){
        if(s[i] == '(') {stk.push(s[i]); small++;}
        else if(s[i] == '[') {stk.push(s[i]); big++;}
        else if(s[i] == ')'){
            if(small <= 0) return false;
            else {
                if(stk.top() == '(') {stk.pop(); small--;}
            }
        }
        else if(s[i] == ']'){
            if(big <= 0) return false;
            else {
                if(stk.top() == '[') {stk.pop(); big--;}
            }
        }
    }
    return stk.empty();
}

int main(){
    while(1){
        string s;
        getline(cin, s);
        if(s == ".") break;
        if(check_closed(s)) cout << "yes\n";
        else cout << "no\n";
    }

    return 0;
}
