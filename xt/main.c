#include <stdio.h>
#include <proc.h>
#include <signal.h>

extern void xmain();
extern void handler();

struct xentry xtab[10]; 
int currxid = 0; 

void main(int argc, char *argv[])
{
   register struct xentry *xptr;
   struct xentry m;
   int i;
   int xidxmain;

   for(i=0 ; i < NPROC; i++){
      xptr = &xtab[i];
      xptr->xid = i;
      xptr->xlimit =  (WORD) malloc(STKSIZE);
      xptr->xbase = xptr->xlimit + STKSIZE - sizeof(WORD);
      xptr->xstate = XFREE;
   }

   /* the first thread runs user's xmain with id 0*/
   xidxmain = xthread_create(xmain, 2, argc, argv);
   xtab[xidxmain].xstate = XRUN;
   signal(SIGALRM,handler);//
   ualarm(20000,0); //
   ctxsw(m.xregs, xtab[xidxmain].xregs);
   /* never be here */
}


