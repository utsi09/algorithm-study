#include <bits/stdc++.h>
using namespace std;

int alpha[130];
//map<char, int> ap;

int main(){
    string s;
    cin >> s;
    for(int i=0; i<s.size(); i++){
        alpha[int(s[i])]++;
    }
    for(int i=97; i<=122; i++){
        cout << alpha[i] << " ";
    }
    return 0;
}
