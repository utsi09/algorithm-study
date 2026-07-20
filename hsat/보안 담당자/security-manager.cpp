#include <iostream>
using namespace std;
int n;
int min_open;
int max_open;
int min_close;
int max_close;
int change = 0;

int main(){
  cin >> n;
  if(n%2 == 1){
    cout << "No";
    return 0;
  }

  for(int i=0; i<n; i++){
    char this_c;
    cin >> this_c;
    if(this_c == '('){
      min_open++;
      max_open++;
    }
    if(this_c == ')'){
      min_open--;
      max_open--;
    }
    if(this_c == '?'){
      min_open--;
      max_open++;
    }
    
    min_open = max(0, min_open);

    if(max_open < 0){
      cout << "No\n";
      return 0;
    }
    //cout << "min open : " << min_open << "|| max open : " << max_open << " || min close :" << min_close << " || max close : "<< max_close <<'\n';
  }

  cout << (min_open == 0 ? "Yes" : "No");

  return 0;
}