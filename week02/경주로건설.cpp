/*
- dfs 시에 시간초과
- 초기 아이디어 : 우선순위 큐에 price를 기준으로 하여 bfs 진행(이유 : 가격을 거리로 작은 가격부터 차례차례 움직여야 한다고 생각함 그러나 메모리 초과가 남
- 인터넷 해설 참조.....

설명 
- car 라는 객체를 설정하여 좌표, 지금까지의 가격, 이전에 온 방향 정보를 넣어줌
- 방문 안한 곳은 바로 방문 
- 방문 한 곳이면 가격을 비교하여 작거나 같으면 방문 

*/

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <cstring>

using namespace std;

int n;
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
struct car{   // 차 정보, 
    int x;
    int y;
    int price;
    int dir;   
    car(int _x, int _y, int _price, int _dir) : x(_x), y(_y), price(_price), dir(_dir) {};
};
int d[25][25];  // 거리 정보

int solution(vector<vector<int>> board) {
    memset(d, -1, sizeof(d));
    n = board.size();
    queue<car> q;
    car start(0, 0, 0, -1); // 처음 시작 -1로 어느 방향이든 직선으로 판단할 수 잇도록 
    q.push(start);
    d[0][0] = 0;
    int answer = 0;

    while (!q.empty()) {
        car temp = q.front();
        q.pop();
        int x = temp.x;
        int y = temp.y;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;  // 범위
            if (board[nx][ny] == 1) continue;  // 벽
            int nprice;
            if (k == temp.dir || temp.dir == -1) {  // 직선도로이면 +1 
                nprice = temp.price + 1;
            }
            else {
                nprice = temp.price + 6;  // 커브이면 + 6   
            }            
            car temp(nx, ny, nprice, k);
            if (d[nx][ny] == -1) {  // 방문 안한 곳이면 바로 방문 
                d[nx][ny] = nprice;
                q.push(temp);
            }
            else if (d[nx][ny] != -1 && d[nx][ny] >= nprice) {   // 방문 한 곳이면 현재 가격이 작거나 같으면 방문 
                d[nx][ny] = nprice;
                q.push(temp);
            }
            //  여기서 만약 x1 -> x2 -> x3를 방문한다면 x2 일 때 x1을 방문 할지도 모른다는 생각 가졌지만, d[x1]이 당연히 d[x2] 보다 작을 것이기 때문에 방문 x 
        }
    }

    answer = d[n - 1][n - 1];

    return answer * 100;  // 마지막 가격에 * 100;
}