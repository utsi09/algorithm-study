#include <bits/stdc++.h>
using namespace std;
char adj[65][65];
int m_size = 0;
string s="";

string quard(int y, int x, int m_size){
    string ret="";
    if(m_size==1) {
        // cout << adj[y][x];
        return string(1, adj[y][x]);
    }
    char first = adj[y][x];
    for(int i=y; i<y+m_size; i++){
        for(int j=x; j<x+m_size; j++){
            if(adj[i][j] != first){
                ret+='(';
                ret+=quard(y,x,m_size/2);
                ret+=quard(y,x+m_size/2,m_size/2);
                ret+=quard(y+m_size/2,x,m_size/2);
                ret+=quard(y+m_size/2,x+m_size/2,m_size/2);
                ret+=')';
                return ret;
            }
        }
    }
    return string(1,first);
}

int main(){
    cin >> m_size;
    for(int i=0; i<m_size; i++){
        cin >> s;       
        for(int j=0; j<m_size; j++){
            adj[i][j] = s[j];
        }
    }
    cout << quard(0,0,m_size);

    return 0;
}
