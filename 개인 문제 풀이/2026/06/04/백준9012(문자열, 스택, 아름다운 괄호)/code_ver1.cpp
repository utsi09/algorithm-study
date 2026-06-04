#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int n;
int open, closed;

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        open = 0; closed = 0;
        string s;
        cin >> s;
        bool closed_error = false;
        for(int i=0; i<s.size(); i++){
            if(s[i] == '(') open++;
            else if(s[i] == ')') closed++;
            if(open < closed) {cout <<"NO\n"; closed_error=true; break;}
        }

        //cout << open << "," << closed << endl;
        if(closed_error) continue;
        //cout << "not err" << endl;
        open == closed ? (cout<<"YES\n") : (cout<<"NO\n");
    }

    return 0;
}
