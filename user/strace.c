#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 3) {
    fprintf(2, "Uso: strace mascara comando [argumentos...]\n");
    exit(1);
  }

  if(trace(atoi(argv[1])) < 0) {
    fprintf(2, "strace: error al activar trace\n");
    exit(1);
  }

  exec(argv[2], &argv[2]);

  fprintf(2, "strace: no se pudo ejecutar el comando\n");
  exit(1);
}

