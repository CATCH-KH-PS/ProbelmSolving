/*
설명 
- map으로 이름에 index를 부여해 준다. 
- node_parent에 각 index 별로 부모 노드의 index 정보를 기입, 
- node_box[i] 에 i 를 부모 노드로 가지는 놈들을 모두 push_back;

1. 이름 두개가 들어오면 이전에 들어온 것인지 아닌지 확인
2. 들어온 적이 있으면 그것의 부모노드 index를 알아냄
3. 들어온 적이 없으면 새롭게 넣어주고 처음 자기 자신을 부모 노드로 가진다. 
4. 두 부모 노드의 크기를 비교해 작은 것으로 부모노드를 통일 
5. 통일하는 과정 (node_box에서  큰 부모노드를 부모로 가지는 노드들을 작은 부모노드로 이동, node_parent에서도 다 변경)
6. 두 부모노드가 같으면 그냥 그 부모노드를 가지는 node의 갯수를 node_box.size로 반환
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>
#include <map>
using namespace std;
map<string, int> index_map;  //  map에 이름에 index 매칭 
vector<int> node_parent(200001, -1);  // 각 index의 부모 노드들을 지정,  처음에는 자기 자신을 부모 노드로 가짐 
vector<int> node_box[200001];  // index를 부모 노드로 가지는 node들을 push_back;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);  // 이거 차이로 시간초과 났었음 
	int tc;
	cin >> tc;
	while (tc--) { 
		int n;
		index_map.clear();  // 테스트 케이스를 위해 초기화
		cin >> n;
		int index = 0; // 인덱스 매칭 위해 0부터 시작
		for (int i = 0; i < n; i++) {
			int p_ind1, p_ind2;  // 
			string name1, name2;
			cin >> name1 >> name2;  // 두개의 이름을 받고 
			if (index_map.count(name1) != 0) {  // name1에 대하여 이전에 들어온적이 있는데 확인
				int node_number = index_map[name1];  // 들어왔으면 그것의 index를 받고
				p_ind1 = node_parent[node_number];  // 부모 index를 확인
			}
			else if (index_map.count(name1) == 0) { // 들어온적이 없으면 
				index_map[name1] = index;  // 맵에 처음으로 매칭 
				p_ind1 = index;  // 부모 인덱스는 자기 자신
				node_parent[p_ind1] = p_ind1;  // 부모는 자기 자신이라고 표시
				node_box[p_ind1].push_back(p_ind1); // 부모 인덱스에 자기 자신 넣기 
				index += 1;
			}
			if (index_map.count(name2) != 0) {  // name2에 대하여 똑같이 실행
				int node_number = index_map[name2];
				p_ind2 = node_parent[node_number];
			}
			else if (index_map.count(name2) == 0) {
				index_map[name2] = index;
				p_ind2 = index;
				node_parent[p_ind2] = p_ind2;
				node_box[p_ind2].push_back(p_ind2);
				index += 1;
			}

			if (p_ind1 == p_ind2) {  // 둘의 부모가 같으면 그 부모노드를 가지는 node들의  갯수 print
				cout << node_box[p_ind1].size() << '\n';
				continue;
			}
			else if (p_ind1 > p_ind2) {  // 한쪽이 더 크면 
				cout << node_box[p_ind1].size() + node_box[p_ind2].size() << '\n'; // 두 부모노드를 가지는 node의 갯수 print
				int num = node_box[p_ind1].size();  // 두 부모 중 작은 것으로 부모 노드를 합침
				for (int j = 0; j < num; j++) { // 큰것을 부모노드로 가지는 놈들을 작은 부모 노드로 옮기고, 부모노드 정보도 갱신
					int node_num = node_box[p_ind1][j];
					node_parent[node_num] = p_ind2;
					node_box[p_ind2].push_back(node_num);
				}
				node_box[p_ind1].clear();  // 큰 부모였던 것을 빈것으로 
			}
			else if (p_ind1 < p_ind2) {  // 위와 마찬가지로
				cout << node_box[p_ind1].size() + node_box[p_ind2].size() << '\n';
				int num = node_box[p_ind2].size();
				for (int j = 0; j < num; j++) {
					int node_num = node_box[p_ind2][j];
					node_parent[node_num] = p_ind1;
					node_box[p_ind1].push_back(node_num);
				}
				node_box[p_ind2].clear();
			}
		}
		for (int i = 0; i < index; i++) {  // 다음의 위해 초기화하는 과정 
			node_parent[i] = -1;
			node_box[i].clear();
		}
	}
	return 0;
}
