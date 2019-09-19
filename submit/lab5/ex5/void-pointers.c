#include <stdio.h>

int main() {
  char cs[] = { 'a', 'b', 'c', 'd', 'e' };
  int is[] = { 1, 2, 3, 4, 5 };
  void *p = cs;
  for (int i = 0; i < sizeof(cs)/sizeof(cs[0]); i++) {
    printf("void pointer p = %p, pointing at char %c\n", p, *(char *)p);
    p = (char *)p + 1;
  }
  p = is;
  for (int i = 0; i < sizeof(is)/sizeof(is[0]); i++) {
    printf("void pointer p = %p, pointing at int %d\n", p, *(int *)p);
    p = (int *)p + 1;
  }
  return 0;
}
