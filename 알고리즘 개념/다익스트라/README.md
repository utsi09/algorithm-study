<img width="1400" height="876" alt="Image" src="https://github.com/user-attachments/assets/1b9c8122-3016-4ad9-aad8-92d71e4ab7a8" />

BFS의 queue 를 우선순위 큐로 교체하고

visited[ny][nx] = visited[i][j] + 1 을

dist[v] = now_w + next_w 로 교체하면 그게 다익스트라다

즉 pair<(weight), (vertex)> 형태의 우선순위큐로 dist를 갱신해간다. 

