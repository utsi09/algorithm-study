트리랑 그리디로 푸는 문제 인줄 알고

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;
int n,m;

struct node{
    int idx; //자식노드 삽입용
    int val; // value
    node *c1 = NULL; //자식노드 1
    node *c2 = NULL; //자식 노드 2
    bool is_pop = false;
};
vector<node> v;
bool is_root = false;
priority_queue<pair<int , int>> pq;
int cnt = 0;


int cal(node& n){
    int tmp_ret = 0;
    for(node &nn : v){
        if(nn.c1 ==NULL && nn.c2 == NULL && nn.is_pop == false){
            tmp_ret += nn.val;
        }
    }
    tmp_ret += n.val;
    if(n.idx == 1) is_root = true;
    return tmp_ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i=1; i<=n; i++){ //idx는 1부터기 때문에
        node tmp;
        tmp.idx = i;
        cin >> tmp.val;
        v.push_back(tmp);
        pq.push({tmp.val,tmp.idx}); //값, idx 값 기준 내림차순
    }
    for(int i=1; i<n; i++){ //결국 push_back된건 0부터
        int tmp_parrent; cin >> tmp_parrent;
        for(node &n : v){
            if(n.idx == tmp_parrent){
                if(n.c1 == NULL) n.c1 = &v[i];
                else n.c2 = &v[i];
            }
        }
    }
    //cout << v[8].val<< endl;
    while(1){
        if(is_root) break;

        //1.값이 가장 높은 리프노드를 꺼낸다
        pair<int,int> tmp = pq.top(); pq.pop();
        //int tmp_val = tmp.first; 
        int tmp_idx = tmp.second;
        if(v[tmp_idx-1].c1 != NULL || v[tmp_idx-1].c2 != NULL) continue; //리프노드 아니면 스킵
        //cout << ":start " << tmp_val << ":" << tmp_idx << endl;
        //2. 그 리프노드의 부모를 찾아서 연산 후 pop을 한다 , cnt에 반영
        for(node &n : v){
            //cout << "hi\n";
            if(n.c1 != NULL && n.c1->idx == tmp_idx){
                //cout << n.idx << " is parrent(c1) >" << tmp_idx << endl;
                int ret = cal(n);
                cnt = max(cnt, ret); //피크메모리
                n.c1->is_pop = true;
                n.c1 = NULL;
                break;
            }
            else if(n.c2 != NULL && n.c2->idx == tmp_idx){
                //cout << n.idx << " is parrent(c2) >" << tmp_idx << endl;
                int ret = cal(n);
                cnt = max(cnt, ret); //피크메모리
                n.c2->is_pop = true;
                n.c2 = NULL;
                break;
            }
        }
        //cout << cnt<<endl;
    }
    if(cnt > m) cout << "OOM";
    else cout << cnt;
    return 0;
}
```

이렇게 했는데 로직도 무조건 각 노드 크기가 1인지 이해못했어서 이렇게 풀었었고

처음 인풋에서 리프노드 + 1 이 정답이다
