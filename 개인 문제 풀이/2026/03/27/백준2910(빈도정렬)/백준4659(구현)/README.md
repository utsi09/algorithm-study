https://www.acmicpc.net/problem/4659

---

구현 문제이다

```cpp
while(cin >> passwd && passwd != "end")
```
이렇게 입력과 동시에 검사하도록 처리하는 부분

그리고 이전에는 벡터로 매번 이전과 다르면 초기화하고 size로 검사하는 식으로 했었는데 cnt가 훨씬 깔끔한것같다

그리고 사소하지만 중요한건데

```cpp
if (!(curr=='e' || curr=='o'))
```

이것과

```cpp
if (curr!='e' || curr!='o'))
```

이것은 다르다
