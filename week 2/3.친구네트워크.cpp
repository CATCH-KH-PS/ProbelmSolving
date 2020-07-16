#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <string>
#include <stdlib.h>
using namespace std;

int t, n, f;
int parent[200000];
int cntChildren[200000];
char str1[21], str2[21];

int getParent(int a) {
	if (parent[a] == a) return a;
	else return parent[a] = getParent(parent[a]);
}

void unionParent(int a, int b) {
	a = getParent(a);
	b = getParent(b);

	if (a < b) {
		parent[b] = a;

		cntChildren[a] += cntChildren[b];
		cntChildren[b] = 1;
		//딸린 자식들 내 아래로 합치기
	}
	else if (a > b) {
		//걍 else로 하면, 원래 친구였던 애들이 들어왔을 때
		//즉 같은 부모를 가리키게 된다면, else문 내부가 실행되면서
		//cntchildren 값을 1로 바꿔버리게 된다 .
		parent[a] = b;

		cntChildren[b] += cntChildren[a];
		cntChildren[a] = 1;
		//딸린 자식들 내 아래로 합치기
	}
}


int main() {
	scanf("%d", &t);
	for (int T = 0; T < t; T++) {
		scanf("%d", &f);
		for (int i = 0; i < f * 2; i++) {
			parent[i] = i;
			cntChildren[i] = 1;
		}

		int order = 0;
		map<string, int> m;

		for (int i = 0; i < f; i++) {
			scanf("%s %s", str1, str2);
			if (m.count(str1) == 0) { m[str1] = order++; }
			if (m.count(str2) == 0) { m[str2] = order++; }

			unionParent(m[str1], m[str2]);
			//얘가 궁금한거는 지금 입력된 노드들의. 부모??의 자식의 수
			// str1의 cnt값이 str2보다 작을 것이므로, 친구네트워크가 2명뿐이라도
			// str1의 자식 수가 증가하게된다.
			printf("%d\n", cntChildren[getParent(m[str1])]);
		}
	}
	//system("pause");

	return 0;
}
