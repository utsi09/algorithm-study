#include <iostream>

using namespace std;
int n;
int min_open;
int max_open;


int main(){
  cin >> n;

  if(n%2 == 1){
    cout<<"No";
    return 0;
  }

  for(int i=0; i<n; i++){
    char this_c;
    cin >> this_c;

    if(this_c == '('){
      min_open++;
      max_open++;
    }

    else if(this_c == ')'){
      min_open--;
      max_open--;
    }

    else if(this_c == '?'){
      min_open--;
      max_open++;
    }
    
    min_open = max(0, min_open);
    if(max_open < 0){
      cout<<"No";
      return 0;
    }
  }

  cout << (min_open == 0 ? "Yes" : "No");


  return 0;
}
