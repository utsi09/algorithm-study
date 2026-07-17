#include <bits/stdc++.h>
using namespace std;
#define INF 98765432
int n,m,k;
int adj[11][11];
int er,ec; //exit
int dy[4] = {-1, 1, 0, 0}; //상하좌우
int dx[4] = {0, 0, -1, 1};
int ret_d=0;
int temp[11][11]; //회전 맵
int cnt = 0;

struct npc{
	int r,c;
	bool is_escape = false;
};
vector<npc> npcs;

int tr, tc; //정사각형 좌상단 좌표
int br, bc; //정사각형 우하단 좌표

int get_d(int ny, int nx){
	return abs(er - ny) + abs(ec - nx);
}

void db_rmap(){
	for(int i=tr; i<=br; i++){
		for(int j=tc; j<=bc; j++){
			cout << adj[i][j] <<" ";
		}
		cout <<'\n';
	}

	for(int i=tr; i<=br; i++){
		for(int j=tc; j<=bc; j++){
			cout << temp[i][j] <<" ";
		}
		cout <<'\n';
	}
}

void db_map(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << adj[i][j] << " ";
		}
		cout <<'\n';
	}
	
}

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> adj[i][j];
		}
	}
	for(int i=0; i<m; i++){
		npc tmp;
		cin >> tmp.r >> tmp.c;
		tmp.r--;
		tmp.c--;
		npcs.push_back(tmp);
	}
	cin >> er >> ec;
	er--;
	ec--;

	for(int t=0; t<k; t++){
		
		//cout << "-------" << t << "------\n";
		//cout << er <<","<<ec <<" : goal\n";
		//cout << npcs.size() <<'\n';
		//1. 참가자들의 움직임
		for(npc& me : npcs){
			if(me.is_escape) continue;
			int best_ret = get_d(me.r, me.c); //현재보다 가까워지지않으면 움직임 x
			int best_d = -1;
			for(int d=0; d<4; d++){
				int ny = me.r + dy[d];
				int nx = me.c + dx[d];
				if(ny<0 || nx<0 || ny>=n || nx>=n || adj[ny][nx]) continue;
				int this_ret = get_d(ny,nx);
				if(this_ret < best_ret){
					best_d = d;
					best_ret = this_ret;
				}
				//상하 우선은 자동 구현
			}
			//cout << me.r <<","<<me.c <<" >> ";
			if(best_d != -1){ //움직임 처리
				me.r += dy[best_d];
				me.c += dx[best_d];
				ret_d++;
			}
			//cout << me.r <<","<<me.c <<"\n";
			if(me.r == er && me.c == ec){
				me.is_escape = true;
				cnt++;
				me.r = -1;
				me.c = -1;
			}
		}

		if(cnt == m) break;
		// 2. 미로의 회전
		/*
		높이나 넓이중 큰 값 기준으로 정사각형 윈도우를 만들어서 갱신
		*/
		// 2.1 가장 작은 정사각형 구하기
		
		tr = INF;
		tc = INF;
		br = INF;
		bc = INF;
		int best_ws = INF; //정사각형 크기
		for(int i=0; i<npcs.size(); i++){
			if(npcs[i].is_escape) continue;
			int ii = npcs[i].r;
			int jj = npcs[i].c;
			//cout << ii <<"," << jj << ": start\n";
			int ws = max(abs(er-ii), abs(ec-jj)) + 1; //윈도우 사이즈
			if(ws > best_ws) continue; //정사각형 크기로 거르기
			if(ws < best_ws){
				tr = INF;
				tc = INF;
				br = INF;
				bc = INF;
			}
			best_ws = ws;
			//cout <<"window size : " <<best_ws<<'\n';
			bool exit_checker = false; //최적의 좌상단 나왔으면 true
			for(int r=0; r<n; r++){
				for(int c=0; c<n; c++){ //모든 행과 열을 시작점으로
					bool size_checker = true; //윈도우가 맵 안에 들어가는지
					bool npc_checker = false; //윈도우 안에 npc 있는지
					bool end_checker = false; //윈도우 안에 탈출구 있는지
					
					for(int rr=r; rr<r+ws; rr++){
						for(int cc=c; cc<c+ws; cc++){
							if(cc >= n || rr >= n){
								size_checker = false;
								//cout << "size false\n";
							}
							if(rr == ii && cc == jj){
								npc_checker = true;
								//cout << "npc_checker = true;\n";
							}
							if(rr == er && cc == ec){
								end_checker = true;
								//cout << "end_checker = true;\n";
							}
						}
					}
					if(size_checker == true && npc_checker == true && end_checker == true){
						//이미 좌상단 부터 했기 때문에 최소r,c는 불필요
						if(r > tr) continue;
						if(r == tr && c > tc) continue;
						tr = r; 
						tc = c;
						br = tr + ws - 1;
						bc = tc + ws - 1;
						//cout <<"changed to : "<< tr <<"," << tc << "\n"; 
						exit_checker = true;
					}
					if(exit_checker) break;
				}
				if(exit_checker) break;
			}

		}

		//cout << tr <<"," << tc <<" ~ " << br <<"," <<bc <<" : best box\n"; 


		// 2.2 정사각형의 회전
		//맵 회전
		//cout << "best ws :" << best_ws <<'\n';
		fill(&temp[0][0], &temp[0][0]+11*11, 0);
		
		for(int i=tr; i<=br; i++){
			for(int j=tc; j<=bc; j++){
				int local_r = i - tr; //로컬좌표계
				int local_c = j - tc;

				int temp_r = local_c;
				int temp_c = best_ws - local_r - 1; 
				temp[temp_r+tr][temp_c+tc] = adj[i][j];
			}

		}
		
		for(int i=tr; i<=br; i++){
			for(int j=tc; j<=bc; j++){
				adj[i][j] = temp[i][j];
				if(adj[i][j] > 0) adj[i][j]--;
			}
		}
		//db_map();
		
		//npc 회전
		for(npc& me : npcs){
			if(me.is_escape) continue;
			if(!(tr <= me.r && br >= me.r) || !(tc <= me.c && bc >= me.c)) continue; //정사각형 범위 외면 스킵
			int local_y = me.r - tr;
			int local_x = me.c - tc;
			me.r = local_x;
			me.c = best_ws - local_y - 1;
			me.r += tr;
			me.c += tc;
		}
		//탈출구 회전
		int local_er = er - tr;
		int local_ec = ec - tc;
		er = local_ec;
		ec = best_ws - local_er - 1;
		er += tr;
		ec += tc;
	}


	cout << ret_d <<'\n';
	cout << er+1 <<" " <<ec+1;


	return 0;
}
