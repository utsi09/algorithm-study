#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct car{
    int in=-1;
    int out=0;
    int use_time=0; //순수 주차시간
    bool last_state = 0; //0:출차 상태, 1:주차상태
    int fee = 0;
};

vector<int> car_list; //0 : 1231, 1:1231 차번호 기록용
car cars[10000];

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    int free_time = fees[0];
    int base_fee = fees[1];
    int unit_time = fees[2];
    int unit_fee = fees[3];

    int records_size = records.size();

    for(int i=0; i<records_size; i++){ //기록 한줄 파싱
        car tmp;
        int nt = (int(records[i][0]-'0')*10 + int(records[i][1]-'0')) * 60 + 
            (int(records[i][3]-'0')*10 + int(records[i][4]-'0'));
        //cout << nt << '\n'; 
        int this_car = 0;
        for(int idx : {6,7,8,9}){
            this_car = this_car*10 + int(records[i][idx]-'0');
        }
        car_list.push_back(this_car);
        if(cars[this_car].last_state == 0){ //출차상태였다면
            cars[this_car].last_state = 1;
            cars[this_car].in = nt;
        }
        else{ //주차 상태였다면
            cars[this_car].use_time += nt - cars[this_car].in;
            cars[this_car].in = -1;
            cars[this_car].out = 0;
            cars[this_car].last_state = 0;
            //cout << cars[this_car].use_time << '\n';
        }
    }

    sort(car_list.begin(), car_list.end());
    car_list.erase(unique(car_list.begin(), car_list.end()), car_list.end());
    for(int this_car : car_list){
        cout << "check :" << this_car << '\n';
        if(cars[this_car].in != -1){ //자정 지났는데 주차 돼있으면
            int midnight = 60*23 + 59;
            cars[this_car].use_time += (midnight - cars[this_car].in);
            cout << "+" << (midnight - cars[this_car].in) << '\n';
        }
        cars[this_car].fee += base_fee; //기본요금 무조건 냄
        cars[this_car].use_time = max(0, cars[this_car].use_time - free_time); //무료시간 차감

        if(cars[this_car].use_time % unit_time != 0){
            cars[this_car].fee += unit_fee;
        }
        cars[this_car].fee += (cars[this_car].use_time / unit_time) * unit_fee;
        cout << cars[this_car].fee << endl;
        answer.push_back(cars[this_car].fee);
    }

    return answer;
}
