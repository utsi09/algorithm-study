## 제일 베이직한 BFS 문제
1. 가중치같은 그리드 그래프에서 최단거리를 찾는 문제임
2. 실버1 문제

https://www.acmicpc.net/problem/2178

4 6

101111

101010

101011

111011

위와 같이 입력이 따닥따닥 붙어있는 경우는 **scanf**로 입력처리

```cpp
for(int i=0; i<end_y; i++){
        for(int j=0; j<end_x; j++){
            scanf("%1d", &adj[i][j]);
        }
    }
