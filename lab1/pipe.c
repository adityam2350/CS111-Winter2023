#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char *argv[])
{
  int fd[2];
  int prev_fd_read;
  int status;
  if (argc==1)
  {
    return EINVAL;
  }
  for (int i=1;i<argc;i++)
   { 
     if (i<argc-1)
     {
       pipe(fd);
     }
     printf("The read end of the pipe: %d\n",fd[0]);
     printf("The write end of the pipe: %d\n",fd[1]);
     printf("The prev_read: %d\n",prev_fd_read);
     int t = fork();
     if (t==0)
     {
       
       if(i<argc-1)
       {
	 //Manages reading outputting the to the write end of the pipe
	 dup2(fd[1],1);
	 close(fd[0]);
	 close(fd[1]);
       }
       if (i>1)
       {
	 //Manages redirecting standard input to the read end of the pipe
	 dup2(prev_fd_read,0);
	 close(prev_fd_read);
       }
      execlp(argv[i],argv[i],NULL);
      //error handler for child processes
      return errno;
     }
     else if (t>0)
     {
       //Error handler for parent process
       int w_error=waitpid(t,&status,0);
       if (w_error==-1)
       {
	 return errno;
       }
       if(!WIFEXITED(status))
       {
	 return ECHILD;
       }
       else
       {
	 if (WEXITSTATUS(status)!=0)
	 {
	   return WEXITSTATUS(status);
	 }
       }
       //Ensure that everything closes properly in parent process
       if (i<argc-1)
       {
	 close(fd[1]);
       }
       if (i>1)
       {
	 close(prev_fd_read);
       }
       prev_fd_read=fd[0];
     }
     else
     {
       exit(ECHILD);
       return ECHILD;
     }
     
   }
  return 0;
}
