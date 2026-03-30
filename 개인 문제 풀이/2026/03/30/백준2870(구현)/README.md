https://www.acmicpc.net/problem/2870

---
# 내생각
```cpp
if (s[j] < 65) ret+=s[j];
```
다음과 같이 아스키코드를 기준으로 숫자를 검사 사실 string값에 int 씌우면 알수있어서 외울필요는 없는것같다

```cpp
 if(j==s.size()-1 && ret.size()) go();
```
해당 줄로 마지막인덱스때 남아있는게 있으면 go 함수 돌리도록 했음

```cpp
bool cmp(string a, string b){
    if(a.size() != b.size()) return a.size() < b.size();
    return a < b;
}
```
return a.front() < b.front() 하면 앞 숫자만 비교하므로 주의

```cpp
ret+=s[j];
```
당연하지만 스트링은 += 연산이 가능하다

---
# 보완

추가적으로 내 코드에서는 
```cpp
 if(j==s.size()-1 && ret.size()) go();
```
매번 루프에서 마지막인지 검사하지만 

```cpp
	for(int i = 0; i < n; i++){
		cin >> s; 
	 	ret = "";
		for(int j = 0; j < s.size(); j++){
			if(s[j] < 65)ret += s[j];
			else if(ret.size()) go(); 
		}
		if(ret.size()) go(); 
	}
```
이방식이 훨씬 깔끔한것같다
