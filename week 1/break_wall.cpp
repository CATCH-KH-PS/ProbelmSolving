#include <cstdio>
#include <queue>
using namespace std;
const int MAX = 1010;
int map[MAX][MAX];
int cost1[MAX][MAX], cost2[MAX][MAX];
bool visited1[MAX][MAX], visited2[MAX][MAX];
int n, m;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int main() {
	char buf[1010];
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		for (int j = 0; j < m; j++) {
			map[i][j + 1] = buf[j] - '0';
		}
	}
	//1,1에서 BFS
	queue<pair<int, int>> Q1;
	Q1.push(make_pair(1, 1));
	cost1[1][1] = 1;
	visited1[1][1] = true;
	while (!Q1.empty()) {
		int now_x = Q1.front().first;
		int now_y = Q1.front().second;
		int now_c = cost1[now_x][now_y];
		Q1.pop();
		for (int i = 0; i < 4; i++) {
			int next_x = now_x + dx[i];
			int next_y = now_y + dy[i];
			int next_c = now_c + 1;
			if (next_x < 1 || next_x > n || next_y < 1 || next_y > m) { continue; }
			if (visited1[next_x][next_y]) { continue; }
			visited1[next_x][next_y] = true;
			cost1[next_x][next_y] = next_c;
			if (map[next_x][next_y] == 0) Q1.push(make_pair(next_x, next_y));
		}
	}
	//n,m에서 BFS
	queue < pair<int, int>> Q2;
	Q2.push(make_pair(n, m));
	cost2[n][m] = 1;
	visited2[n][m] = true;
	while (!Q2.empty()) {
		int now_x = Q2.front().first;
		int now_y = Q2.front().second;
		int now_c = cost2[now_x][now_y];
		Q2.pop();
		for (int i = 0; i < 4; i++) {
			int next_x = now_x + dx[i];
			int next_y = now_y + dy[i];
			int next_c = now_c + 1;
			if (next_x < 1 || next_x > n || next_y < 1 || next_y > m) { continue; }
			if (visited2[next_x][next_y]) { continue; }
			visited2[next_x][next_y] = true;
			cost2[next_x][next_y] = next_c;
			if (map[next_x][next_y] == 0) Q2.push(make_pair(next_x, next_y));
		}
	}
	bool flag = false;
	int min = 987654321;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (visited1[i][j] && visited2[i][j]) {
				flag = true;
				if (min > cost1[i][j] + cost2[i][j] - 1) {
					min = cost1[i][j] + cost2[i][j] - 1;
				}
			}
		}
	}
	if (flag) printf("%d", min);
	else printf("-1");
	return 0;
}