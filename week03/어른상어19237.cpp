/*
그냥 꼼꼼히 구현하는 것이 답인듯한 문제 같습니다. 

변수 
- tmap = 향기정보를 저장하는 맵  <상어번호, 상어가 방문한 시간>
- smap = 상어정보를 저장하는 맵  <상어번호, 방향>
- sxy = 상어의 번호별 좌표 -> 상어 이동시 불필요한 탐색을 줄이기 위한 
- pri = 상어별 우선순위를 저장 3차원으로 하여 [상어 번호][상어 현재방향][그에따른 우선순위방향]

알고리즘 
1. 냄새 정보를 갱신해준다.
- sxy를 통해 현재 상어가 있는 자리에 냄새를 남긴다. 
- 전체 맵을 탐색하면서 냄새가 사라질 시간이 된 곳이 있으면 없애준다. 
2. 상어가 움직인다. 
- 1번 상어부터 움직인다. 
- 죽은 상어는 pass, 조건에 따라 상어 움직이고
- 같은 칸에 마주치면 상어번호로 비교해서 갱신(마주치는 상황 발생시 남은 상어의 수 -=1)
3. 시간 += 1
4. 남은 상어의 수가 1마리 이면 시간을 리턴
5. 위의 과정을 시간이 1000일 때까지 시행
6. 만약 1000을 넘으면 -1 리턴 


*/


#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;

int n, m, ti,time;
int left_s;  // 맵에 남은 상어의 수 
pair<int, int> tmap[21][21];  // 냄새가 남는 맵
vector < vector<pair<int, int>>> smap(21, vector < pair<int, int>>(21)); // 상어의 번호와 방향
pair<int, int> sxy[201]; // 상어 인덱스 별로 좌표
int pri[201][4][4]; // 상어별 우선순위 방향
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

tuple<int, int, int> s_dfind(int x, int y, int num, int dir) { // 이동할 방향 선택, 좌표와 방향 같이 리턴
	vector<tuple<int, int, int>> zero;  // 우선순위별로 확인하면서 빈곳이면 여기에 넣음
	vector<tuple<int, int, int>> nzero;  // 빈곳 아니면 여기에 넣음
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[pri[num][dir][k]]; // 우선순위별로 확인
		int ny = y + dy[pri[num][dir][k]];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (tmap[nx][ny].first == 0) {
			zero.push_back(make_tuple(nx, ny, pri[num][dir][k]));
		}
		else if (tmap[nx][ny].first == num) {
			nzero.push_back(make_tuple(nx, ny, pri[num][dir][k]));
		}
	}

	if (zero.size() != 0) { // 0인 곳이 있으면 바로 리턴
		return zero[0];
	}
	else {
		return nzero[0];
	}
}

void trace() {  // 맵에 상어의 냄새를 남기는 함수
	for (int i = 1; i <= m; i++) { // tmap에는 인덱스와 냄새를 남긴 시간을 기록
		int x, y;
		tie(x, y) = sxy[i];
		if (x == -1) continue; // 죽은 상어는 지나침
		tmap[x][y] = make_pair(i, time);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tmap[i][j].first == 0) continue;
			if (tmap[i][j].second + ti == time) { // 냄새를 남긴 시간 + 기한 == 현재 시간 이면 냄새 사라짐 
				tmap[i][j] = make_pair(0, 0);
			}
		}
	}
}

void s_move() { // 상어가 움직이는 함수 
	vector<vector<pair<int, int>>> smap2(smap); // 새로운 맵
	for (int i = 1; i <= m; i++) {		// 새로운 맵에 상어들 다 없애기 
		int x, y;
		tie(x, y) = sxy[i];
		if (x == -1) continue;
		smap2[x][y] = make_pair(0, 0);
	}
	for (int i = 1; i <= m; i++) {			// 1번 상어부터 확인하면서 이동
		int x, y, nx, ny, num, dir;
		tie(x, y) = sxy[i];
		if (x == -1) continue;
		tie(num, dir) = smap[x][y];
		tie(nx, ny, dir) = s_dfind(x, y, num, dir);
		if (smap2[nx][ny].first == 0) {				// 이동하려는 곳에 먼저 이동한 상어가 없으면
			smap2[nx][ny] = make_pair(num, dir);
			sxy[i] = make_pair(nx, ny);
		}
		else {											// 상어가 있으면 
			left_s -= 1;
			int o_num, o_dir;
			tie(o_num, o_dir) = smap2[nx][ny];			
			if (o_num < num) {							// 원래 있던 상어가 번호가 더 작으면 현재 상어는 죽은 상어로 바꿈
				sxy[num] = make_pair(-1, -1);
				continue;
			}
			else {										// 현재 상어가 더 작으면 원래 있던 상어 죽은 상태로 표시 후, 현재 상어 둠 
				smap2[nx][ny] = make_pair(num, dir);
				sxy[i] = make_pair(nx, ny);
				sxy[o_num] = make_pair(-1, -1);
			}
		}
	}
	smap = smap2;	  // 마지막에 맵을 갱신
}


int solution() {
	time = 0;
	while (time <= 1000) {			// 1000초가 넘어도 1번 상어보다 더 남아 있으면 빠져나가서 -1 리턴 
		trace();
		s_move();
		time += 1;
		if (left_s == 1) return time;		// 남은 상어 1마리이면 시간 리턴 
	}
	return -1;				//
}



int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> m >> ti;
	
	left_s = m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			if (x == 0) {						// 빈칸
				smap[i][j] = make_pair(0, 0);
				tmap[i][j] = make_pair(0, 0);
			}
			else if (x != 0) {					 // 상어 있으면 상어 좌표 갱신 하고 tmap에 상어 번호와 지금 시간인 0 을 넣어준다. 
				tmap[i][j] = make_pair(x, 0);
				sxy[x] = make_pair(i, j);
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		int dir, x, y;
		cin >> dir;
		tie(x, y) = sxy[i];
		smap[x][y] = make_pair(i, dir-1);		// smap에 상어 번호와 방향 갱신
	}
	for (int i = 1; i <= m; i++) {					// 상어별 우선순위 방향 갱신 i = 상어 번호, j = 현재 방향 , u = 우선순위 
		for (int j = 0; j < 4; j++) {
			for (int u = 0; u < 4; u++) {
				int x;
				cin >> x;
				pri[i][j][u] = x - 1;
			}
		}
	}
	
	cout << solution();

	return 0;
}