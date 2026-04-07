https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/mint-choco-milk/submissions?page=1&page_size=20

---

디버깅시

맵 초기화 부분 꼭 확인

if 안에서 continue 와 break 꼭 체크하기

q.push({ny,nx}); 같이 반복되는거 있는데 if 여러번 반복되면 누락되는 경우가 많음

char 마다 꺼내서 char 끼리 다 비교해서 +하고 vector에 넣고 erase unique 하는 방식으로 했는데 비효율적인것같다
