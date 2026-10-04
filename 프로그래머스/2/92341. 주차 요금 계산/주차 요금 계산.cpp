#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

map<string, queue<int>> dic; //str 차번호, 시간


vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    int free_time = fees[0];
    int base_fee = fees[1];
    int unit_time = fees[2];
    int unit_fee = fees[3];
    
    for(string this_line : records){ //기록 한줄 파싱
        string car_num = this_line.substr(6, 4); //차번호 str
        int nt = stoi(this_line.substr(0,2)) * 60 +  //분단위 시간
            stoi(this_line.substr(3,2));
        dic[car_num].push(nt); 
    }
    
    for(pair<string, queue<int>> q : dic){
        //cout << q.second.front() << '\n';
        int this_fee = 0;
        int parking_time = 0;
        while(!q.second.empty()){
            int last_time = q.second.front();
            q.second.pop();
            if(!q.second.empty()){ //출차 관리
                parking_time += q.second.front() - last_time;
                q.second.pop();
            }
            else{ //마지막에 출차가 안됐으면
                parking_time += 1439 - last_time;
            }
        }
        this_fee += base_fee;
        if(parking_time > free_time){ //기본시간 초과시
            this_fee += ((parking_time - free_time + unit_time - 1) 
                         / unit_time) * unit_fee;
        }
        answer.push_back(this_fee);
        //cout << q.first << " -> parking time is :" << parking_time << '\n';
    }
    
    return answer;
}