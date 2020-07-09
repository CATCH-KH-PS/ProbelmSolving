#include <string>
#include <vector>
#include <memory.h>
#include <queue>
#include <iostream>
using namespace std;

int dx[] = {1, 1, 0};
int dy[] = {0, 1, 1};

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    
    int check[30][30] = {{0}};
    int next_flag = 0; // 계속 진행할것인가?
    while (1)
    {
        memset(check,0 ,sizeof(check));
        next_flag = 0;
        
        for(int i = 0 ; i < board.size(); i++)
        {
            for(int j = 0 ; j < board[i].size(); j++)
            {
                char name = board[i][j];
                if (name == 0) // 빈공간이면 지나침
                    continue;
                bool boom_flag = 1; // 터짐이 존재하는지 flag
                for(int k = 0; k < 3; k++) // 우, 우하, 하 검사
                {
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                    if (ny >=0 && ny < m && nx >=  0 && nx < n)
                    {
                        if (board[ny][nx] != name) // 만약 인형이 다르면 loop탈출
                        {
                            boom_flag = 0;
                            break;
                        }
                    }
                    else // 범위벗어나면 loop 탈출
                    {
                           boom_flag = 0;
                            break;
                    }
                        
                }
                if (boom_flag) // 만약 2x2 이상 인형이 터졌으면
                {
                    next_flag = 1; // 다음루프 활성화
                    if (check[i][j] == 0) // 터진개수 ++(base위치)
                            answer++;
                    check[i][j] = 1; //  터진위치 체크
                         for(int k = 0; k < 3; k++)
                    {
                        int ny = i + dy[k];
                        int nx = j + dx[k];
                        if (ny >=0 && ny < m && nx >=  0 && nx < n)
                        {
                            if (check[ny][nx] == 0) // 터진개수 ++(우, 우하, 하 위치)
                                answer++;
                           check[ny][nx] = 1; // 터진위치 체크
                        }
                    }
                }
            }
        }
               
    for(int i = 0 ; i < board.size(); i++)
        {
            for(int j = 0 ; j <board[i].size();j++)
            {
               
                if(check[i][j] == 1) // 체크된곳 터뜨리기(빈곳으로 만듬)
                    board[i][j] = 0;
            }
          
        }  
         // 내리기
        
        for (int x = 0; x < board[0].size(); x++)
        {
            for(int y = board.size()-1; y >= 0 ; y--)
            {
                if (board[y][x] == 0)
                {
                    for(int ny = y - 1 ; ny >= 0; ny--) 
                    {
                        if (board[ny][x] != 0)
                        {
                            board[y][x] = board[ny][x];
                            board[ny][x] = 0;
                            break;
                        }
                    }
                }
            }
        }
        if (!next_flag) // 루프플래그 비활성화시 탈출
            break;
    }
    return answer;
}
