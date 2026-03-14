https://www.acmicpc.net/problem/1992

# 내 생각

쿼드 트리 , 조건이 맞지않을 경우 사이즈의 절반만큼 다시 재귀함수를 호출하는 것이 특징이다.

처음에 adj맵을 int로 선언해서 틀렸음.

```cpp
string(1, adj[y][x]);

첫번째 인자의 길이만큼 두번째 인자의 char를 넣는다
