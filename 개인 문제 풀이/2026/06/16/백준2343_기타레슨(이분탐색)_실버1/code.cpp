#include <bits/stdc++.h>
using namespace std;
#define INF 987654321
int n,m;
int lecture[100004];
int left_i;
int right_i;
int ret = 98765432;

bool checker(int length){
    int now_length;
    int idx = 0;
    for(int i=0; i<m; i++){ //블루레이 수
        now_length = length; //풀피
        while(1){
            if(idx < n && now_length >= lecture[idx]){ //강의 수 초과하지않고 블루레이 길이 초과x
                now_length -=  lecture[idx];
                idx++;
                //cout << idx << " : processed\n";
            }
            else {
                break;
            }
        }
    }
    return (idx == n);
}

int main() {
    cin >> n >> m;
    left_i=1; right_i=0;
    for(int i=0; i<n; i++){
        cin >> lecture[i];
        right_i += lecture[i]; //최대 right는 모든 강의 길이를 더한 값
    }

    while(1){
        if(left_i > right_i) break;
        int mid = (left_i + right_i) / 2;
        //cout << mid << " : MID \n";
        if(checker(mid)){
            ret = min(ret, mid);
            right_i = mid - 1;
        }
        else{
            left_i = mid + 1;
        }
    }

    cout << ret;

    return 0;
}
