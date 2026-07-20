#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int min_open;
int max_open;


int main(){
  cin >> n;
  if(n % 2 == 1){
    cout <<"No";
    return 0;
  }
  cin >> s;
  for(int i=0; i<n; i++){
    if(s[i] == '('){
      min_open++;
      max_open++;
    }
    else if(s[i] == ')'){
      min_open--;
      max_open--;
    }
    else{
      min_open--;
      max_open++;
    }
    min_open = max(0, min_open);

    if(max_open < 0){
      cout <<"No";
      return 0;
    }
  }

  cout << (min_open == 0 ? "Yes" : "No");

  return 0;
}

/*

)가 더많은데 지나가거나
뒤에 ( 로 끝나거나

(와) 숫자가 다르거나
n이 홀수이거나

최소 ( 랑 최대 ( 을 계산


*/