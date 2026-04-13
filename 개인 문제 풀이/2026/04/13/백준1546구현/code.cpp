#include <iostream>
#include <vector>
using namespace std;
vector<float> scores;
int n;
float max_s=0;
float cnt=0.0;

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        float tmp; cin>>tmp;
        scores.push_back(tmp);
    }
    for(float& score : scores){
        max_s = max(score, max_s);
    }
    for(float& score : scores){
        score = score / max_s * 100;
        cnt += score;
    }
    cout << (cnt / scores.size());
    
    return 0;
}
