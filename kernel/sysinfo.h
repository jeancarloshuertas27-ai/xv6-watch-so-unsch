#ifndef SYSINFO_H
#define SYSINFO_H

#include "types.h"

struct sysinfo {
  uint64 freemem;
  uint64 totalmem;
  uint64 freepages;
  uint64 nproc;
};

#endif
