#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info;

  if(sysinfo(&info) < 0){
    fprintf(2, "sysstat: fallo al obtener informacion del sistema\n");
    exit(1);
  }

  uint64 usedmem = info.totalmem - info.freemem;
  uint64 pct_used = (usedmem * 100) / info.totalmem;

  printf("=== Estadisticas del Sistema (xv6) ===\n");
  printf("Memoria total:    %lu bytes (%lu MB)\n", info.totalmem, info.totalmem / (1024 * 1024));
  printf("Memoria libre:    %lu bytes (%lu MB)\n", info.freemem, info.freemem / (1024 * 1024));
  printf("Memoria usada:    %lu bytes (%lu%%)\n", usedmem, pct_used);
  printf("Paginas libres:   %lu\n", info.freepages);
  printf("Procesos activos: %lu\n", info.nproc);

  exit(0);
}
