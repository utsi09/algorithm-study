#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;
string S, T;
stack<char> st;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> S >> T;
    for(char c : S){
        st.push(c);
        if(st.size() >= T.size() && st.top() == T[T.size()-1]){
            string ret="";
            for(char i : T){
                ret += st.top(); st.pop();
            }
            reverse(ret.begin(),ret.end());
            if (ret != T)
            {
                for(char c : ret){
                    st.push(c);
                }
            }
        }
    }
    if(!st.size()) cout << "FRULA";
    else{
        string ret="";
        while(st.size()){
            ret+=st.top(); st.pop();
        }
        reverse(ret.begin(),ret.end());
        for(char c : ret){
            cout << c;
        }
    }
    return 0;
}

