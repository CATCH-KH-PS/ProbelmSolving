#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;



string to_str(vector<int> N){
	string str;
	for(int i = 0 ; i < N.size() ; i++){
		if(N[i] < 10) str.push_back(N[i] + '0');
		else str.push_back('A' + N[i]-10); 
	}
	return str;
}

string getN(int num,int n){
	vector<int> N;
	if(num == 0) return "0";
	while(num != 0){
		N.push_back(num % n);
		num /= n;
	}
	reverse(N.begin(),N.end());
	return to_str(N);
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    string str = "";
    int num = 0;
    while(str.length() <= t*m){
	//	cout<<num<<" "<<getN(num,n)<<endl;
		str+=getN(num,n);
		num++;
	}
	for(int i = 0 ; i < t ; i++){
		answer.push_back(str[i*m+p-1]);
	}
    return answer;
}

int main(void){
	cout<<solution(2,4,2,1)<<endl;
}

