#include <bits/stdc++.h>
#include <iostream>
using namespace std;
vector<pair<int,int>> v;
int N, C;
map<int,int> mp, mp_first;

bool cmp(pair<int,int> first, pair<int,int> second){
    if (first.first == second.first){
        return mp_first[first.second] < mp_first[second.second];
    }
    return first.first > second.first;
}

int main() {
    cin >> N >> C;
    for(int i=0; i<N; i++){
        int tmp;
        cin>>tmp; mp[tmp]++;
        if(mp_first[tmp]==0) mp_first[tmp] = i+1;
    }
    for (auto i : mp){
         v.push_back(make_pair(i.second, i.first)); // <몇번, 순수숫자>
    }
    sort(v.begin(), v.end(), cmp);
    for (auto i : v){
        for (int j=0; j<i.first; j++){
            cout << i.second << " ";
        }
    }
    return 0;
}
