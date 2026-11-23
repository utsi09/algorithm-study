#include <bits/stdc++.h>
using namespace std;


int n;
stack<pair<char,int>> st;
int ret = 0;

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        char ch;
        scanf(" %c", &ch);
        if(st.size() && st.top().first == '(' && ch == ')'){
            st.pop();
            continue;
        }
        else{
            st.push({ch, i});
        }
    }

    if(st.empty()){
        cout << n;
        return 0;
    }
    int before_top = n-1;
    ret = before_top - st.top().second;
  
    while(st.size()){
        int gap = before_top - st.top().second - 1;
        ret = max(ret, gap);
        
        before_top = st.top().second;
        st.pop();
        if(st.size() == 0){
            ret = max(ret, before_top);
            break;
        }
    }
    cout << ret;
    return 0;
}