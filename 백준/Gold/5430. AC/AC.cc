#include <bits/stdc++.h>
using namespace std;

int t;




int main(){

    cin >> t;

    for(int i=0; i<t; i++){
        bool error_check = false;
        
        
        string p;
        cin >> p;
        int num; cin >> num;
        string raw;
        cin >> raw;
        vector<int> v;
        int now_tmp = 0;
        for(int j=0; j<raw.size(); j++){
            if(num == 0) break;
            if(raw[j] == '[') continue;
            if(raw[j] == ',' || raw[j] == ']'){
                v.push_back(now_tmp);
                now_tmp = 0;
                continue;
            }
            else{
                now_tmp = now_tmp*10 + (raw[j] - '0');
            }
            
        }

        int l = 0;
        int r = v.size() - 1;
        bool is_reverse = false;
        
        for(char& c : p){
            if(c == 'R'){
                is_reverse = !is_reverse;
            }
            else if(c == 'D'){
                if(l > r){
                    error_check = true;
                    break;
                }
                if(!is_reverse) l++;
                else if(is_reverse) r--;
            }   
        }       


        if(error_check){
            cout << "error\n";
        }

        else if(is_reverse){
            cout << "[";
            for(int ii=r; ii >=l; ii--){
                if(ii != r) cout << ",";
                cout << v[ii];
            }
            cout << "]\n";
        } 

        
        else{
            cout << "[";
            for(int ii=l; ii<=r; ii++){
                if(ii != l) cout << ",";
                cout << v[ii];
            }
            cout << "]\n";
        }

    }

    return 0;
}