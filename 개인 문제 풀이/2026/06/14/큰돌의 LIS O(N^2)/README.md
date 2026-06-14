최대 부분 수열 즉 LIS 문제를 풀어봤다

dp와 아이디어가 유사하다

cnt[j] 에는 이전에 j 자리에서 만든 가장 좋은 LIS 값을 가지고 있고 
cpp
```
if(a[j] < a[i] && max_value < cnt[j]) max_value = cnt[j]

```
자기자신은 이미 검증되었으므로 max_value+1 한 값을 cnt[i]에 넣는다
