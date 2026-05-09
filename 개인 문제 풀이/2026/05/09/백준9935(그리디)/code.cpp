#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

string s, t;
string ret = "";

int main() {
    cin >> s >> t;
    for(int i=0; i<s.size(); i++){
        ret += s[i];
        if(ret.size() < t.size()) continue;
        if(t == ret.substr(ret.size() - t.size(), t.size())){
            ret.erase(ret.size() - t.size(), t.size());
        }
    }
    if(!ret.size()) cout << "FRULA";
    else cout << ret;
    return 0;
}
