#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define ADD 0
#define SUB 1
#define EQU 2

int base[3];
int A[3], B[3], C[3], op[2];

char buffer[15];
int n_buffer = 0;

char results[1000][15];
int n_results = 0;

void read(int *const X)
{
    char c;
    while (!isalnum(c = getchar()))
        ;
    ungetc(c, stdin);

    int index = 0;
    X[0] = -1;
    X[1] = -1;
    X[2] = -1;
    while (isalnum(c = getchar()))
    {
        X[index++] = (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;
    }
    assert(index == 1 || index == 2 || index == 3);
    if (index == 1)
    {
        X[2] = X[0];
        X[1] = -1;
        X[0] = -1;
    }
    if (index == 2)
    {
        X[2] = X[1];
        X[1] = X[0];
        X[0] = -1;
    }
    ungetc(c, stdin);
}

void write(int *const X)
{
    if (X[0] >= 0)
        buffer[n_buffer++] = (X[0] <= 9) ? X[0] + '0' : X[0] - 10 + 'A';
    if (X[1] >= 0)
        buffer[n_buffer++] = (X[1] <= 9) ? X[1] + '0' : X[1] - 10 + 'A';
    assert(X[2] >= 0);
    buffer[n_buffer++] = (X[2] <= 9) ? X[2] + '0' : X[2] - 10 + 'A';
}

void result()
{
    for (int i = 0; i < n_results; i++)
        if (strcmp(buffer, results[i]) == 0)
            return;
    strcpy(results[n_results++], buffer);
}

void generate()
{
    n_buffer = 0;
    write(A);
    buffer[n_buffer++] = op[0] == ADD ? '+' : (op[0] == SUB ? '-' : '=');
    write(B);
    buffer[n_buffer++] = op[1] == ADD ? '+' : (op[1] == SUB ? '-' : '=');
    write(C);
}

int eval(int *const X, int base)
{
    int sum = 0;
    if (X[0] >= 0)
    {
        sum = sum * base + X[0];
    }
    if (X[1] >= 0)
    {
        sum = sum * base + X[1];
    }
    assert(X[2] >= 0);
    sum = sum * base + X[2];
    return sum;
}

bool judge_base(int *const X, int base)
{
    return (X[0] < base) && (X[1] < base) && (X[2] < base);
}

bool judge()
{
    if ((op[0] != EQU && op[1] != EQU) || (op[0] == EQU && op[1] == EQU))
        return false;
    if (!judge_base(A, base[0]))
        return false;
    if (!judge_base(B, base[1]))
        return false;
    if (!judge_base(C, base[2]))
        return false;
    if (op[0] == EQU)
    {
        assert(op[1] == ADD || op[1] == SUB);
        if (op[1] == ADD)
        {
            return eval(A, base[0]) == eval(B, base[1]) + eval(C, base[2]);
        }
        else
        {
            return eval(A, base[0]) == eval(B, base[1]) - eval(C, base[2]);
        }
    }
    else
    {
        assert(op[0] == ADD || op[0] == SUB);
        if (op[0] == ADD)
        {
            return eval(A, base[0]) + eval(B, base[1]) == eval(C, base[2]);
        }
        else
        {
            return eval(A, base[0]) - eval(B, base[1]) == eval(C, base[2]);
        }
    }
}

int _A[3], _B[3], _C[3], _op[2];

bool table_add[16][16] = {
    //  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
};

bool table_self[16][16] = {
    //  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
};

/*
#define ADD 0
#define SUB 1
#define EQU 2
*/

bool table_op_add[3][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 0, 0},
};

void try_self_p(int *p)
{
    if (p < 0)
        return;
    int backup = *p;
    for (int i = 0; i < 16; i++)
    {
        if (table_self[backup][i])
        {
            *p = i;
            if (judge())
            {
                generate();
                result();
            }
        }
    }
    *p = backup;
}

void try_self()
{
    try_self_p(&A[0]);
    try_self_p(&A[1]);
    try_self_p(&A[2]);
    try_self_p(&B[0]);
    try_self_p(&B[1]);
    try_self_p(&B[2]);
    try_self_p(&C[0]);
    try_self_p(&C[1]);
    try_self_p(&C[2]);
}

void try_add_nb(int *p)
{
    if (p < 0)
        return;
    int backup = *p;
    for (int i = 0; i < 16; i++)
    {
        if (table_add[backup][i])
        {
            *p = i;
            if (judge())
            {
                generate();
                result();
            }
        }
    }
    *p = backup;
}

