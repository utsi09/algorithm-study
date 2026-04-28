#include <bits/stdc++.h>
using namespace std;
#define prev taewook
int o;
string prev; // o : 현재턴 이긴팀 , prev : 이전에 점수난 시간
int n;
int asum,bsum; //이긴시간 (초)
int a=0; //점수
int b=0;

string to_str_time(int score){
    string m = "00" + to_string(score / 60);
    string s = "00" + to_string(score % 60);
    return m.substr(m.size()-2,2) + ":" + s.substr(s.size()-2,2);
}

int to_int_time(string str){
    int m = atoi(str.substr(0,2).c_str()) * 60;
    int s = atoi(str.substr(3,2).c_str());
    return m+s;
}

void go(int& team, string now){
    team += to_int_time(now) - to_int_time(prev);
    // cout << team <<"gi\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i=0; i<n; i++){
        string now; //현재시간
        cin >> o >> now;
        //더높은점수인 팀 시간 기록
        if(a>b) go(asum,now);
        else if(b>a) go(bsum,now);
        //prev갱신
        prev = now;
        //팀점수갱신
        o==1 ? a+=1 : b+=1;
    }
    if(a>b) go(asum,"48:00");
    else if(b>a) go(bsum,"48:00");
    //합산
    // cout << asum << bsum << endl;
    cout << to_str_time(asum) <<"\n";
    cout << to_str_time(bsum) <<"\n";
    return 0;
}
