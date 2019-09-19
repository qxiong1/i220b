#include <stdio.h>

int main() {
  enum { N = 5 };

  int is[N];
  int indexes[] = { 1, 3, 2, 4, 0, 3 };
  for (int i = 0; i < sizeof(indexes)/sizeof(indexes[0]); i++) {
    int n = indexes[i];
    int isOk = 0;
    do {
      printf("is[] is at %p\n", is);
      printf("enter pointer to is[%d]: ", n);
      fflush(stdout);
      int *p;
      if (scanf("%p", &p) == 1) {
        isOk = (*p == is[n]);
        printf("%s\n", isOk ? "ok" : "not ok");
      }
      else {
        printf("bad input: enter hex pointer value\n");
      }
      int c = getchar();
      while (c != '\n' && c != EOF) { //waste line
        c = getchar();
      }
    } while (!isOk);
  }
  return 0;
}
