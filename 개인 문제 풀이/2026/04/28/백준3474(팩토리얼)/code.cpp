#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
int n;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i=0; i<n; i++){
        int tmp; cin >> tmp;
        int num_2=0;
        int num_5 =0;

        for(int j=2; j<=tmp; j*=2){
            num_2 += tmp / j;
        }
        for(int k=5; k<=tmp; k*=5){
            num_5 += tmp / k;
        }
        cout << min(num_2, num_5)<<"\n";
    }

    return 0;
}
