/* 
설명 
- i와 j가 연결되어 있으면 a[i]에 j를 넣고, a[j]에 i를 넣는다.
- 1부터 시작에서 dfs로 연결된 모든 곳들을 확인 
- d로 확인 여부 check
- 마지막에 d에 true인 것의 갯수 셈 (1번 노드는 제외)
*/


#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <cstring>

using namespace std;
int n, m;
vector<int> a[101];
bool d[101];

void dfs(int x) {

	for (int i = 0; i < a[x].size(); i++) {
		int y = a[x][i];
		if (d[y]) continue;
		d[y] = true;
		dfs(y);

	}
			
}

int main() {
	cin >> n >> m;
	memset(d, false, sizeof(d));
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	d[1] = true;
	dfs(1);
	int ans = 0;
	for (int i = 2; i <= n; i++) {
		if (d[i]) ans += 1;
	}
	cout << ans;
	return 0;
}