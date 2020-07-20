#include <cstdio>

int map[30][30];		//상어들
int shark_x[410];			//상어정보
int shark_y[410];
int shark_d[410];
int trans_dir[410][5][5];	//방향 우선순위
bool shark_gone[410];

int whose[30][30];			//냄새 정보
int remain[30][30];
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int n, m, k, shark_cnt;

void input() {
	scanf("%d %d %d", &n, &m, &k);
	shark_cnt = m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);

			if (map[i][j] > 0) {
				shark_x[map[i][j]] = i;
				shark_y[map[i][j]] = j;
			}
		}
	}for (int i = 1; i <= m; i++) scanf("%d", &shark_d[i]);
	for (int idx = 1; idx <= m; idx++) {
		for (int j = 1; j <= 4; j++)
			scanf("%d %d %d %d", &trans_dir[idx][j][1], &trans_dir[idx][j][2], &trans_dir[idx][j][3], &trans_dir[idx][j][4]);
	}
}

void decrease_smell() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (remain[i][j] > 0) { remain[i][j]--; }
			if (remain[i][j] == 0) { whose[i][j] = 0; }
		}
	}
}

void leave_smell() {
	for (int i = 1; i <= m; i++) {
		if (!shark_gone[i]) {
			whose[shark_x[i]][shark_y[i]] = i;
			remain[shark_x[i]][shark_y[i]] = k;
		}
	}
}

int find_dir(int idx) {
	int now_x = shark_x[idx];
	int now_y = shark_y[idx];
	int now_d = shark_d[idx];

	bool find_flag = false;
	int next_dir;
	//빈칸 찾자
	for (int d = 1; d <= 4; d++) {
		int next_x = now_x + dx[trans_dir[idx][now_d][d]];
		int next_y = now_y + dy[trans_dir[idx][now_d][d]];

		if (next_x < 0 || next_y < 0 || next_x > n - 1 || next_y > n - 1) continue;
		if (remain[next_x][next_y] > 0) continue;

		return trans_dir[idx][now_d][d];
	}

	//내 냄새로 이동
	for (int d = 1; d <= 4; d++) {
		int next_x = now_x + dx[trans_dir[idx][now_d][d]];
		int next_y = now_y + dy[trans_dir[idx][now_d][d]];

		if (next_x < 0 || next_y < 0 || next_x > n - 1 || next_y > n - 1) continue;
		if (whose[next_x][next_y] != idx) continue;

		return trans_dir[idx][now_d][d];
	}
}

void move(int idx) {
	if (shark_gone[idx]) return;
	int nx = shark_x[idx];
	int ny = shark_y[idx];

	int next_d = find_dir(idx);
	int next_x = nx + dx[next_d];
	int next_y = ny + dy[next_d];

	shark_x[idx] = next_x;
	shark_y[idx] = next_y;
	shark_d[idx] = next_d;

	if (map[next_x][next_y] != 0) {
		int rm_idx = map[next_x][next_y];
		shark_gone[rm_idx] = true;
		shark_cnt--;
	}
	map[next_x][next_y] = idx;
	map[nx][ny] = 0;
}

int main() {
	//1. 입력받자마자 현재위치에서 냄새풍기기
	//
	//2 .그리고 m번부터 1번상어 순차적으로 이동
	//	-> 역순: 작은번호 상어가 큰 상어 덮어쓸 수 있음
	//	-> 이동하자마자 냄새풍기면 안됨 (동시이동이므로)
	//
	//3. 모든 상어 이동 끝났으면 지도상 모든 냄새 1감소
	//4. 그리고 현재 상어의 위치에 새로운 냄새 추가

	input();
	leave_smell();

	int time = 0;
	while (time <= 1000 && shark_cnt > 1) {

		for (int i = m; i >= 1; i--) { move(i); }
		decrease_smell();
		leave_smell();
		time++;
	}

	if (time > 1000) printf("-1");
	else printf("%d", time);
	return 0;
}
