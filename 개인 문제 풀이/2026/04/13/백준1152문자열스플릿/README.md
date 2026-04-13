https://www.acmicpc.net/status?user_id=utsi09&problem_id=1152

---

풀었던건데 기억할겸 다시 풀어봄

```cpp
string line;
getline(cin,line);
```

로 입력받고 커스텀 split 함수에서 

string 라이브러리에 있는 find 함수와 substr을 이용해

딜리미터를 찾고 start를 옮기고 마지막에 남은걸 추출하는 식으로한다

substr의 두번째 인자를 헷갈리면 안되는데 pos가 아니라 추출할 사이즈를 의미한다.

이문제도 현모 기출에있어서풀어봤다
