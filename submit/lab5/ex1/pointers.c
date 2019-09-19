#include <stdio.h>

int main() {
  char cs[] = { 'a', 'b', 'c', 'd', 'e' };
  char *cp = cs;
  for (int i = 0; i < sizeof(cs)/sizeof(cs[0]); i++) {
    printf("char pointer cp = %p, pointing at char %c\n", cp, *cp);
    cp++;
  }

  int is[] = { 1, 2, 3, 4, 5 };
  int *ip = is;
  for (int i = 0; i < sizeof(is)/sizeof(is[0]); i++) {
    printf("int pointer ip = %p, pointing at int %d\n", ip, *ip);
    ip++;
  }
  return 0;
}
