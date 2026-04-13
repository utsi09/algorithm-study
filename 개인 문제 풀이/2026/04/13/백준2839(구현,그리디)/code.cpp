#include <iostream>
using namespace std;
int n;
int num5; //5키로 봉투 개수
int mod5; //5로 나눈 나머지
int num3 = 0; //3키로 봉투 개수
bool checker = false; //성공 판단
int t;

int main(){
    cin >> n;
    num5 = n / 5; // 18 > 3,
    //mod5 = n % 5; // 18 -> 3
    //cout << num5;
    for(t=num5; t>=0; t--){ //3 일때 떨어지는지. 2일때 떨어지는지 / 1일때 떨어지는지/ 마지막 3키로만으로 되는지
        //cout << t << ": 5kg num\n";
        if(t != 0) mod5 = n - (5 * t); //modq5 줄어든 num5로 갱신 
        else mod5 = n; //5키로주머니가 0이니깐 그대로
        //cout << mod5 << ": mod num\n";
        if(mod5 == 0){ //조건 달성
            checker = true;
            break;
        }
        if(mod5 % 3 == 0){
            num3 = mod5 / 3; //나눠떨어지면 그 갯수 저장
            checker = true;
            break;
        }
        //cout << t << ": 5키로 봉투 개수\n";
    }
    num5 = t; //5키로 봉투 

    if(checker == false){
        cout << -1;
        return 0; //프로그램 종료
    }

    cout << (num5 + num3);
    return 0;
}
