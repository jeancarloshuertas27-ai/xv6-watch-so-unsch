// testwatch: suite de pruebas de xv6-Watch (Nivel 4).
// Uso: testwatch cpu | mem | fork | err | all
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

#ifdef HAVE_SYSINFO
#include "kernel/sysinfo.h"
int sysinfo(struct sysinfo *);
#endif

#define PAGINA 4096
#define PAGINAS_MEM 10
#define BYTES_MEM (PAGINAS_MEM * PAGINA)

static int
indice_propio(struct pstat *st)
{
  int pid = getpid();
  for (int i = 0; i < NPROC; i++)
    if (st->inuse[i] && st->pid[i] == pid)
      return i;
  return -1;
}

static uint64
rtime_propio(void)
{
  struct pstat st;

  if (getprocinfo(&st) < 0)
    return 0;
  int i = indice_propio(&st);
  return i < 0 ? 0 : st.rtime[i];
}

// CP-02: un hijo consume CPU y su rtime debe aumentar.
static void
caso_cpu(void)
{
  uint64 antes_padre = rtime_propio();
  int pid = fork();

  if (pid < 0) {
    printf("testwatch cpu: fork fallo\n");
    return;
  }
  if (pid == 0) {
    uint64 antes = rtime_propio();
    volatile uint64 suma = 0;

    for (uint64 i = 0; i < 50000000ULL; i++)
      suma += i;

    uint64 despues = rtime_propio();
    printf("testwatch cpu: hijo pid=%d rtime antes=%lu despues=%lu incremento=%lu\n",
           getpid(), antes, despues, despues - antes);
    exit(0);
  }
  wait(0);
  uint64 despues_padre = rtime_propio();
  printf("testwatch cpu: padre pid=%d rtime antes=%lu despues=%lu\n",
         getpid(), antes_padre, despues_padre);
}

// CP-03: sbrk(40960) y escritura de las 10 paginas; sysinfo debe reflejar el consumo.
static void
caso_mem(void)
{
#ifdef HAVE_SYSINFO
  struct sysinfo antes, despues;
  char *bloque;

  if (sysinfo(&antes) < 0) {
    printf("testwatch mem: sysinfo inicial fallo\n");
    return;
  }
  bloque = sbrk(BYTES_MEM);
  if (bloque == SBRK_ERROR) {
    printf("testwatch mem: sbrk(%d) fallo\n", BYTES_MEM);
    return;
  }
  for (int i = 0; i < BYTES_MEM; i += PAGINA)
    bloque[i] = 1;
  bloque[BYTES_MEM - 1] = 1;

  if (sysinfo(&despues) < 0) {
    printf("testwatch mem: sysinfo final fallo\n");
    return;
  }
  uint64 usado = antes.freemem - despues.freemem;
  printf("testwatch mem: pedidos=%d bytes (%d paginas) libres antes=%lu despues=%lu diferencia=%lu bytes (%lu paginas)\n",
         BYTES_MEM, PAGINAS_MEM, antes.freemem, despues.freemem,
         usado, usado / PAGINA);
#else
  printf("testwatch mem: omitido; sysinfo (Nivel 3) aun no esta integrado en main\n");
#endif
}

// CP-05 (parte): fork simple con PIDs de padre e hijo.
static void
caso_fork(void)
{
  int padre = getpid();
  int pid = fork();

  if (pid < 0) {
    printf("testwatch fork: fork fallo\n");
    return;
  }
  if (pid == 0) {
    printf("testwatch fork: hijo pid=%d padre=%d\n", getpid(), padre);
    exit(0);
  }
  wait(0);
  printf("testwatch fork: padre pid=%d hijo=%d\n", getpid(), pid);
}

// CP-06: punteros invalidos deben devolver -1 sin kernel panic.
static void
caso_err(void)
{
  int r1 = getprocinfo((struct pstat *)0);

#ifdef HAVE_SYSINFO
  int r2 = sysinfo((struct sysinfo *)0xffffffff);

  printf("testwatch err: getprocinfo(0)=%d sysinfo(0xffffffff)=%d\n", r1, r2);
  if (r1 == -1 && r2 == -1)
    printf("testwatch err: OK, punteros invalidos rechazados sin kernel panic\n");
  else
    printf("testwatch err: FALLO, se esperaba -1 en ambas llamadas\n");
#else
  printf("testwatch err: getprocinfo(0)=%d; sysinfo omitido (Nivel 3 no integrado)\n", r1);
#endif
}

static void
uso(void)
{
  printf("uso: testwatch cpu | mem | fork | err | all\n");
}

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    uso();
    exit(1);
  }

  if (strcmp(argv[1], "cpu") == 0)
    caso_cpu();
  else if (strcmp(argv[1], "mem") == 0)
    caso_mem();
  else if (strcmp(argv[1], "fork") == 0)
    caso_fork();
  else if (strcmp(argv[1], "err") == 0)
    caso_err();
  else if (strcmp(argv[1], "all") == 0) {
    caso_cpu();
    caso_mem();
    caso_fork();
    caso_err();
  } else {
    uso();
    exit(1);
  }

  exit(0);
}
