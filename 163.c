#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    _NotHandled,
    _AlreadyHandled,
    _NotLand,
    _ResultSaved,
} _Status;

typedef struct {
    _Status _;
} Status;

const Status NotHandled = {._ = _NotHandled};
const Status AlreadyHandled = {._ = _AlreadyHandled};
const Status NotLand = {._ = _NotLand};
const Status ResultSaved = {._ = _ResultSaved};

typedef struct {
    bool _;
} Boolean;

const Boolean True = {._ = true};
const Boolean False = {._ = false};

typedef struct {
    int size;
    Status status;
} Cell;

int n, m;
Cell *cells;

void init()
{
    scanf("%d%d", &n, &m);
    cells = (Cell *)malloc(sizeof(Cell) * n * m);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            char input;
            while (isblank(input = getchar()))
                ;
            Cell init_cell;
            init_cell.size = 0;
            if (input == '.')
                init_cell.status = NotHandled;
            else
                init_cell.status = NotLand;
            cells[r * m + c] = init_cell;
        }
    }
}

int counter;

void handle(int r, int c, Boolean init_call)
{
    if (r < 0 || r >= n || c < 0 || c >= m)
        return;
    Cell cell = cells[r * m + c];
    if (cell.status._ == NotLand._ || cell.status._ == AlreadyHandled._)
        return;
    if (init_call._) {
        counter = 0;
    }
    ++counter;
    cells[r * m + c].status = AlreadyHandled;
    handle(r - 1, c - 1, False);
    handle(r - 1, c + 1, False);
    handle(r + 1, c - 1, False);
    handle(r + 1, c + 1, False);
    if (init_call._) {
        cells[r * m + c].status = ResultSaved;
        cells[r * m + c].size = counter;
    }
}

int main()
{
    init();
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            handle(r, c, True);
        }
    }
    int max = -1;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (cells[r * m + c].size == ResultSaved) {
                
            }
        }
    }
}
