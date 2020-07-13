#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>
using namespace std;
int n, m;
int d[1001][1001][2];
int a[1001][1001];
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			a[i][j] = s[j] - '0';
		}
	}
	memset(d, -1, sizeof(d));
	queue<tuple<int, int, int>> q;
	d[0][0][0] = 1;
	q.push(make_tuple(0, 0, 0));
	while (!q.empty()) {
		int x, y, z;
		tie(x, y, z) = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (a[nx][ny] == 0) { // 벽이 아닐 경우 
				if (d[nx][ny][z] != -1) continue;
				d[nx][ny][z] = d[x][y][z] + 1;
				q.push(make_tuple(nx, ny, z));
			}
			else { // 벽인 경우 
				if (z == 1) continue; // 한번 벽을 사용했으면 사용 불가
				d[nx][ny][z + 1] = d[x][y][z] + 1;
				q.push(make_tuple(nx, ny, z + 1));
			}
		}
	}
	int ans1 = d[n - 1][m - 1][0];
	int ans2 = d[n - 1][m - 1][1];
	if (ans1 == -1 && ans2 == -1) {
		cout << -1;
	}
	else if (ans1 == -1 && ans2 != -1) {
		cout << ans2;
	}
	else if (ans2 == -1 && ans1 != -1) {
		cout << ans1;
	}
	else {
		cout << min(ans1, ans2);
	}
	return 0;
}
