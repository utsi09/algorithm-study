https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/baby-whale-first-voyage/description
소요시간 2시간 원트 성공

---

현재 고래가 보고있는 방향에 따라 탐색하는 방향 우선순위가 다르기 때문에 탐색 배열인 dy, dx 를 2차원 배열로 첫번째 차원은 현재 보고 있는 방향

두번째 차원은 우선순위로 저장했다

사방이 막혀있는 경우는 일반적인 bfs로 이동하되 방향은 저장해야되는데

```cpp
if(ny<ii) tmp_d = 0; else if(ny>ii) tmp_d = 1;
            else if(nx<jj) tmp_d = 2; else if(nx>jj) tmp_d = 3;
```
이 경우에는 이렇게 이동한 위치와 원래 위치를 비교해 방향을 저장하고

best_d가 되면 tmp_d 를 받고 최종적으로 받은 best_d를 전역 d로 저장하는 방식으로 구현했다
