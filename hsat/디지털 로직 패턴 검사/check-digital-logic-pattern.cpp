#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
int k,m;


int main(){
	string s;
	cin >> s;
	cin >> k >> m;
	unordered_map<unsigned long long,int> cnt;
	for(int i=0; i<=s.size() - k; i++){
		unsigned long long pwd = 0;
		for(int idx=i; idx<i+k; idx++){ //k 길이 만큼 
			int tmp = s[idx] - '0';
			pwd = pwd * 2 + tmp;
		}
		cnt[pwd]++;
		if(cnt[pwd] >= m){
			cout << "1\n";
			return 0;
		}
	}

	cout << "0\n";
	return 0;
}
