#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;
vector<int> a;
vector<int> b;
int a_s, b_s;
int ret = 0;
int mid;


void solve(vector<int> aa, vector<int> bb){

  for(int i=0; i<aa.size(); i++){
    int here = aa[i];
    int leftt = 0; int rightt = bb.size();

    while(1){
      mid = (leftt + rightt) / 2;
      if(leftt > rightt || mid >= bb.size()){
        ret++;
        break;
      }
      
      if(here < bb[mid]){
        rightt = mid - 1;
      }
      else if(here > bb[mid]){
        leftt = mid + 1;
      }
      else if(here == bb[mid]){
        break;
      }
    }
  }
  return;
}



int main(){
  cin >> a_s >> b_s;
  for(int i=0; i<a_s; i++){
    int tmp;
    cin >> tmp;
    a.push_back(tmp);
  }
  for(int i=0; i<b_s; i++){
    int tmp;
    cin >> tmp;
    b.push_back(tmp);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  solve(a,b);
  solve(b,a);
  cout << ret;



  return 0;
}
