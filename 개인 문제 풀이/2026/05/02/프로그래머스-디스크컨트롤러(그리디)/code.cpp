#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<vector<int>> jobs) {
    int answer = 0; 
    int n = jobs.size();
    sort(jobs.begin(),jobs.end());
    int t=0;
    int work=0;
    int count = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    while(count < n){
        while(work < n && t >= jobs[work][0]){ //현재 시간보다 작으면
            pq.push({jobs[work][1], jobs[work][0]}); 
            work++;
        }
        //가장 우선순위 선정
        if(pq.size()){
            answer += ((t + pq.top().first) - pq.top().second);
            t += pq.top().first;
            pq.pop();
            count++;
        }
        else{
            t = jobs[work][0];
        }
    }
    
    return answer/n;
}
