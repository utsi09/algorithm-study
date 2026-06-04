#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int n;
int open, closed;
#include <stack>

bool check_closed(string s){
    stack<char> stk;
    for(int i=0; i<s.size(); i++){
        if(s[i] == '(') stk.push(s[i]);
        else if(s[i] == ')'){
            if(!stk.size()) return false;
            else {
                if(stk.top() == '(') stk.pop();
            }
        }
    }
    return stk.empty();
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        if(check_closed(s)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
