#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "types.h"
#include "param.h"

struct pstat {
  int inuse[NPROC];
  int pid[NPROC];
  int ppid[NPROC];
  int state[NPROC];
  uint64 sz[NPROC];
  uint64 rtime[NPROC];
  uint64 syscalls[NPROC];
  char name[NPROC][16];
};

#endif
