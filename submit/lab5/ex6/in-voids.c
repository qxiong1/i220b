#include <stdio.h>

typedef struct {
  const char *exp;
  void *p;
} ExpPointer;

int main() {

  char cs[] = { 'a', 'b', 'c', 'd', 'e' };
  int is[] = { 1, 2, 3, 4, 5 };
  ExpPointer questions[] = {
    { "is[2]", &is[2] },
    { "cs[3]", &cs[3] },
    { "is[4]", &is[4] },
    { "cs[1]", &cs[1] },
    { "cs[4]", &cs[4] },
    { "is[1]", &is[1] },
  };
  for (int i = 0;
       !feof(stdin) && i < sizeof(questions)/sizeof(questions[0]);
       i++) {
    ExpPointer q = questions[i];
    int isOk = 0;
    do {
      printf("cs[] is at %p; is[] is at %p\n", cs, is);
      printf("enter pointer to %s: ", q.exp);
      fflush(stdout);
      void *p;
      int nOk = scanf("%p", &p);
      if (nOk == 1) {
        isOk = (p == q.p);
        printf("%s\n", isOk ? "ok" : "not ok");
      }
      else if (nOk == EOF) {
        break;
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