void try_add_op(int *p)
{
    assert(*p == ADD || *p == SUB || *p == EQU);
    int backup = *p;
    for (int i = 0; i < 3; i++)
    {
        if (table_op_add[backup][i])
        {
            *p = i;
            if (judge())
            {
                generate();
                result();
            }
        }
    }
    *p = backup;
}

void try_sub_nb(int *p)
{
    if (p < 0)
        return;
    int backup = *p;
    for (int i = 0; i < 16; i++)
    {
        if (table_add[i][backup])
        {
            *p = i;
            if (judge())
            {
                generate();
                result();
            }
        }
    }
    *p = backup;
}

void try_sub_op(int *p)
{
    assert(*p == ADD || *p == SUB || *p == EQU);
    int backup = *p;
    for (int i = 0; i < 3; i++)
    {
        if (table_op_add[i][backup])
        {
            *p = i;
            if (judge())
            {
                generate();
                result();
            }
        }
    }
    *p = backup;
}

void try_add()
{
    try_add_nb(&A[0]);
    try_add_nb(&A[1]);
    try_add_nb(&A[2]);
    try_add_nb(&B[0]);
    try_add_nb(&B[1]);
    try_add_nb(&B[2]);
    try_add_nb(&C[0]);
    try_add_nb(&C[1]);
    try_add_nb(&C[2]);
    try_add_op(&op[0]);
    try_add_op(&op[1]);
}

void try_sub()
{
    try_sub_nb(&A[0]);
    try_sub_nb(&A[1]);
    try_sub_nb(&A[2]);
    try_sub_nb(&B[0]);
    try_sub_nb(&B[1]);
    try_sub_nb(&B[2]);
    try_sub_nb(&C[0]);
    try_sub_nb(&C[1]);
    try_sub_nb(&C[2]);
    try_sub_op(&op[0]);
    try_sub_op(&op[1]);
}

void try_add_and_sub_nb(int *p)
{
    if (p < 0)
        return;
    int backup = *p;
    for (int i = 0; i < 16; i++)
    {
        if (table_add[backup][i])
        {
            *p = i;
            try_sub();
        }
    }
    *p = backup;
}

void try_add_and_sub_op(int *p)
{
    assert(*p == ADD || *p == SUB || *p == EQU);
    int backup = *p;
    for (int i = 0; i < 3; i++)
    {
        if (table_op_add[backup][i])
        {
            *p = i;
            try_sub();
        }
    }
    *p = backup;
}

void try_add_and_sub()
{
    try_add_and_sub_nb(&A[0]);
    try_add_and_sub_nb(&A[1]);
    try_add_and_sub_nb(&A[2]);
    try_add_and_sub_nb(&B[0]);
    try_add_and_sub_nb(&B[1]);
    try_add_and_sub_nb(&B[2]);
    try_add_and_sub_nb(&C[0]);
    try_add_and_sub_nb(&C[1]);
    try_add_and_sub_nb(&C[2]);
    try_add_and_sub_op(&op[0]);
    try_add_and_sub_op(&op[1]);
}

void try_sub_and_add_nb(int *p)
{
    if (p < 0)
        return;
    int backup = *p;
    for (int i = 0; i < 16; i++)
    {
        if (table_add[i][backup])
        {
            *p = i;
            try_add();
        }
    }
    *p = backup;
}

void try_sub_and_add_op(int *p)
{
    assert(*p == ADD || *p == SUB || *p == EQU);
    int backup = *p;
    for (int i = 0; i < 3; i++)
    {
        if (table_op_add[i][backup])
        {
            *p = i;
            try_add();
        }
    }
    *p = backup;
}

void try_sub_and_add()
{
    try_sub_and_add_nb(&A[0]);
    try_sub_and_add_nb(&A[1]);
    try_sub_and_add_nb(&A[2]);
    try_sub_and_add_nb(&B[0]);
    try_sub_and_add_nb(&B[1]);
    try_sub_and_add_nb(&B[2]);
    try_sub_and_add_nb(&C[0]);
    try_sub_and_add_nb(&C[1]);
    try_sub_and_add_nb(&C[2]);
    try_sub_and_add_op(&op[0]);
    try_sub_and_add_op(&op[1]);
}

// can call backup() and recover()
int main()
{
    scanf("%d%d%d", &base[0], &base[1], &base[2]);
    read(A);
    op[0] = getchar() == '+' ? ADD : SUB;
    read(B);
    assert(getchar() == '=');
    op[1] = EQU;
    read(C);
    // backup();

    if (judge())
    {
        generate();
        result();
    }

    try_self();
    // recover();
    try_add_and_sub();
    // recover();
    try_sub_and_add();

    for (int i = 0; i < n_results; i++)
    {
        printf("%s\n", results[i]);
    }

    return 0;
}
