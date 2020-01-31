//#include "user.h"
#include "types.h"
#include "stat.h"

#define PGSIZE 4096

int main(int argc, char* argv[]) {
  int j;
  int indexLength = 10*PGSIZE;
  int* arr = malloc(indexLength);
  for (j = 0; j < 10; j++) {
    arr[j] = j;
    cprintf("%d\n", arr[j]);
  }
  for (j = 10; j > 0; j--) {
    // Tests for LRU and FIFO
    cprintf("%d\n", arr[j]);
  }
  fork();
  return 0;
}
