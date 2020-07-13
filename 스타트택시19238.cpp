/*
설명

1. 출발지와 도착지 정보를 승객 인덱스에 따라 분류 
2. map에는 빈칸 : 0 , 벽 : -1, 승객의 출발지 : 승객 index
3. visit에 각 승객을 처리햇는지 체크

알고리즘 

1. 가장 가까운 승객을 bfs 로 찾는다. 
2. 승객을 찾으면 그 위치를 반환, 못찾으면 -1을 반환 
3. 승객까지의 거리가 현재 가지고 있는 연료보다 크면 -1 리턴 

4. 그 위치로 택시 이동 
5. 그 위치에서 도착지까지 bfs로 이동, 도착하고 연료보다 거리가 짧으면 도착지로 택시 이동
6. 도착 못하거나 거리가 더 멀면 -1 리턴 
7. 다시 1번으로 

8. 승객을 m 명만큼 성공적으로 수행할때까지  수행못하면 -1 리턴 


틀린 이유 : 승객을 찾는 과정에서 처리한 다른 승객이 있는 경우 그냥 빈칸처럼 해야하지만
그냥 넘어가도록 설정하여 계속 틀림 , 수정 후 정답
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
int dx[] = { 0, 0, 1, -1};
int dy[] = { 1, -1, 0, 0 };
pair<int, int> st[401]; // 승객 출발지 정보
pair<int, int> de[401]; // 승객 도착지 정보
int tx, ty, fuel; // 택시 정보
int map[20][20];  // map
int d[20][20];  // bfs 돌때 방문 여부, 거리 정보
bool visit[401];  // 승객 처리 유무 정보 

bool compare(pair<int, int> a, pair<int, int> b) { // 거리가 같은 승객들의 우선순위 
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}


pair<int, int> find_c() {  // 가장 가까운 승객을 찾는 함수 
	queue<pair<int, int>> q;  
	vector<pair<int, int>> temp;   // 거리가 가장 가까운 승객들의 정보를 입력
	memset(d, -1, sizeof(d));
	int distance = -1;  // 가장 가까운 승객의 거리 
	if (map[tx][ty] != 0 && !visit[map[tx][ty]]) return make_pair(tx, ty);  // 현재 위치에 승객이 있고, 그 승객이 아직 처리가 안됐으면 바로 승객 위치 리턴

	q.push(make_pair(tx, ty));
	d[tx][ty] = 0;

	while (!q.empty()) {
		int x, y;
		tie(x, y) = q.front();
		q.pop();
		if (distance == d[x][y]) break;  // 승객의 거리가 최소 인 점들을 다 돌았으면 bfs 나오기 
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;  // 범위 
			if (map[nx][ny] == -1) continue;  // 벽이면 x
			if (d[nx][ny] != -1) continue;   // 방문했으면 x
			if (map[nx][ny] == 0 ) {  //  빈칸이면 그냥 넣기 
				q.push(make_pair(nx, ny));
				d[nx][ny] = d[x][y] + 1;
				continue;
			}
			if (visit[map[nx][ny]]) {  // 이거때문에 계속 틀림   처리된 승객이 있는 칸이면 그냥 큐에 넣기 
				q.push(make_pair(nx, ny));
				d[nx][ny] = d[x][y] + 1;
			}
			else {  // 승객이면 거리가 가장 가까운 승객 정보에 넣기 
				temp.push_back(make_pair(nx, ny));
				d[nx][ny] = d[x][y] + 1;
				distance = d[nx][ny];
			}
		}
	}
	if (temp.size() == 0) return make_pair(-1, -1);  // 승객이 없으면 -1 리턴  
	sort(temp.begin(), temp.end(), compare);  // 우선순위 선정
	fuel -= distance;  // 거리만큼 연료 소모
	if (fuel < 0) return make_pair(-1, -1);  // 연료가 부족하면 -1 리턴
	
	return temp[0];
}

pair<int, int> t_move(int num) {  // 택시가 승객을 수송하는 함수 
	memset(d, -1, sizeof(d));
	d[tx][ty] = 0;
	queue<pair<int, int>> q;
	q.push(make_pair(tx, ty));
	int sx, sy, ex, ey;  // 승객의 출발 도착 정보
	tie(sx, sy) = st[num];
	tie(ex, ey) = de[num];
	if (tx == ex && ty == ey) return make_pair(ex, ey);  // 출발점이 도착지이면 바로 리턴
	int distance = - 1;
	while (!q.empty()) {
		int x, y;
		tie(x, y) = q.front();
		q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (map[nx][ny] == -1) continue;
			if (d[nx][ny] != -1) continue;
			if (nx == ex && ny == ey) {  // 도착을 하면 종료 
				distance = d[x][y] + 1;
				break;
			}
			q.push(make_pair(nx, ny));
			d[nx][ny] = d[x][y] + 1;
		}
		if (distance != -1) break;  // 도착을 하면 종료
	}
	if (distance == -1) return make_pair(-1, -1);  // 도착을 못하면 -1 리턴 
	if (distance > fuel) return make_pair(-1, -1);  // 거리가 출발당시 연료보다 크면 -1 리턴
	fuel += distance;  // 충전
	return make_pair(ex, ey);  // 도착지 정보 리턴
}

bool solution() {
	int cnt = 0;

	while (cnt != m) {
		tie(tx, ty) = find_c();  // 승객 정보 찾고 
		if (tx == -1 || ty == -1) return false;  // -1이면 운행실패
		int num = map[tx][ty];
		tie(tx, ty) = t_move(num);  // 승객 운송
		if (tx == -1 || ty == -1) return false;  // -1이면 운행 실패
		visit[num] = true;  // 운행 성공했으면 승객 처리 
		cnt += 1;
	}

	return true;
}




int main() {
	cin >> n >> m >> fuel;
	memset(visit, false, sizeof(visit));
	memset(d, -1, sizeof(d));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) map[i][j] = -1;  // 벽은 -1로 
		}
	}
	cin >> tx >> ty;
	tx -= 1;
	ty -= 1;
	for (int i = 1; i <= m; i++) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		st[i] = make_pair(x1-1, y1-1);
		de[i] = make_pair(x2-1, y2-1);
		map[x1-1][y1-1] = i;  // 승객 출발지에 승객 index 입력 
	}
	if (solution()) cout << fuel;
	else cout << -1;

	return 0;
}

