// start for debug
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <string.h>

void gets(char *buffer)
{
    char inner_buffer[256];
    scanf("%s", inner_buffer);
    strcpy(buffer, inner_buffer);
}
// end for debug

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#define MAX_LEN 4096

// 各种数据类型的变量
char c = '\0';
short s = 0;
int i = 0;
long long ll = 0;
float f = 0.0;
double d = 0.0;
char str[MAX_LEN] = "";
void *p = NULL;

// 输入、输出缓存区
char in_buf[MAX_LEN], out_buf[MAX_LEN];

// 输入、输出缓冲区当前位置
char in_fmt[MAX_LEN], out_fmt[MAX_LEN];

// 输入、输出格式控制字符串
int in_idx, out_idx;

// 用于自行定义辅助函数，如果没有，可以空缺
//____qcodep____

// return if the char is end of string
// gcc block expression language extension is used here
#define RET_IF_END(A) \
    if ((A) == '\0') RETURN()

#define RET_IF_TRUE(A) \
    if ((A)) RETURN()

#define LENGTH_SPECIFIER_NONE 0
#define LENGTH_SPECIFIER_HH 1
#define LENGTH_SPECIFIER_H 2
#define LENGTH_SPECIFIER_L 3
#define LENGTH_SPECIFIER_LL 4
// #define LENGTH_SPECIFIER_J 5  // length specifier j, z and t are not supported
// #define LENGTH_SPECIFIER_Z 6  // they are added in C99, and are not commonly used
// #define LENGTH_SPECIFIER_T 7
#define LENGTH_SPECIFIER_L_CAPITAL 8

#define SPECIFIER_I 1
#define SPECIFIER_D 2
#define SPECIFIER_U 3
#define SPECIFIER_O 4
#define SPECIFIER_X 5
#define SPECIFIER_F 6
#define SPECIFIER_E 7
#define SPECIFIER_G 8
#define SPECIFIER_A 9
#define SPECIFIER_C 10
#define SPECIFIER_S 11
#define SPECIFIER_P 12
#define SPECIFIER_SCANSET 13
#define SPECIFIER_N 14

// read a char from input buffer
char mygetc()
{
    return in_buf[in_idx++];
}

// after redo_readchar(), the next readchar() will read the same char
void myungetc()
{
    in_idx--;
}

