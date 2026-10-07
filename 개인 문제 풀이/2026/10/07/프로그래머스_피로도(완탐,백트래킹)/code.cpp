#include <string>
#include <vector>

using namespace std;
int visited[10];


int rpg(int k, auto dungeons){ //현재 hp
    int ret = 0;
    for(int i=0; i<dungeons.size(); i++){
        if(visited[i] || k < dungeons[i][0]) continue; //최소필요피로도 검사
        visited[i] = 1;
        ret = max(ret, rpg(k-dungeons[i][1], dungeons) + 1);
        visited[i] = 0; //백트래킹
    }
    return ret;
}


int solution(int k, vector<vector<int>> dungeons) {
    int answer = rpg(k, dungeons);
    return answer;
}
