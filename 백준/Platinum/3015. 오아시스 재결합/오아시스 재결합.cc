#include <bits/stdc++.h>
using namespace std;

int n;
stack<pair<int,int>> st;

long long ret;

int main(){
    cin >> n;

    for(int i=0; i<n; i++){
        int tmp; cin >> tmp;
        int cnt = 1;
        while(st.size() && st.top().first <= tmp){ 
            ret += st.top().second;
            if(st.top().first == tmp){
                cnt = st.top().second + 1;   
            }
            st.pop();
        }

      
        if(st.size()) ret++;
        st.push({tmp, cnt});
        //cout << i << " : " << ret <<'\n';
    }
    cout << ret;

    return 0;
}