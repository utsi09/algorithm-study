#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>
using namespace std;

struct format{
    string head;
    int num=0;
    int idx=0;
};

bool comp(const format& a, const format& b){
    if(a.head < b.head) return true; //
    else if(a.head == b.head){
        if(a.num < b.num) return true;
        else if(a.num == b.num){
            if(a.idx < b.idx) return true;
        }
    }
    return false;
}


vector<string> solution(vector<string> files) {
    vector<string> answer;
    vector<format> standard_files; //정의된 파일
    int n = files.size();
    for(int i=0; i<n; i++){ //파일 하나하나 파싱 시작
        int fs = files[i].size();
        format tmp;
        tmp.idx = i;
        bool is_header = true; //현재 헤더 영역인지
        int num_cnt = 0; //num 영역 5개 최대
        for(int ii=0; ii<fs; ii++){
            bool is_int = (int(files[i][ii]) <= 57 && int(files[i][ii] >=48));
            if(!is_int && !is_header){
                break;
            }
            else if(!is_int && is_header){ //string 헤더에 넣기
                tmp.head.push_back(tolower(files[i][ii]));
            }
            
            else if(is_int && num_cnt <= 5){ //숫자 NUM에 넣기
                num_cnt++;
                is_header=false;
                tmp.num = tmp.num*10 + (tolower(files[i][ii]) - '0');
            }
        }
        cout << tmp.head << " : head\n";
        cout << tmp.num << " : num\n";
        standard_files.push_back(tmp);
    }
    
    sort(standard_files.begin(), standard_files.end(), comp);
    
    for(format tmp : standard_files){
        int here = tmp.idx;
        answer.push_back(files[here]);
    }
    
    return answer;
}