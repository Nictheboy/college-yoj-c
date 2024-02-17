#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  if (n <= 0)
    return 0;
  for (int i = 0; i < n - 1; i++) {
    printf("hello world\n");
  }
  printf("hello world");
  return 0;
}
