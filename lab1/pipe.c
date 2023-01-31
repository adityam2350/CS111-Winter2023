#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
  int fd[2];
  for (int i=1;i<argc;i++)
   {
     if (i!=argc-1)
     {
       pipe(fd);
     }
     int t = fork();
     if (t==0)
     {
       if(i!=argc-1)
       {
	 dup2(fd[1],1);
	 close(fd[0]);
	 close(fd[1]);
       }
       if (i!=1)
       {
	 dup2(fd[0],0);
	 close(fd[0]);
       }
       execlp(argv[i],argv[i],NULL);
       break;
     }
     else if (t>0)
     {
       close(fd[1]);
     }
     else
     {
       exit(3);
     }
     
   }
  return 0;
}
