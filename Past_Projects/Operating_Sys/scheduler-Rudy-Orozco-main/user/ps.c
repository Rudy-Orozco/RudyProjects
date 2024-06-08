#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    struct pstat pst;

    setTickets(10);
    setColor(INDIGO);
    getpinfo(&pst);

    static char *states[] = {
    [UNUSED]    "unused",
    [USED]      "used",
    [SLEEPING]  "sleep ",
    [RUNNABLE]  "runble",
    [RUNNING]   "run   ",
    [ZOMBIE]    "zombie"
    };

    static char *color[] = {
    [RED]   "RED",
    [ORANGE] "ORANGE",
    [YELLOW] "YELLOW",
    [GREEN] "GREEN",
    [BLUE] "BLUE",
    [INDIGO] "INDIGO",
    [VIOLET] "VIOLET"
    };

    printf("NAME    |PID    |STATUS |COLOR  |TICKETS\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < NPROC; i++)
    {   
        if(pst.state[i] != UNUSED)
        {
            printf("%s\t", pst.name[i]);
            printf("|%d\t", pst.pid[i]);
            printf("|%s\t", states[pst.state[i]]);
            printf("|%s\t", color[pst.color[i]]);
            printf("|%d\t", pst.tickets[i]);
            printf("\n");
        }
    }
    return 0;
}