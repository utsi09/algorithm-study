#include <iostream>
#include <vector>
#include <string>
using namespace std;
string a,b,c,d;
long long ab, cd;

int main(){
    cin >> a >> b >> c>> d;
    ab = stoll(a+b);
    cd = stoll(c+d);
    cout << ab+cd;
    return 0;
}
