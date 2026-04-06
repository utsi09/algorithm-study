https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/microbial-research/description

---

소요시간 : 6시간

이전 유형에서는 직사각형을 유지하기 위해 구조체로 w, h, r, c 이런식으로 저장했는데

이번 유형은 갉아먹히고 언제든 상태가 변할수있어서 

```cpp
struct Virus{
    int min_i, min_j, k;
    vector<pair<int,int>> shape;
    bool is_die=false;
};
```
이런식으로 제일 왼쪽 제일 아래를 기준으로 절대 좌표 앵커를 가지고 나머지는 상대 좌표로 shape 좌표 벡터를 저장했다.

그리고 디버깅용으로 시각화할때 기존처럼 하면 안되고 x가 오른쪽 y가 위로 가는 경우에는 

```cpp
 for(int i=n-1;i>=0;i--){
            for(int j=0;j<n;j++){
                cout << setw(1) << adj[i][j] << " ";
            }
            cout << endl;
        }
```

이런식으로 i 방향은 반대가 됐으므로 n에서 --되는 식으로 해야 제대로 나온다.

그리고 상태가 변한후 다시 min_i min_j를 갱신해야하는데

```cpp
        for(Virus& tmp_v : viruses){
            int min_i = 987654;
            int min_j = 987654;
            for(pair<int,int> p : tmp_v.shape){
                min_i = min(min_i, p.first);
                min_j = min(min_j, p.second);
            }
            tmp_v.min_i += min_i; 
            tmp_v.min_j += min_j;
            for(pair<int,int>& p : tmp_v.shape){ //상대좌표들 min 기준 업데이트
                p.first -= min_i;
                p.second -= min_j;
            }
```
가장 왼쪽 아래인거를 뽑고 

현재 min i랑 j에 그것을 더해야한다.

반대로 각 쉐이프 벡터에는 기준 상대 좌표를 빼야한다. 

중요한점은 갱신한 절대 좌표를 빼면 안되고 갱신한 상대좌표를 빼야한다는 것이다.

```cpp
if(!placed) v.is_die = true;
            else put_virus(v);
```
이부분도 else 처리를 안해서 죽은 바이러스 처리를 했음에도 바이러스를 그리려고 한 실수를 했다.

```cpp
if(k1 > k2) swap(k1,k2);
```
swap 함수는 변수간의 값을 바꿔주는 함수이다.

```cpp
sort(adj_virus.begin(), adj_virus.end());
        adj_virus.erase(unique(adj_virus.begin(), adj_virus.end()), adj_virus.end());
```
이 2줄은 벡터에 중복되는 값들이 있을때 오름순으로 정렬후 uniq로 중복되는것들은 뒤로 보내고 그 idx부터 end까지 날림으로서 유일한 값만 남기는 방법이다 

꼭 기억하자

