#include <bits/stdc++.h>
using namespace std;

vector<int> v;

int m[3][3] = {
    {10,20,21},
    {70,90,12},
    {80,110,120},
};
int visited[3][3];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

void print(){
    for (auto i : v){
        cout << i << " ";
    }
    cout << endl;
}

void go(int i, int j){
    visited[i][j]=1;
    if(i==2 && j==2){
        print();
        return;
    }
    for(int k=0; k<4; k++){
        int ny = i +dy[k];
        int nx = j +dx[k];
        if (ny<0 || nx<0 || ny>=3 || nx>=3) continue;
        if (visited[ny][nx]) continue;
        v.push_back(m[ny][nx]);

        go(ny,nx);

        visited[ny][nx]=0;
        v.pop_back();
        
    }
}

int main() {
    
    v.push_back(m[0][0]);
    
    go(0,0);

    return 0;
}
