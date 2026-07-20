#include<string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    stack<char> st;
    for(int i=0; i<s.size(); i++){
        if(s[i] == ')'){
            if(st.size() && st.top() == '('){
                st.pop();
                continue;
            }
            st.push(')');
        }
        else{
            st.push('(');
        }
    }
    
    return (st.size()>0 ? false : true);
}