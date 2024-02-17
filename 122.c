#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int n, m;
    bool *map; // map[m + 3 + r * (m + 2) + c]
    bool *ok;
} Maze, *pMaze;

void MazeInit(pMaze maze, int n, int m)
{
    maze->n = n;
    maze->m = m;
    maze->map = (bool *)malloc(sizeof(bool) * (m + 2) * (n + 2));
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            maze->map[i * (m + 2) + j] = false;
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int input;
            scanf("%d", &input);
            input ? (maze->map[m + 3 + r * (m + 2) + c] = true) : (maze->map[m + 3 + r * (m + 2) + c] = false);
        }
    }
    maze->ok = (bool *)malloc(sizeof(bool) * m * n);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            maze->ok[r * m + c] = false;
        }
    }
    maze->ok[0] = true;
}

void MazeExpand(pMaze maze, int r, int c)
{
    int m = maze->m;
    int indexOfMap = m + 3 + r * (m + 2) + c;
    int indexOfOk = r * m + c;
    if (maze->map[indexOfMap - 1] == true && maze->ok[indexOfOk - 1] == false) {
        maze->ok[indexOfOk - 1] = true;
        MazeExpand(maze, r, c - 1);
    }
    if (maze->map[indexOfMap + 1] == true && maze->ok[indexOfOk + 1] == false) {
        maze->ok[indexOfOk + 1] = true;
        MazeExpand(maze, r, c + 1);
    }
    if (maze->map[indexOfMap - (m + 2)] == true && maze->ok[indexOfOk - m] == false) {
        maze->ok[indexOfOk - m] = true;
        MazeExpand(maze, r - 1, c);
    }
    if (maze->map[indexOfMap + (m + 2)] == true && maze->ok[indexOfOk + m] == false) {
        maze->ok[indexOfOk + m] = true;
        MazeExpand(maze, r + 1, c);
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    Maze maze;
    MazeInit(&maze, n, m);
    MazeExpand(&maze, 0, 0);
    if (maze.ok[n * m - 1])
        printf("YES");
    else
        printf("NO");
    return 0;
}
