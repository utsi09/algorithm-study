각 시선마다 left와 right 변수를 증가시키는 방식으로 시야가 퍼져나가는걸 구현했음

전사들은 벽이 상관없기 때문에 bfs가 아닌 단순 
```cpp
int mob_bfs(int y, int x, int ey, int ex){
    return abs(y - ey) + abs(x - ex);
}
```
로 구현 해도 됨
이걸 늦게 깨달아서 bfs로 몹들도 처리했다가 시간초과를 많이 당했다
