#include <stdio.h>

int main() {
  while (1) {
    int i;
    if (scanf("%x", &i) != 1) break;
    printf("%d %s -%d\n", i, (i == -i) ? "==" : "!=", i);
  }
  return 0;
}
