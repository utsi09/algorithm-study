#include <bits/stdc++.h>
using namespace std;
int h,k,r;

pair<queue<int>, queue<int>> workers[11][10000];
int ret = 0;

int main(){
    cin >> h >> k >> r;

    int intern_num = pow(2, h);
    for(int i=0; i<intern_num; i++){ //말단 인턴 수
        for(int j=0; j<k; j++){//말단 대기 업무
            int tmp;
            cin >> tmp;
            if(j%2==0) workers[h][i].first.push(tmp);
            else workers[h][i].second.push(tmp);
        }
    }

    for(int t=1; t<=r; t++){ // 날짜만큼 진행 1일부터 시작
        for(int i=0; i<=h; i++){ //0행부터 시작
            int reps = pow(2, i); 
            for(int j=0; j<reps; j++){ // 높이별 직원 개수는 2의 i승 
                if(i==0){ //부서장   
                    if(t % 2 == 1){ //홀수
                        if(workers[i][j].first.empty()) continue;
                        ret += workers[i][j].first.front();
                        //cout <<"odd : " << workers[i][j].first.front() << '\n';
                        workers[i][j].first.pop();
                    }
                    else{
                        if(workers[i][j].second.empty()) continue;
                        ret += workers[i][j].second.front();
                        //cout <<"even : " << workers[i][j].second.front() << '\n';
                        workers[i][j].second.pop();
                    }
                }
                else{ //큐에 있는 업무 올리기(받기x)
                    //상사기준 어디쪽 직원인지
                    if(j%2==0){ //왼
                        if(t % 2 == 1){ //홀수날 처리
                            if(workers[i][j].first.empty()) continue;
                            int work = workers[i][j].first.front();
                            workers[i][j].first.pop();
                            workers[i-1][j/2].first.push(work); //상사한테 올리기 (왼쪽 직원)
                        }
                        else{
                            if(workers[i][j].second.empty()) continue;
                            int work = workers[i][j].second.front();
                            workers[i][j].second.pop();
                            workers[i-1][j/2].first.push(work); //상사한테 올리기 (왼쪽 직원)
                        }
                    }
                    else{ //오른
                        if(t % 2 == 1){ //홀수날 처리
                            if(workers[i][j].first.empty()) continue;
                            int work = workers[i][j].first.front();
                            workers[i][j].first.pop();
                            workers[i-1][(j-1)/2].second.push(work); //상사한테 올리기 (왼쪽 직원)
                        }
                        else{ //짝수날
                            if(workers[i][j].second.empty()) continue; 
                            int work = workers[i][j].second.front();
                            workers[i][j].second.pop();
                            workers[i-1][(j-1)/2].second.push(work); //상사한테 올리기 (왼쪽 직원)
                        }
                    }
                }
            }
        }

    }

    cout << ret;
    return 0;
}
