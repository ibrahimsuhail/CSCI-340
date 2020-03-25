#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1


int main(int argc,char* argv[])
{
    char* time_arg[]={ "/bin/time","-1",NULL};
    // create time argument
    execlp(time_arg[0],time_arg[1]);
    // replace the calling process image with a new process image
    char* c = argv[1];
    // get the command from command line
    int fd[2];
    // you access the pipe through the file descriptor array
    // int fd[] filedescriptors: fd[0] is the read end of the pipe, and
    // fd[1] is the write end.
    pid_t pid;
    // parent process creates a pipe and then sends a fork() call
    // creating the child process
    
    clock_t parent_start = clock();
    // start parents timer
    
    // get parent's start time
    time_t current_time;
    char* c_time_string;
    current_time = time(NULL);
    c_time_string = ctime(&current_time);
    // stringify the parents starting time to place in the write message
    
    char write_msg [BUFFER_SIZE];
    strcpy(write_msg, c_time_string);
    // create write message and copy parents starting time into it
    char read_msg[BUFFER_SIZE];
    // message to read
    /* create pipe */
    if (pipe(fd) == -1) {
       fprintf(stderr,"Pipe failed");
    return 1;
    }
    /* fork a child process */
    clock_t parent_end = clock();
    // stop parent process' timer
    time_t end_time;
    char* end_time_string;
    end_time = time(NULL);
    end_time_string = ctime(&end_time);
    // get parents end time
    
    pid = fork();
     // fork a new process
     // clock_t child_starting = clock();
    
    time_t child_start;
    char* child_start_string;
    child_start = time(NULL);
    child_start_string = ctime(&child_start);
    // get child start time
    
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    if (pid > 0) { /* parent process */
    /* close the unused end of the pipe */
        close(fd[READ_END]);
    /* write to the pipe */
    write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
       /* close the write end of the pipe */
    close(fd[WRITE_END]);
    }
    else { /* child process */
      //  clock_t child_end = clock();
    /* close the unused end of the pipe */
        close(fd[WRITE_END]);
    /* read from the pipe */
    read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("child starting time: %s", child_start_string);
        printf("parent starting time: %s",read_msg);
        printf("parent ending time: %s", end_time_string);
        double elapsed = (double)(parent_end - parent_start)/ CLOCKS_PER_SEC;
        printf("Parent Time Elapsed = %f\n",elapsed);
        printf("command: %s \n",c);
        printf("child pid: %d\nparent pid: %d\n",getpid(),getppid());

       /* close the read end of the pipe */
    close(fd[READ_END]);
}
    
   
}
    
