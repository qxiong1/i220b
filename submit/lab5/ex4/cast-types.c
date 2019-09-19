#include <stdio.h>

int main() {
  char cs[] = { 'a', 'b', 'c', 'd', 'e' };
  int is[] = { 1, 2, 3, 4, 5 };
  char *cp = (char *)is;
  int *ip = (int *)cs;
  for (int i = 0; i < sizeof(cs)/sizeof(cs[0]); i++) {
    printf("char pointer cp = %p, pointing at int %d (0x%x)\n",
           cp, *cp, *cp);
    cp = (char *)(((int *)cp) + 1);
  }
  for (int i = 0; i < sizeof(is)/sizeof(is[0]); i++) {
    printf("int pointer ip = %p, pointing at char '%c' (0x%x)\n", ip, *ip, *ip);
    ip = (int *)(((char *)ip) + 1);
  }
  return 0;
}
