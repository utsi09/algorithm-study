#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> money) { // 5 , [1,2,5], -> 4
    int dp[100001];
    dp[0] = 1;
    for(int c : money){
        for(int i=1; i<100001; i++){
            if(i >= c) dp[i] += dp[i-c];
        }
    }

    int answer = dp[n];
    return answer;
}
