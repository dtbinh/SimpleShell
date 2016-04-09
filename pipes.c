#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

// Add parameters for knowing which command to pipe into the other
void pipe_output(char* command1[], char* command2[]){
  int fds[2];
  pid_t id1,id2;
  pipe (fds);
  if ((id1 =fork())< 0){
    perror("fork failed:");
    exit(1);
  }
  if (id1==0){
    dup2(fds[0],0);
    close(fds[1]);
    // Execure the second command using the pipe file descriptor as the input
    execvp(command2[0], command2);
  }
  if ((id2 =fork())< 0){
    perror("fork failed:");
    exit(2);
  }

  if (id2 == 0) {
    dup2(fds[1],1);
    close(fds[0]);
    // Execure the first command using the pipe file descriptor as the output
    execvp(command1[0], command1);
  }

  else {
    close(fds[0]);
    close(fds[1]);
    waitpid(id1,NULL,0);
    waitpid(id2,NULL,0);
  }
}
