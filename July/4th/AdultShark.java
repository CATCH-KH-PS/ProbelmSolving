import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class AdultShark {

    static class Pair {
        int x;
        int y;

        public Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static class Information {
        int sharkNumber;
        int time; // 남은 시간

        public Information(int sharkNumber, int time) {
            this.sharkNumber = sharkNumber;
            this.time = time;
        }
    }

    static class Shark {
        int x;
        int y;
        int direction;
        int[][] priority;

        public Shark(int x, int y) {
            this.x = x;
            this.y = y;
        }

    }

    static int N, M, k;
    static int[][] dir = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 제자리, 위, 아래, 왼쪽, 오른쪽
    static Shark[] sharks;
    static Information[][] map;
    static ArrayList<Pair> list = new ArrayList();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");

        N = Integer.parseInt(st.nextToken()); // 격자 크기
        M = Integer.parseInt(st.nextToken()); // 상어 수
        k = Integer.parseInt(st.nextToken()); // 냄새 유효시간

        map = new Information[N + 1][N + 1];
        sharks = new Shark[M + 1];

        for (int i = 1; i <= N; i++) {
            st = new StringTokenizer(br.readLine(), " ");
            for (int j = 1; j <= N; j++) {
                int value = Integer.parseInt(st.nextToken());
                if (value != 0) {
                    sharks[value] = new Shark(i, j);
                }
            }
        }

        st = new StringTokenizer(br.readLine(), " ");
        for (int i = 1; i <= M; i++) {
            sharks[i].direction = Integer.parseInt(st.nextToken());
        }

        for (int i = 1; i <= M; i++) {
            int[][] priority = new int[5][5];
            for (int j = 1; j <= 4; j++) {
                st = new StringTokenizer(br.readLine(), " ");

                for (int k = 1; k <= 4; k++)
                    priority[j][k] = Integer.parseInt(st.nextToken());
            }
            sharks[i].priority = priority;
        }

        int timestamp = 0;

        while (timestamp <= 1000) {

            timestamp++;

            // 1) 현재 상어 위치에 냄새 남기고 좌표 list에 넣기
            for (int i = 1; i <= M; i++) {
                if (sharks[i] == null)
                    continue;

                Shark shark = sharks[i];

                map[shark.x][shark.y] = new Information(i, k);
                list.add(new Pair(shark.x, shark.y));
            }

            //2) 상어 이동 시키기
            for (int i = 1; i <= M; i++) {

                if (sharks[i] == null)
                    continue;

                Shark shark = sharks[i];

                int newX = 0, newY = 0, newDirection = 0;
                boolean flag = false;

                for (int j = 1; j <= 4; j++) {
                    newX = shark.x + dir[shark.priority[shark.direction][j]][0];
                    newY = shark.y + dir[shark.priority[shark.direction][j]][1];

                    if (isInside(newX, newY) && map[newX][newY] == null) {
                        flag = true;
                        newDirection = shark.priority[shark.direction][j];
                        break;
                    }
                }

                if (flag) { // 상어가 빈칸으로 이동 가능함
                    sharks[i].x = newX;
                    sharks[i].y = newY;
                    sharks[i].direction = newDirection;
                } else { // 상어가 이동할 수 있는 칸이 없다면 -> 자신의 냄새가 있는 칸으로 방향을 잡는다.
                    for (int j = 1; j <= 4; j++) {
                        newX = shark.x + dir[shark.priority[shark.direction][j]][0];
                        newY = shark.y + dir[shark.priority[shark.direction][j]][1];

                        if (isInside(newX, newY) && map[newX][newY].sharkNumber == i) {
                            sharks[i].x = newX;
                            sharks[i].y = newY;
                            sharks[i].direction = shark.priority[shark.direction][j];
                            for (int k = 0; k < list.size(); k++) {
                                if (list.get(k).x == newX && list.get(k).y == newY) {
                                    list.remove(k);
                                }
                            }
                            break;
                        }
                    }
                }
            }

            //2) 전에 남겼던 냄새 1초씩 깎기
            for (int j = 0; j < list.size(); j++) {
                Pair pair = list.get(j);
                if (map[pair.x][pair.y].time - 1 == 0) {
                    map[pair.x][pair.y] = null;
                    list.remove(j);
                    j--;
                } else {
                    map[pair.x][pair.y].time--;
                }
            }

            //3) 한 칸에 여러 마리의 상어가 남아 있으면, 가장 작은 번호를 가진 상어를 제외하고 격자 밖으로 쫓아낸다.
            int[][] visited = new int[N + 1][N + 1];

            for (int i = 1; i <= M; i++) {
                if (sharks[i] == null)
                    continue;
                Shark shark = sharks[i];
                if (visited[shark.x][shark.y] == 0) {
                    visited[shark.x][shark.y] = i;
                } else {
                    sharks[i] = null;
                }
            }

            //4) 1번 상어만 살아있는지 검사
            boolean outFlag = true;
            for (int i = 2; i <= M; i++) {
                if (sharks[i] != null) {
                    outFlag = false;
                }
            }

            if (outFlag)
                break;

        }

        if (timestamp == 1001)
            System.out.println(-1);
        else
            System.out.println(timestamp);
    }

    public static boolean isInside(int x, int y) {
        return x >= 1 && x <= N && y >= 1 && y <= N;
    }
}



