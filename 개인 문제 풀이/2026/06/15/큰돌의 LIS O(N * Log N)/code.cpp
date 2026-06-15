#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int n,num,len;
int lis[1004];


int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> num;
        auto lowerPos = lower_bound(lis, lis+len, num);
        if(*lowerPos==0) len++;
        *lowerPos = num;
    }
    cout << len;
    return 0;
}
