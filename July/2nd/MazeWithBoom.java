import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;

public class MazeWithBoom {

    //c++전환시 Place 구조체로 구현
    static class Place {
        int x;
        int y;
        int distance;
        int boom; //벽 부신 횟수

        public Place(int x, int y, int distance, int boom) {
            this.x = x;
            this.y = y;
            this.distance = distance;
            this.boom = boom;
        }
    }

    //bfs 기본요소
    static int N, M, answer;
    static int[][] map, visit;
    static int[] dx = {0,0,-1,1};
    static int[] dy = {-1,1,0,0};

    public static void main(String[] args) throws Exception{

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        String[] string = br.readLine().split(" ");

        N = Integer.parseInt(string[0]); //행
        M = Integer.parseInt(string[1]); //열

        map = new int[N][M]; //초기화
        visit = new int[N][M]; //초기화

        for(int i=0; i < N; i++){
            string = br.readLine().split("");
            for (int j = 0; j < M; j++){
                map[i][j] = Integer.parseInt(string[j]);
                visit[i][j] = Integer.MAX_VALUE;
            }
        }

        answer = Integer.MAX_VALUE;

        bfs(0,0);

        if (answer == Integer.MAX_VALUE) {
            System.out.println(-1);
        }
        else {
            System.out.println(answer);
        }
    }

    public static void bfs(int x, int y){
        Queue<Place> queue = new LinkedList<>();

        queue.add(new Place(x, y, 1, 0));
        visit[y][x] = 0 ;//처음 벽 부신 횟수

        while(!queue.isEmpty()){

            Place place = queue.poll();

            //목적지 끝과 좌표가 같을 때 종료
            if(place.y == N-1 && place.x==M-1){
                answer = place.distance;
                break;
            }

        for (int i = 0; i < 4; i++)  {
            int nx = place.x + dx[i];
            int ny = place.y + dy[i];

            if (ny<0 || nx<0 || ny>=N || nx>=M) continue;

            if (visit[ny][nx] <= place.boom) continue;

            if(map[ny][nx] == 0){
                visit[ny][nx] = place.boom;
                queue.add(new Place(nx, ny, place.distance+1, place.boom));
            }
            else {
                if(place.boom == 0){
                    visit[ny][nx] = place.boom +1;
                    queue.add(new Place(nx, ny, place.distance+1, place.boom+1));
                }
            }
        }
        }
    }

}