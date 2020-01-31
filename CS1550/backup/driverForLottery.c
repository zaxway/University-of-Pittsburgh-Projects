#include "proc.c"
#include "pstat.h"
#include "param.h"
#include "stat.h"
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  settickets(30);
  int pid = fork();
  if (pid == 0) {
    while(1);
  }

  settickets(20);
  pid = fork();
  if (pid == 0) {
    while(1);
  }

  settickets(10);
  pid = fork();
  if (pid == 0) {
    while(1);
  }
    
    int i;
  while(1) {
    struct pstat stat;
    getpinfo(&stat);
    for (i = 0; i < NPROC; i++) {
      if (stat.inuse[i] == 1) {
        printf(0, "PID: %d, Tickets: %d, Ticks: %d",stat.pid[i], stat.tickets[i], stat.ticks[i]);
      }
    }
  }
    printf(0, "\n");
  exit();
  return 0;

}
