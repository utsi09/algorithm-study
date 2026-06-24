https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/escape-unknown-space/description

---

<img width="1400" height="876" alt="Image" src="https://github.com/user-attachments/assets/62a748d7-ea3c-48a6-895e-5860ae055b5e" />

다른 문제들보다 빡셌는데 2차원 BFS 만 풀다가 3차원 BFS를 마주하니까 어떻게 접근해야할지 몰랐다

중간에 코드를 몇번 갈아 엎었는데

처음엔 입력되는 시간의 공간 단면도가 시간의 공간 천장 기준인 줄 알고 시간을 날렸고 (미지의공간 기준 단면도 였음)

두번째엔 미지의 공간 기준 단면도니까 바로 이어 붙이면 되겠다 쉽구나 하고 생각없이 입력값그대로 m*4m 배열을 붙였다가

가장 중요한건 옆면간의 이동이 되냐인데 동서남북 그대로 붙이니까 될리가 없다

마지막엔 그래도 이어붙였던 순서를 기준으로 BFS 함수들의 매핑을 고쳐주니까 정답이 나왔다

이외에 생각나는건 순서를 하드코딩하지않고 hash_table 배열을 만들어서 i -> m*4m에 매핑 시켜줬던 거랑

막히는 시간인 ab_map을 -1로 초기화 시켜서 아직 이동하지않은 이상현상과 구분했던 것 정도이다.
