<img width="1400" height="876" alt="Image" src="https://github.com/user-attachments/assets/0a3398b7-5aca-4d92-b866-70dae1d37839" />

1. 음수 가중치가 있고 음수 사이클을 감지할때 사용하는게 벨만 포드다

(음수 가중치가 있고 음수 사이클은 없을때 && V <= 400 일때는 플로이드 워셜)

(음수 가중치와 음수 사이클이 없을때 한 시작지점에서 모든 지점까지의 최단 거리를 구할땐 다익스트라)

모든 정점이 간선의 방향이 1 -> 2 -> 3 -> 4 일땐 한번의 스테이지 진행으로 모두 갱신하지만

만약 방향이 1 <- 2 <- 3 <- 4 일땐 스테이지를 최악의 경우 v-1 번 반복한다

벨만 포드는 한번 더 돌렸을때 변화가 생기면 (최단거리가 바뀔 경우는 음수 사이클이 있을 때니까) 음수 사이클이 있다고 판단한다.


cpp```
for(int i=0; i<n; i++){
        for(int here = 1; here <= n; here++){
            for(pair<int,int> arrow : adj[here]){
                int weight = arrow.first;
                int to = arrow.second;
                int new_cost = weight + dist[here];
                if(dist[here] != INF && dist[to] > new_cost){
                    if(i == n-1) q.push(to);
                    dist[to] = new_cost;
                }
            }
        }
    }

```
