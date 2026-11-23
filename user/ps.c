#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

static struct pstat st;

static char *states[] = {
  [0] "UNUSED",
  [1] "USED",
  [2] "SLEEPING",
  [3] "RUNNABLE",
  [4] "RUNNING",
  [5] "ZOMBIE"
};

int
main(int argc, char *argv[])
{
  if(getprocinfo(&st) < 0){
    fprintf(2, "ps: error al obtener procesos\n");
    exit(1);
  }

  printf("PID\tPPID\tESTADO\t\tMEM(B)\tTICKS\tSYSCALLS\tNOMBRE\n");
  for(int i = 0; i < NPROC; i++){
    if(st.inuse[i]){
      char *s = (st.state[i] >= 0 && st.state[i] <= 5) ? states[st.state[i]] : "?";
      printf("%d\t%d\t%s\t%lu\t%lu\t%lu\t\t%s\n",
             st.pid[i], st.ppid[i], s, st.sz[i],
             st.rtime[i], st.syscalls[i], st.name[i]);
    }
  }
  exit(0);
}
