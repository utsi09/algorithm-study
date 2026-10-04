#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int t=1;
int on_road = 0; //도로위의 현재 중량
int idx = 0; //트럭 포인터
int pop_cnt = 0;
int last_t = 0;
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    queue<pair<int,int>> q;
        
    while(1){
        int next_w = truck_weights[idx]; //다음 트럭 무게
        if(on_road + next_w <= weight && last_t != t){ //동시에 올라가는거 불가능
            q.push({next_w, t}); //무게, 투입시기
            on_road += next_w;
            cout << idx << ":idx || is on || on load : " << on_road << "time is " << t << endl;
            idx++;
            last_t = t;
        }
        else{
            t++;
        }
        if(t >= q.front().second + bridge_length){ //지나간 시간이면
            cout << "time : " << t << " || " << q.front().first << " is gone \n";
            cout << "now idx : " << idx << '\n';
            on_road -= q.front().first;
            q.pop();
            pop_cnt++;
            if(pop_cnt == truck_weights.size()) break;
        }
        
        
  
    }
    
    answer = t;
    return answer;
}
