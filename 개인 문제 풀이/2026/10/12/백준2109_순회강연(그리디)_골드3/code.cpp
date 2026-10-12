#include <bits/stdc++.h>
using namespace std;

int n;
int day, fee;
priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> pq;
int cnt;

int main(){
    cin >> n;
    if(n == 0){
        puts("0");
        return 0;
    }
    for(int i=0; i<n; i++){
        cin >> fee >> day;
        pq.push({day,fee});
    }

    int first_day = pq.top().first; //가장 뒤에 있는 일정
    for(int t=first_day; t>=1; t--){ //역순으로 진행
        if(pq.empty() || pq.top().first < t) continue; //아직 day 아니면 패스
        int val = pq.top().second; //받을돈
        int today = pq.top().first; //마감일
        cnt += val; //무조건 마감일과 같거나 그전이므로 결과값에 반영
        pq.pop();
        queue<int> q; // 버리지않고 재활용, 역순이므로 계속 활용가능함
        while(pq.size() && pq.top().first == today){ //마감일과 pop했던 것과 중복이면 사용 계속 가능하도록 마감일 조정하기
            int tmp = pq.top().second; //요금
            q.push(tmp); //일단 큐에 넣기
            pq.pop(); 
        }
        while(q.size()){ //큐에 있는 것들 재사용 가능하도록 세팅
            pq.push({t-1, q.front()});
            q.pop();
        }
    }
    cout << cnt;
    return 0;
}
