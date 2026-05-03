#include <bits/stdc++.h>
using namespace std;
int n;
int ret = 0;


int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    vector<pair<int,int>> rec(n);
    for(int i=0; i<n; i++){
        int p,d; cin >> p >> d;
        rec[i].first = d; rec[i].second = p; //날짜 , 돈 순서
    }
    sort(rec.begin(), rec.end());
    reverse(rec.begin(),rec.end());

    priority_queue<int> pq;
    int j=rec[0].first; //가장높은날짜
    int count = 0;
    int done = 0;
    while(done < n && j > 0){
        while(rec[count].first == j){ //아직 다 못 넣고 거꾸로 오는 일정 날짜가 날짜와 일치할때
            pq.push(rec[count].second);
            count++;
        }
        if(pq.size()) {ret += pq.top(); pq.pop(); done++;} //있으면 같은 시간대중 가장 높은 가격대 ret에 +

        //j를 다음 count 시간대로 업데이트
        //pq가 비었다면 다음시간대로 순간이동 / 안비었으면 그냥 j-1하고 pq덧셈
        if(pq.empty()) j = rec[count].first;
        else j--;
    
    }

    cout << ret;
    return 0;
}

