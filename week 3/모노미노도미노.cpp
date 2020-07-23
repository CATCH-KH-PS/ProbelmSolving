#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stdlib.h>
int map[15][15];
int n;

int cnt = 1;

int green_area(int blockType, int y) {
	//놓을 수 있는 행의 인덱스 반환
	int ret = 4;

	if (blockType == 1) {
		while (ret < 9) {
			if (map[ret + 1][y] == 0) ret++;
			else return ret;
		}return ret;
	}

	if (blockType == 2) {
		while (ret < 9) {
			if (map[ret + 1][y] == 0 && map[ret + 1][y + 1] == 0) ret++;
			else return ret;
		}return ret;
	}

	if (blockType == 3) {
		while (ret < 8) {
			if (map[ret + 1][y] == 0 && map[ret + 2][y] == 0) ret++;
			else return ret;
		}return ret;
	}
}

int blue_area(int blockType, int x) {
	//놓을 수 있는 열의 인덱스 반환
	int ret = 4;

	if (blockType == 1) {
		while (ret < 9) {
			if (map[x][ret + 1] == 0) ret++;
			else return ret;
		}return ret;
	}

	if (blockType == 2) {
		while (ret < 8) {
			if (map[x][ret + 1] == 0 && map[x][ret + 2] == 0) ret++;
			else return ret;
		}return ret;

	}

	if (blockType == 3) {
		while (ret < 9) {
			if (map[x][ret + 1] == 0 && map[x + 1][ret + 1] == 0) ret++;
			else return ret;
		}return ret;
	}
}

//t == 1
void put1x1(int x, int y) {
	int gidx = green_area(1, y); //행
	int bidx = blue_area(1, x);  //열

	map[gidx][y] = cnt;

	map[x][bidx] = cnt;
}

//t == 2
void put1x2(int x, int y) { //넓쭉이
	int gidx = green_area(2, y);
	int bidx = blue_area(2, x);

	map[gidx][y] = cnt;
	map[gidx][y + 1] = cnt;

	map[x][bidx] = cnt;
	map[x][bidx + 1] = cnt;
}

//t == 3
void put2x1(int x, int y) { //길쭉이
	int gidx = green_area(3, y);
	int bidx = blue_area(3, x);

	map[gidx][y] = cnt;
	map[gidx + 1][y] = cnt;

	map[x][bidx] = cnt;
	map[x + 1][bidx] = cnt;
}

int check_green() {
	for (int i = 9; i >= 4; i--) {
		if (map[i][0] != 0 && map[i][1] != 0 &&
			map[i][2] != 0 && map[i][3] != 0) {
			return i;
		}
	}return 0;
}

int check_blue() {
	for (int i = 9; i >= 4; i--) {
		if (map[0][i] != 0 && map[1][i] != 0 &&
			map[2][i] != 0 && map[3][i] != 0) {
			return i;
		}
	}return 0;
}

void rm_green(int idx) {
	for (int col = 0; col < 4; col++) {
		for (int i = idx; i >= 3; i--) {
			map[i][col] = map[i - 1][col];
		}
	}
}

void rm_blue(int idx) {
	for (int row = 0; row < 4; row++) {
		for (int i = idx; i >= 3; i--) {
			map[row][i] = map[row][i - 1];
		}
	}
}

int main() {
	scanf("%d", &n);

	int t, x, y;
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &t, &x, &y);
		if (t == 1) put1x1(x, y);
		if (t == 2) put1x2(x, y);
		if (t == 3) put2x1(x, y);
		cnt++;

		while (true) {
			int idx = check_green();
			if (idx == 0) {
				bool flag = true;
				if (map[5][0] != 0 || map[5][1] != 0 || map[5][2] != 0 || map[5][3] != 0) { rm_green(9); flag = false; }
				//if (map[4][0] != 0 || map[4][1] != 0 || map[4][2] != 0 || map[4][3] != 0) { rm_green(1); flag = false; }
				if (flag) break;
			}
			else rm_green(idx);
		}

		while (true) {
			int idx = check_blue();
			if (idx == 0) {
				bool flag = true;
				if (map[0][5] != 0 || map[1][5] != 0 || map[2][5] != 0 || map[3][5] != 0) { rm_blue(9); flag = false; }
				//if (map[0][4] != 0 || map[1][4] != 0 || map[2][4] != 0 || map[3][4] != 0) { rm_blue(1); flag = false; }
				if (flag) break;
			}
			else rm_blue(idx);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i > 3 && j > 3) continue;
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}
