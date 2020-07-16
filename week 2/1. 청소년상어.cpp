#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct info {
	int x;
	int y;
	int d;
	bool eaten;
};
int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };
vector<int> answer;

bool isValid(int nx, int ny, int nd, int sx, int sy) {
	int next_x = nx + dx[nd];
	int next_y = ny + dy[nd];

	if (next_x < 0 || next_x > 3 || next_y < 0 || next_y > 3) return false;
	if (next_x == sx && next_y == sy) return false;

	return true;
}

void move_fish(int map[][4], info fish[], int shark_x, int shark_y, int idx) {
	int now_x = fish[idx].x;
	int now_y = fish[idx].y;
	int now_d = fish[idx].d;
	if (now_x == shark_x && now_y == shark_y) return;
	if (fish[idx].eaten) return;

	while (!isValid(now_x, now_y, now_d, shark_x, shark_y)) {
		now_d++;
		if (now_d > 8) now_d = 1;
	}fish[idx].d = now_d;

	//swap
	int target_x = now_x + dx[now_d];
	int target_y = now_y + dy[now_d];
	int target = map[target_x][target_y];

	map[now_x][now_y] = target;
	map[target_x][target_y] = idx;
	fish[target].x = now_x;
	fish[target].y = now_y;
	fish[idx].x = target_x;
	fish[idx].y = target_y;
}

vector<pair<int, int>> togo(int map[][4], info fish[], int sx, int sy) {
	vector<pair<int, int>> ret;
	int sidx = map[sx][sy];
	int sd = fish[sidx].d;

	for (int i = 1; i < 4; i++) {
		int nsx = sx + (dx[sd] * i);
		int nsy = sy + (dy[sd] * i);

		if (nsx < 0 || nsx > 3 || nsy < 0 || nsy > 3) continue;
		if (map[nsx][nsy] == 0) continue;
		ret.push_back(make_pair(nsx, nsy));
	}
	return ret;
}

void recursion(int tmap[][4], info tfish[], int shark_x, int shark_y, int score) {
	int map[4][4];
	info fish[17];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			map[i][j] = tmap[i][j];
	}for (int i = 1; i <= 16; i++) fish[i] = tfish[i];
	fish[map[shark_x][shark_y]].eaten = true;

	//물고기 이동
	for (int i = 1; i <= 16; i++) move_fish(map, fish, shark_x, shark_y, i);

	//상어 이동 가능한 후보 좌표 벡터로 반환하는 함수 작성
	vector<pair<int, int>> candidate = togo(map, fish, shark_x, shark_y);

	score += map[shark_x][shark_y];
	map[shark_x][shark_y] = 0;

	if (candidate.size() == 0) answer.push_back(score); //벡터가 비어있으면 answer에 score 추가
	else {												//else 벡터 순회하면서 상어좌표 바꿔가면서 recursion 호출 
		for (int i = 0; i < candidate.size(); i++) {
			recursion(map, fish, candidate[i].first, candidate[i].second, score);
		}
	}
}

int main() {
	int map[4][4] = { 0, };
	info fish[17] = { 0, };
	int tmp;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			scanf("%d %d", &map[x][y], &tmp);
			fish[map[x][y]].x = x;
			fish[map[x][y]].y = y;
			fish[map[x][y]].d = tmp;
		}
	}

	recursion(map, fish, 0, 0, 0);

	sort(answer.begin(), answer.end());
	printf("%d", answer[answer.size() - 1]);
	return 0;
}

