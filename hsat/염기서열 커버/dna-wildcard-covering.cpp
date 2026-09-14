#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int N, M;
vector<string> sequences;

int ret = 98765432;
vector<string> dp; // 이 숫자일때 이런 문자열이다 저장

// [] 어떤 염기서열들을 조합했는지 비트마스킹으로 저장

vector<int> memo;

int solve(int mask){

    if(mask == 0) return 0;

    if(memo[mask] != -1)
        return memo[mask];

    // mask 전체가 초염기서열 하나로 합쳐짐
    if(!dp[mask].empty() && dp[mask] != "#"){
        return memo[mask] = 1;
    }

    int ret = N;

    // 가장 오른쪽의 1
    int first = mask & -mask;

    // mask의 부분집합만 순회
    for(int group = mask; group; group = (group - 1) & mask){

        // 같은 분할을 여러 순서로 보는 걸 줄임
        if(!(group & first))
            continue;

        // 이 group 자체가 하나의 초염기서열이 될 수 없음
        if(dp[group].empty() || dp[group] == "#")
            continue;

        ret = min(
            ret,
            1 + solve(mask ^ group)
        );
    }

    return memo[mask] = ret;
}



bool make_dna(int combi, int candidate){
    int next = combi | (1 << candidate);
    dp[next] = dp[combi];
    for(int i=0; i<M; i++){ //모든 자리 확인 
        if(dp[combi][i] == '.'){
            dp[next][i] = sequences[candidate][i];
            continue;
        }
        if(sequences[candidate][i] == '.'){
            dp[next][i] = dp[combi][i];
            continue;
        }
        if(dp[combi][i] == sequences[candidate][i]){
            dp[next][i] = dp[combi][i];
            continue;
        }
        return false;
    }

    return true;
}



void make_all(int combi){

    if(dp[combi] == "#") return;
    
    for(int i=0; i<N; i++){
        if(combi & (1 << i)){
            continue; //이미 반영했음
        }
        int next = combi | (1 << i);
        if(dp[next].empty()){ //
            if(!make_dna(combi, i)){
                dp[next] = "#"; //불가능 문자
                continue;
            }
            make_all(next);
        }

    }



}



int main() {
    cin >> N >> M;
    sequences.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> sequences[i];
    }

    dp.resize(1 << N);
    memo.resize(1 << N, -1);
    dp[0] = string(M, '.');
    make_all(0);
    
    cout << solve((1<<N) - 1);

    return 0;
}
