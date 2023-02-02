#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char *argv[])
{
  int* pid_array;
  pid_array=(int *)malloc((argc-1)*sizeof(int));
  if (pid_array==NULL)
  {
    return errno;
  }
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
      printf("Errno: %d\n",errno);
      return errno;
     }
     else if (t>0)
     {
       
       pid_array[i-1]=t;
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
       return ECHILD;
     }
     
   }
  for (int i=0;i<argc-1;i++)
  {
       int w_error=waitpid(pid_array[i],&status,0);
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
  }
  return 0;
}
