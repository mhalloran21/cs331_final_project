#include <stdio.h>
#include "a.h"
#include "b.h"

int main() {
  int c = bar(foo(1));
  printf("c = %d\n", c);
  return 0;
}