// alternative to isspace() in ctype.h
int myisspace(int c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

// alternative to isdigit() in ctype.h
int myisdigit(int c)
{
    return c >= '0' && c <= '9';
}

// the following functions (do_read_*) return true if input is ended
// and return false if input is not ended
#define RETURN() \
    return 1

#define _READ_D(ptr, max_len)                           \
    *ptr = 0;                                           \
    int sign = 1;                                       \
    int digit;                                          \
    int read_len = 0;                                   \
    char buf_char;                                      \
    RET_IF_END(buf_char = mygetc());                    \
    if (read_len < max_len && buf_char == '-') {        \
        sign = -1;                                      \
        read_len++;                                     \
        RET_IF_END(buf_char = mygetc());                \
    }                                                   \
    while (read_len < max_len && myisdigit(buf_char)) { \
        digit = buf_char - '0';                         \
        *ptr = *ptr * 10 + digit;                       \
        read_len++;                                     \
        RET_IF_END(buf_char = mygetc());                \
    }                                                   \
    myungetc();                                         \
    *ptr *= sign;                                       \
    return 0;

int do_read_d(int *ptr, int max_len)
{
    _READ_D(ptr, max_len)
}

int do_read_hhd(signed char *ptr, int max_len)
{
    _READ_D(ptr, max_len)
}

int do_read_hd(short int *ptr, int max_len)
{
    _READ_D(ptr, max_len)
}

int do_read_ld(long *ptr, int max_len)
{
    _READ_D(ptr, max_len)
}

int do_read_lld(long long *ptr, int max_len)
{
    _READ_D(ptr, max_len)
}

/*
Any number of digits, optionally preceded by a sign (+ or -).
Decimal digits assumed by default (0-9), but a 0 prefix introduces octal digits (0-7), and 0x hexadecimal digits (0-f).
Signed argument.
*/
#define _READ_I(ptr, max_len)                                                                                                                 \
    *ptr = 0;                                                                                                                                 \
    int sign = 1;                                                                                                                             \
    int digit;                                                                                                                                \
    int read_len = 0;                                                                                                                         \
    char buf_char;                                                                                                                            \
    int mode;                                                                                                                                 \
    RET_IF_END(buf_char = mygetc());                                                                                                          \
    if (read_len < max_len && buf_char == '-') {                                                                                              \
        sign = -1;                                                                                                                            \
        read_len++;                                                                                                                           \
        RET_IF_END(buf_char = mygetc());                                                                                                      \
    }                                                                                                                                         \
    mode = 0;                                                                                                                                 \
    if (read_len < max_len && buf_char == '0') {                                                                                              \
        read_len++;                                                                                                                           \
        RET_IF_END(buf_char = mygetc());                                                                                                      \
        if (read_len < max_len && (buf_char == 'x' || buf_char == 'X')) {                                                                     \
            mode = 2;                                                                                                                         \
            read_len++;                                                                                                                       \
            RET_IF_END(buf_char = mygetc());                                                                                                  \
        } else {                                                                                                                              \
            mode = 1;                                                                                                                         \
        }                                                                                                                                     \
    }                                                                                                                                         \
    switch (mode) {                                                                                                                           \
    default:                                                                                                                                  \
        assert(0);                                                                                                                            \
        break;                                                                                                                                \
    case 0:                                                                                                                                   \
        while (read_len < max_len && myisdigit(buf_char)) {                                                                                   \
            digit = buf_char - '0';                                                                                                           \
            *ptr = *ptr * 10 + digit;                                                                                                         \
            read_len++;                                                                                                                       \
            RET_IF_END(buf_char = mygetc());                                                                                                  \
        }                                                                                                                                     \
        break;                                                                                                                                \
    case 1:                                                                                                                                   \
        while (read_len < max_len && buf_char >= '0' && buf_char <= '7') {                                                                    \
            digit = buf_char - '0';                                                                                                           \
            *ptr = *ptr * 8 + digit;                                                                                                          \
            read_len++;                                                                                                                       \
            RET_IF_END(buf_char = mygetc());                                                                                                  \
        }                                                                                                                                     \
        break;                                                                                                                                \
    case 2:                                                                                                                                   \
        while (read_len < max_len && (myisdigit(buf_char) || (buf_char >= 'a' && buf_char <= 'f') || (buf_char >= 'A' && buf_char <= 'F'))) { \
            if (myisdigit(buf_char)) {                                                                                                        \
                digit = buf_char - '0';                                                                                                       \
            } else if (buf_char >= 'a' && buf_char <= 'f') {                                                                                  \
                digit = buf_char - 'a' + 10;                                                                                                  \
            } else {                                                                                                                          \
                digit = buf_char - 'A' + 10;                                                                                                  \
            }                                                                                                                                 \
            *ptr = *ptr * 16 + digit;                                                                                                         \
            read_len++;                                                                                                                       \
            RET_IF_END(buf_char = mygetc());                                                                                                  \
        }                                                                                                                                     \
        break;                                                                                                                                \
    }                                                                                                                                         \
    myungetc();                                                                                                                               \
    *ptr *= sign;                                                                                                                             \
    return 0;

int do_read_i(int *ptr, int max_len)
{
    _READ_I(ptr, max_len)
}

int do_read_hhi(signed char *ptr, int max_len)
{
    _READ_I(ptr, max_len)
}

int do_read_hi(short int *ptr, int max_len)
{
    _READ_I(ptr, max_len)
}

int do_read_li(long *ptr, int max_len)
{
    _READ_I(ptr, max_len)
}

int do_read_lli(long long *ptr, int max_len)
{
    _READ_I(ptr, max_len)
}

#define _READ_U(ptr, max_len)                           \
    *ptr = 0;                                           \
    int digit;                                          \
    int read_len = 0;                                   \
    char buf_char;                                      \
    RET_IF_END(buf_char = mygetc());                    \
    while (read_len < max_len && myisdigit(buf_char)) { \
        digit = buf_char - '0';                         \
        *ptr = *ptr * 10 + digit;                       \
        read_len++;                                     \
        RET_IF_END(buf_char = mygetc());                \
    }                                                   \
    myungetc();                                         \
    return 0;

int do_read_u(unsigned int *ptr, int max_len)
{
    _READ_U(ptr, max_len)
}

int do_read_hhu(unsigned char *ptr, int max_len)
{
    _READ_U(ptr, max_len)
}

int do_read_hu(unsigned short int *ptr, int max_len)
{
    _READ_U(ptr, max_len)
}

int do_read_lu(unsigned long *ptr, int max_len)
{
    _READ_U(ptr, max_len)
}

int do_read_llu(unsigned long long *ptr, int max_len)
{
    _READ_U(ptr, max_len)
}

#define _READ_O(ptr, max_len)                                          \
    *ptr = 0;                                                          \
    int digit;                                                         \
    int read_len = 0;                                                  \
    char buf_char;                                                     \
    RET_IF_END(buf_char = mygetc());                                   \
    while (read_len < max_len && buf_char >= '0' && buf_char <= '7') { \
        digit = buf_char - '0';                                        \
        *ptr = *ptr * 8 + digit;                                       \
        read_len++;                                                    \
        RET_IF_END(buf_char = mygetc());                               \
    }                                                                  \
    myungetc();                                                        \
    return 0;

int do_read_o(unsigned int *ptr, int max_len)
{
    _READ_O(ptr, max_len)
}

int do_read_hho(unsigned char *ptr, int max_len)
{
    _READ_O(ptr, max_len)
}

int do_read_ho(unsigned short int *ptr, int max_len)
{
    _READ_O(ptr, max_len)
}

int do_read_lo(unsigned long *ptr, int max_len)
{
    _READ_O(ptr, max_len)
}

int do_read_llo(unsigned long long *ptr, int max_len)
{
    _READ_O(ptr, max_len)
}

#define _READ_X(ptr, max_len)                                                                                                             \
    *ptr = 0;                                                                                                                             \
    int digit;                                                                                                                            \
    int read_len = 0;                                                                                                                     \
    char buf_char;                                                                                                                        \
    RET_IF_END(buf_char = mygetc());                                                                                                      \
    while (read_len < max_len && (myisdigit(buf_char) || (buf_char >= 'a' && buf_char <= 'f') || (buf_char >= 'A' && buf_char <= 'F'))) { \
        if (myisdigit(buf_char)) {                                                                                                        \
            digit = buf_char - '0';                                                                                                       \
        } else if (buf_char >= 'a' && buf_char <= 'f') {                                                                                  \
            digit = buf_char - 'a' + 10;                                                                                                  \
        } else {                                                                                                                          \
            digit = buf_char - 'A' + 10;                                                                                                  \
        }                                                                                                                                 \
        *ptr = *ptr * 16 + digit;                                                                                                         \
        read_len++;                                                                                                                       \
        RET_IF_END(buf_char = mygetc());                                                                                                  \
    }                                                                                                                                     \
    myungetc();                                                                                                                           \
    return 0;

int do_read_x(unsigned int *ptr, int max_len)
{
    _READ_X(ptr, max_len)
}

int do_read_hhx(unsigned char *ptr, int max_len)
{
    _READ_X(ptr, max_len)
}

int do_read_hx(unsigned short int *ptr, int max_len)
{
    _READ_X(ptr, max_len)
}

int do_read_lx(unsigned long *ptr, int max_len)
{
    _READ_X(ptr, max_len)
}

int do_read_llx(unsigned long long *ptr, int max_len)
{
    _READ_X(ptr, max_len)
}

int do_read_f(float *ptr, int max_len)
{
}

int do_read_lf(double *ptr, int max_len)
{
}

int do_read_lf_capital(double *ptr, int max_len)
{
}

int do_read_c(char *ptr, int max_len)
{
}

int do_read_string(char *ptr, int max_len, const int scanset[])
{
}

int do_read_p(void **ptr, int max_len)
{
}

int do_read_n(int *ptr, int max_len)
{
}

int do_read_hhn(signed char *ptr, int max_len)
{
}

int do_read_hn(short int *ptr, int max_len)
{
}

int do_read_ln(long int *ptr, int max_len)
{
}

int do_read_lln(long long int *ptr, int max_len)
{
}

#undef RETURN

void myscanf(char *fmt, ...)
{
    //____qcodep____

    in_idx = 0;

    // see https://www.cprogramming.com/tutorial/c/lesson17.html
    va_list args;
    va_start(args, fmt);
#define RETURN()      \
    {                 \
        va_end(args); \
        return;       \
    }

    // See: https://cplusplus.com/reference/cstdio/scanf/
    char *fmt_ptr = fmt;
    char buf_char;
    // for the meaning of the following variables, see their use in the switch statement
    int ignore_flag = 0;
    int max_len = 0;
    int length_specifier = LENGTH_SPECIFIER_NONE;
    int specifier = 0;
    int scanset_negated = 0;
    int scanset[256] = {0};
    const int full_scan_set[256] = {0};
    int ret;
    for (int i = 0; i < 256; i++) ((int *)full_scan_set)[i] = 1;
    // Temporary variables for ignore_flag
    int temp_i;
    signed char temp_hhd;
    short int temp_hi;
    long int temp_li;
    long long int temp_lli;
    unsigned int temp_u;
    unsigned char temp_hhu;
    unsigned short int temp_hu;
    unsigned long int temp_lu;
    unsigned long long int temp_llu;
    float temp_f;
    double temp_lf;
    char temp_c;
    void *temp_p;
    int temp_n;
    while (1) {
        switch (*fmt_ptr) {
        case '\0':
            RETURN();

            // Whitespace character: the function will read and ignore any whitespace characters encountered before the next
            // non-whitespace character (whitespace characters include spaces, newline and tab characters -- see isspace).
            // A single whitespace in the format string validates any quantity of whitespace characters extracted from the stream
            // (including none).
        case ' ': // For blank characters, see https://cplusplus.com/reference/cctype/isspace/
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
            RET_IF_END(buf_char = mygetc());
            while (myisspace(buf_char)) {
                RET_IF_END(buf_char = mygetc());
            }
            myungetc();
            fmt_ptr++;
            break;

            // Non-whitespace character, except format specifier (%): Any character that is not either a whitespace character (blank,
            // newline or tab) or part of a format specifier (which begin with a % character) causes the function to read the next
            // character from the stream, compare it to this non-whitespace character and if it matches, it is discarded and the function
            // continues with the next character of format. If the character does not match, the function fails, returning and leaving
            // subsequent characters of the stream unread.
        default:
            RET_IF_END(buf_char = mygetc());
            if (buf_char != *fmt_ptr) {
                RETURN();
            }
            fmt_ptr++;
            break;

            // Format specifiers: A sequence formed by an initial percentage sign (%) indicates a format specifier, which is used to
            // specify the type and format of the data to be retrieved from the stream and stored into the locations pointed by the
            // additional arguments.

            // A format specifier for scanf follows this prototype:

            //%[*][width][length]specifier

            // Where the specifier character at the end is the most significant component, since it defines which characters are
            // extracted, their interpretation and the type of its corresponding argument:
        case '%':
            fmt_ptr++;
            RET_IF_END(*fmt_ptr);

            // HANDLE INPUT PART: [*]
            // An optional starting asterisk(*) indicates that the data is to be read from the stream but ignored (i.e. it is not stored
            // in the location pointed by an argument).
            if (*fmt_ptr == '*') {
                ignore_flag = 1;
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
            } else {
                ignore_flag = 0;
            }

            // HANDLE INPUT PART: [width]
            // An optional decimal digit string specifies the maximum number of characters to be read in the current reading operation.
            if (myisdigit(*fmt_ptr)) {
                max_len = 0;
                do {
                    max_len = max_len * 10 + (*fmt_ptr - '0');
                    fmt_ptr++;
                    RET_IF_END(*fmt_ptr);
                } while (myisdigit(*fmt_ptr));
            } else {
                max_len = MAX_LEN; // Obviously, this can cause very serious security issues.
            }

            // HANDLE INPUT PART: [length]
            // One of hh, h, l, ll, j, z, t, L (optional).
            // This alters the expected type of the storage pointed by the corresponding argument (see below).
            switch (*fmt_ptr) {
            default:
                length_specifier = LENGTH_SPECIFIER_NONE;
                break;
            case 'h':
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                if (*fmt_ptr == 'h') {
                    fmt_ptr++;
                    RET_IF_END(*fmt_ptr);
                    length_specifier = LENGTH_SPECIFIER_HH;
                } else {
                    length_specifier = LENGTH_SPECIFIER_H;
                }
                break;
            case 'l':
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                if (*fmt_ptr == 'l') {
                    fmt_ptr++;
                    RET_IF_END(*fmt_ptr);
                    length_specifier = LENGTH_SPECIFIER_LL;
                } else {
                    length_specifier = LENGTH_SPECIFIER_L;
                }
                break;
            case 'j':
                assert(0);
                // not supported
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                // length_specifier = LENGTH_SPECIFIER_J;
                break;
            case 'z':
                assert(0);
                // not supported
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                // length_specifier = LENGTH_SPECIFIER_Z;
                break;
            case 't':
                assert(0);
                // not supported
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                // length_specifier = LENGTH_SPECIFIER_T;
                break;
            case 'L':
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                length_specifier = LENGTH_SPECIFIER_L_CAPITAL;
                break;
            }

            // HANDLE INPUT PART: [specifier]
            switch (*fmt_ptr) {
            default: // If the format specifier is invalid, the behavior is undefined.
                RETURN();

                // A % followed by another % matches a single %.
            case '%':
                RET_IF_END(buf_char = mygetc());
                if (buf_char != '%') {
                    RETURN();
                }
                fmt_ptr++;
                continue;

            case '[':
                fmt_ptr++;
                RET_IF_END(*fmt_ptr);
                if (*fmt_ptr == '^') {
                    scanset_negated = 1;
                    fmt_ptr++;
                    RET_IF_END(*fmt_ptr);
                    for (int i = 0; i < 256; i++) scanset[i] = 1;
                } else {
                    scanset_negated = 0;
                    for (int i = 0; i < 256; i++) scanset[i] = 0;
                }
                while (*fmt_ptr != ']') {
                    RET_IF_END(*fmt_ptr);
                    scanset[*fmt_ptr] = !scanset_negated;
                    fmt_ptr++;
                }
                specifier = SPECIFIER_SCANSET;
                fmt_ptr++;
                break;

            case 'i':
                specifier = SPECIFIER_I;
                fmt_ptr++;
                break;

            case 'd':
                specifier = SPECIFIER_D;
                fmt_ptr++;
                break;

            case 'u':
                specifier = SPECIFIER_U;
                fmt_ptr++;
                break;

            case 'o':
                specifier = SPECIFIER_O;
                fmt_ptr++;
                break;

            case 'x':
                specifier = SPECIFIER_X;
                fmt_ptr++;
                break;

            case 'f':
                specifier = SPECIFIER_F;
                fmt_ptr++;
                break;

            case 'e':
                specifier = SPECIFIER_E;
                fmt_ptr++;
                break;

            case 'g':
                specifier = SPECIFIER_G;
                fmt_ptr++;
                break;

            case 'a':
                specifier = SPECIFIER_A;
                fmt_ptr++;
                break;

            case 'c':
                specifier = SPECIFIER_C;
                fmt_ptr++;
                break;

            case 's':
                specifier = SPECIFIER_S;
                fmt_ptr++;
                break;

            case 'p':
                specifier = SPECIFIER_P;
                fmt_ptr++;
                break;
            }

            // EXCUTE INPUT COMMAND
            switch (specifier) {
            default:
                RETURN();
            case SPECIFIER_I:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_i = 0;
                        ret = do_read_i(&temp_i, max_len);
                    } else {
                        ret = do_read_i(va_arg(args, int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_HH:
                    if (ignore_flag) {
                        temp_hhd = 0;
                        ret = do_read_hhi(&temp_hhd, max_len);
                    } else {
                        ret = do_read_hhi(va_arg(args, signed char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_H:
                    if (ignore_flag) {
                        temp_hi = 0;
                        ret = do_read_hi(&temp_hi, max_len);
                    } else {
                        ret = do_read_hi(va_arg(args, short int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_li = 0;
                        ret = do_read_li(&temp_li, max_len);
                    } else {
                        ret = do_read_li(va_arg(args, long int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_LL:
                    if (ignore_flag) {
                        temp_lli = 0;
                        ret = do_read_lli(&temp_lli, max_len);
                    } else {
                        ret = do_read_lli(va_arg(args, long long int *), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_D:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_i = 0;
                        ret = do_read_d(&temp_i, max_len);
                    } else {
                        ret = do_read_d(va_arg(args, int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_HH:
                    if (ignore_flag) {
                        temp_hhd = 0;
                        ret = do_read_hhd(&temp_hhd, max_len);
                    } else {
                        ret = do_read_hhd(va_arg(args, signed char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_H:
                    if (ignore_flag) {
                        temp_hi = 0;
                        ret = do_read_hd(&temp_hi, max_len);
                    } else {
                        ret = do_read_hd(va_arg(args, short int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_li = 0;
                        ret = do_read_ld(&temp_li, max_len);
                    } else {
                        ret = do_read_ld(va_arg(args, long int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_LL:
                    if (ignore_flag) {
                        temp_lli = 0;
                        ret = do_read_lld(&temp_lli, max_len);
                    } else {
                        ret = do_read_lld(va_arg(args, long long int *), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_U:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_u = 0;
                        ret = do_read_u(&temp_u, max_len);
                    } else {
                        ret = do_read_u(va_arg(args, unsigned int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_HH:
                    if (ignore_flag) {
                        temp_hhu = 0;
                        ret = do_read_hhu(&temp_hhu, max_len);
                    } else {
                        ret = do_read_hhu(va_arg(args, unsigned char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_H:
                    if (ignore_flag) {
                        temp_hu = 0;
                        ret = do_read_hu(&temp_hu, max_len);
                    } else {
                        ret = do_read_hu(va_arg(args, unsigned short int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_lu = 0;
                        ret = do_read_lu(&temp_lu, max_len);
                    } else {
                        ret = do_read_lu(va_arg(args, unsigned long int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_LL:
                    if (ignore_flag) {
                        temp_llu = 0;
                        ret = do_read_llu(&temp_llu, max_len);
                    } else {
                        ret = do_read_llu(va_arg(args, unsigned long long int *), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_O:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_u = 0;
                        ret = do_read_o(&temp_u, max_len);
                    } else {
                        ret = do_read_o(va_arg(args, unsigned int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_HH:
                    if (ignore_flag) {
                        temp_hhu = 0;
                        ret = do_read_hho(&temp_hhu, max_len);
                    } else {
                        ret = do_read_hho(va_arg(args, unsigned char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_H:
                    if (ignore_flag) {
                        temp_hu = 0;
                        ret = do_read_ho(&temp_hu, max_len);
                    } else {
                        ret = do_read_ho(va_arg(args, unsigned short int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_lu = 0;
                        ret = do_read_lo(&temp_lu, max_len);
                    } else {
                        ret = do_read_lo(va_arg(args, unsigned long int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_LL:
                    if (ignore_flag) {
                        temp_llu = 0;
                        ret = do_read_llo(&temp_llu, max_len);
                    } else {
                        ret = do_read_llo(va_arg(args, unsigned long long int *), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_X:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_u = 0;
                        ret = do_read_x(&temp_u, max_len);
                    } else {
                        ret = do_read_x(va_arg(args, unsigned int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_HH:
                    if (ignore_flag) {
                        temp_hhu = 0;
                        ret = do_read_hhx(&temp_hhu, max_len);
                    } else {
                        ret = do_read_hhx(va_arg(args, unsigned char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_H:
                    if (ignore_flag) {
                        temp_hu = 0;
                        ret = do_read_hx(&temp_hu, max_len);
                    } else {
                        ret = do_read_hx(va_arg(args, unsigned short int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_lu = 0;
                        ret = do_read_lx(&temp_lu, max_len);
                    } else {
                        ret = do_read_lx(va_arg(args, unsigned long int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_LL:
                    if (ignore_flag) {
                        temp_llu = 0;
                        ret = do_read_llx(&temp_llu, max_len);
                    } else {
                        ret = do_read_llx(va_arg(args, unsigned long long int *), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_F:
            case SPECIFIER_E:
            case SPECIFIER_G:
            case SPECIFIER_A:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_f = 0;
                        ret = do_read_f(&temp_f, max_len);
                    } else {
                        ret = do_read_f(va_arg(args, float *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_lf = 0;
                        ret = do_read_lf(&temp_lf, max_len);
                    } else {
                        ret = do_read_lf(va_arg(args, double *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L_CAPITAL:
                    if (ignore_flag) {
                        temp_lf = 0;
                        ret = do_read_lf_capital(&temp_lf, max_len);
                    } else {
                        ret = do_read_lf_capital(va_arg(args, double *), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_C:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_c = 0;
                        ret = do_read_c(&temp_c, max_len);
                    } else {
                        ret = do_read_c(va_arg(args, char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    // not supported
                    assert(0);
                    break;
                }
                break;
            case SPECIFIER_S:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_c = 0;
                        ret = do_read_string(&temp_c, max_len, full_scan_set);
                    } else {
                        ret = do_read_string(va_arg(args, char *), max_len, full_scan_set);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    // not supported
                    assert(0);
                    break;
                }
                break;
            case SPECIFIER_SCANSET:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_c = 0;
                        ret = do_read_string(&temp_c, max_len, scanset);
                    } else {
                        ret = do_read_string(va_arg(args, char *), max_len, scanset);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    // not supported
                    assert(0);
                    break;
                }
                break;
            case SPECIFIER_P:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_p = NULL;
                        ret = do_read_p(&temp_p, max_len);
                    } else {
                        ret = do_read_p(va_arg(args, void **), max_len);
                    }
                    break;
                }
                break;
            case SPECIFIER_N:
                switch (length_specifier) {
                default:
                    RETURN();
                case LENGTH_SPECIFIER_NONE:
                    if (ignore_flag) {
                        temp_n = 0;
                        ret = do_read_n(&temp_n, max_len);
                    } else {
                        ret = do_read_n(va_arg(args, int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_HH:
                    if (ignore_flag) {
                        temp_hhd = 0;
                        ret = do_read_hhn(&temp_hhd, max_len);
                    } else {
                        ret = do_read_hhn(va_arg(args, signed char *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_H:
                    if (ignore_flag) {
                        temp_hi = 0;
                        ret = do_read_hn(&temp_hi, max_len);
                    } else {
                        ret = do_read_hn(va_arg(args, short int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_L:
                    if (ignore_flag) {
                        temp_li = 0;
                        ret = do_read_ln(&temp_li, max_len);
                    } else {
                        ret = do_read_ln(va_arg(args, long int *), max_len);
                    }
                    break;
                case LENGTH_SPECIFIER_LL:
                    if (ignore_flag) {
                        temp_lli = 0;
                        ret = do_read_lln(&temp_lli, max_len);
                    } else {
                        ret = do_read_lln(va_arg(args, long long int *), max_len);
                    }
                    break;
                }
                break;
            }
            if (ret)
                RETURN();
            break;
        }
    }

    // impossible to reach here
    assert(0);

#undef RETURN
}

void myprintf(char *fmt, ...)
{
    //____qcodep____

    out_idx = 0;
}

int main()
{ // main函数的代码都不需要管，只需实现myscanf和myprintf函数即可。
    int n, m;
    scanf("%d.%d\n", &n, &m);
    if (n == 1) {
        if (m == 1) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i);
            myprintf(out_fmt, i);
            puts(out_buf);
        } else if (m == 2) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &c);
            myprintf(out_fmt, c);
            puts(out_buf);
        } else if (m == 3) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str);
            myprintf(out_fmt, str);
            puts(out_buf);
        } else if (m == 4) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f);
            myprintf(out_fmt, f);
            puts(out_buf);
        }
    } else if (n == 2) {
        if (m == 1) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i);
            myprintf(out_fmt, i);
            puts(out_buf);
        } else if (m == 2) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f);
            myprintf(out_fmt, f);
            puts(out_buf);
        } else if (m == 3) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str);
            myprintf(out_fmt, str);
            puts(out_buf);
        }
    } else if (n == 3) {
        if (m == 1) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str, &i, &c);
            myprintf(out_fmt, str, i, c);
            puts(out_buf);
        } else if (m == 2) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &i, &c);
            myprintf(out_fmt, i, c);
            puts(out_buf);
        }
    } else {
        if (m == 1) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, str, &i, &c);
            myprintf(out_fmt, str, i, c);
            puts(out_buf);
        } else if (m == 2) {
            gets(in_fmt);
            gets(out_fmt);
            gets(in_buf);
            myscanf(in_fmt, &f);
            myprintf(out_fmt, f);
            puts(out_buf);
        }
    }
    return 0;
}