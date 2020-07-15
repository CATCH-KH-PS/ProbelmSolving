#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool visited[101];
bool graph[101][101];
int computers;
int ans = 0;

void dfs(int N){
	for(int i = 1 ; i <= computers ; i++){
		if(graph[N][i] == true && visited[i] == false){
			visited[i] = true;
			ans++;
			dfs(i);
		}
	}
}

int main(void){
	int size;
	cin>>computers>>size;
	for(int i = 0 ; i < size ; i++){
		int row,col;
		cin>>row>>col;
		graph[row][col] = true;
		graph[col][row] = true;
	}
	dfs(1);
	cout<<ans -1<<endl;
}
