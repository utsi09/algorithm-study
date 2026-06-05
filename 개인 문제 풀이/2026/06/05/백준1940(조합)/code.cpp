#include <bits/stdc++.h>
using namespace std;
int n, goal;
vector<int> mat;
vector<int> cb;
int r = 2;
int cnt;
int complet=-1;

void combi(int start){
    if(cb.size() == r){
        int add = 0;
        for(int i=0; i<r; i++){
            //cout << cb[i] << " ";
            add += cb[i];
        }
        //cout << '\n';
        if(add == goal) {cnt++;}
        return;
    }
    for(int i=start; i<n; i++){
        cb.push_back(mat[i]);
        combi(i+1);
        cb.pop_back();

    }
    return;
}

int main(){ 
    cin >> n;
    cin >> goal;
    for(int i=0;i<n; i++){
        int tmp;
        cin >> tmp;
        mat.push_back(tmp);
    }

    combi(0);
    cout << cnt;
    return 0;
}
