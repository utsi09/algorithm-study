  https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/magical-forest-exploration/submissions?page=1&page_size=20

  ---

  중앙에서 4가지 방향을 수식적으로 하려고 했는데 너무 복잡해서 dy dx를 중앙에서 더하는 방식으로 수정했다

  출구를 표시하는 방식도 모든 로봇 idx와 상관없이 -1로 처리했는데 로봇 idx에 음수를 취하는 방식이 훨씬 직관적이고 처리가 쉬웠다

  BFS에서 어떻게 출구로 연결해서 들어갈지 어려웠는데

  ```cpp
if(abs(adj[tmp_i][tmp_j]) == abs(adj[ny][nx]) || adj[tmp_i][tmp_j] < 0){ //양수 -> 음수
                //cout << adj[ny][nx] <<": visit!!\n";
                q.push({ny,nx});
                visited[ny][nx] = 1;
                tmp_rb.score = max(ny+1,tmp_rb.score);
            }
```
다음과 같이 음수 양수와 상관없이 절대값이 같으면 이동 가능, 음수일 경우 무조건 푸쉬하도록 하면 가능했다

출구에서는 0 이 아니면 어디든 이동 가능하고 

0 예외 처리는 앞에서 하기 때문이다.

출구값은 idx의 음수, 복잡한 구현없이 BFS에서 상단 내용과 같은 핵심을 제대로 이해하면 그외에 크게 어려운 부분은 없다
