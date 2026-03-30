https://www.acmicpc.net/problem/2870

---
#내생각
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
