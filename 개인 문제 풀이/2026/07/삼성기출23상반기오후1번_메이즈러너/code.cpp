#include <bits/stdc++.h>
using namespace std;
#define INF 98765432
int n,m,k;
int adj[11][11];
int er,ec; //exit
int dy[4] = {-1, 1, 0, 0}; //상하좌우
int dx[4] = {0, 0, -1, 1};
int ret_d=0;


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
		
		cout << "-------" << t << "------\n";
		//cout << npcs.size() <<'\n';
		//1. 참가자들의 움직임
		for(npc& me : npcs){
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
			if(best_d != -1){ //움직임 처리
				me.r += dy[best_d];
				me.c += dx[best_d];
				ret_d++;
			}
			cout << me.r <<","<<me.c <<"\n";
		}

		// 2. 미로의 회전
		/*
		높이나 넓이중 큰 값 기준으로 정사각형 윈도우를 만들어서 갱신
		*/
		// 2.1 가장 작은 정사각형 구하기
		
		tr = INF;
		tc = INF;
		br = INF;
		bc = INF;
		cout << npcs.size() <<'\n';
		int best_ws = INF; //정사각형 크기
		for(int i=0; i<npcs.size(); i++){
			cout <<"test\n";
			int ii = npcs[i].r;
			int jj = npcs[i].c;
			cout << ii <<"," << jj << ": start\n";
			int ws = max(abs(er-ii), abs(ec-jj)) + 1; //윈도우 사이즈
			cout <<"window size : " <<ws<<'\n';
			if(ws > best_ws) continue; //정사각형 크기로 거르기
			best_ws = ws;
			cout <<"window size : " <<ws<<'\n';
			bool exit_checker = false; //최적의 좌상단 나왔으면 true
			for(int r=0; r<n; r++){
				for(int c=0; c<n; c++){ //모든 행과 열을 시작점으로
					bool size_checker = true; //윈도우가 맵 안에 들어가는지
					bool npc_checker = false; //윈도우 안에 npc 있는지
					bool end_checker = false; //윈도우 안에 탈출구 있는지
					for(int rr=0; rr<ws; rr++){
						for(int cc=0; cc<ws; cc++){
							if(c+cc >= n || r+rr >= n){
								size_checker = false;
								
							}
							if(r+rr == ii && c+cc == jj){
								npc_checker = true;
							}
							if(r+rr == er && c+cc == ec){
								end_checker = true;
							}
						}
					}
					if(size_checker == true && npc_checker == true && end_checker == true){
						//이미 좌상단 부터 했기 때문에 최소r,c는 불필요
						if(r > tr) continue;
						if(r == tr && c > tc) continue;
						tr = r; 
						tc = c;
						br = tr + ws-1;
						bc = tc + ws-1;
					}
					if(exit_checker) break;
				}
				if(exit_checker) break;
			}

		}

		cout << tr <<"," << tc <<" ~ " << br <<"," <<bc <<" : best box\n"; 

		//회전 전에 맵에 npc위치 표시
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int idx=0; idx<npcs.size(); idx++){
					if(npcs[idx].r == i && npcs[idx].c == j){
						adj[i][j] = -(idx+1); //npc idx를 음수로 표기
					}
				}
			}
		}

		for(int idx=0; idx<npcs.size(); idx++){
			cout << idx << " : " << npcs[idx].r <<"," <<npcs[idx].c << '\n';
		}
		// 2.2 정사각형의 회전
		//vector<vector<int>> r_map(best_ws);
		int r_map[best_ws][best_ws];
		int r_r=0;
		int r_c=0;
		map<pair<int,int>, pair<int,int>> m;
		for(int i=tr; i<=br; i++){
			r_c = 0;
			for(int j=tc; j<=bc; j++){
				if(adj[i][j] > 0){ //벽
					r_map[r_c][best_ws- r_r -1] = adj[i][j] - 1;
				}
				else if(adj[i][j] <= 0){ //빈 공간 or npc
					if(adj[i][j] < 0){ //npc
						m[{i,j}].first = r_c;
						m[{i,j}].second = best_ws- r_r -1;
					}
					r_map[r_c][best_ws- r_r -1] = adj[i][j] - 1;
				}
				r_c++;
			}
			r_r++;
		}

		// for(int i=tr; i<=br; i++){
		// 	for(int j=tc; j<=bc; j++){
		// 		cout << adj[i][j] <<" ";
		// 	}
		// 	cout <<'\n';
		// }

		// for(int i=0; i<best_ws; i++){
		// 	for(int j=0; j<best_ws; j++){
		// 		cout << r_map[i][j] <<" ";
		// 	}
		// 	cout <<'\n';
		// }

		for(int idx=0; idx<npcs.size(); idx++){
			int rr = npcs[idx].r;
			int cc = npcs[idx].c;
			if(m[{rr,cc}].first >0 && m[{rr,cc}].second > 0){ //딕셔너리에 값있으면
				npcs[idx].r = m[{rr,cc}].first;
				npcs[idx].c = m[{rr,cc}].second; //값 매핑
			}

		}

		for(int i=tr; i<=br; i++){
		 	for(int j=tc; j<=bc; j++){
				if(adj[i][j] < 0){
					adj[i][j] == 0;
				}
			}
		}
	}


	cout << ret_d <<'\n';
	cout << er <<" " <<ec;


	return 0;
}
