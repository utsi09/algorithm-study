#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

queue<pair<int,int>> q; //우선순위 , cnt 확인용 0,1

int solution(vector<int> priorities, int location) {
    int answer = 1;
    for(int i=0; i<priorities.size(); i++){
        if(i == location) q.push({priorities[i],1});
        else q.push({priorities[i], 0});
    }
    while(1){
        queue<pair<int,int>> tmpq = q;
        int this_p = q.front().first;
        int this_cnt = q.front().second;
        
        tmpq.pop();
        bool bigger_exist = false;
        while(tmpq.size()){
            if(tmpq.front().first > this_p){
                bigger_exist = true;
                cout << "bigger is exist\n";
                break;
            }
            else{
                tmpq.pop();
            }
        }
        if(bigger_exist){
            q.pop();
            q.push({this_p, this_cnt});
        }
        else{
            if(this_cnt){ //찾았던 idx면
                break;
            }
            q.pop();
            answer++;
        }
        
    }

    return answer;
}