#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


void redirect(char* input[], char* output)

{
  int fds[2];
  int count;
  int fd;
  pid_t pid1,pid2;
  char c;
  pipe (fds); // create a pipe and handover to children 
  if ((pid1=fork()) < 0) {
    perror("fork failed:");
    exit(1);
  }
  if (pid1==0) {//code for child 1 starts
    dup2(fds[1],1);// Child 1 connects stdout to upstream end of pipe and
    close(fds[0]);// closes the downstream end of the pipe
    //execlp("more", "more", "myfile.txt",NULL);
    execvp(input[0], input);
  }//code for child 1 ends

  if ((pid2=fork())<0){
    perror("fork failed:");
    exit(2);

  }

  if (pid2==0){ //code for child 2 starts
    fd=open(output,O_RDWR|O_CREAT,0600);
    dup2(fds[0],0); // Child 2 connects stdin to downstream end of pipe and
    close(fds[1]);// closes the upstream end of the pipe
    while ((count=read(0,&c,1))>0) 
      write(fd,&c,1);
    close(fd);
  } //code for child 2 ends
  else {//parent code starts
    close(fds[0]); //parent closes one end of the pipe
    close(fds[1]); //parent closes the other end of the pipe
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
  }//parent code ends
}
