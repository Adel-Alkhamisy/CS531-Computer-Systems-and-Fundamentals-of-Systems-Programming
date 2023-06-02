//
//  main.c
//  CS531_HW4_Final_Version
//
//  Created by ADEL ALKHAMISY on 10/21/22.
//


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
int cs531_system(const char *s);

int main(int argc, char *argv[]){
            int status;
            status=cs531_system(argv[1]);
            printf("\n parent process is sleeping!!! \n");
            sleep(10);
            return status;}



int cs531_system(const char *comm){
            pid_t child_process,status2;
            void (*previously_installed_handler)(int);
            int status, terminal;
            // if child_process==0 then we are in the child process
            child_process = fork();
            if (child_process == 0){//terminal redirection
            terminal = open("/dev/tty",O_RDWR);
                close(1);
                dup(terminal);
                close(2);
                dup(terminal);
                close(terminal);
                signal(SIGINT,SIG_DFL);
                /*replace current process image with new process image. In other words, implement commands.*/
                execlp("sh", "sh", "-c",comm,(char *)0);
            if (child_process == -1){
                // This means that the fork() failed!
                perror("fork_error");
                exit(EXIT_FAILURE);
            }
            //Otherwise, Parent process if the number is positive +ve
            else{
                previously_installed_handler=signal(SIGINT, SIG_IGN);
            do{//child status information
                    status2 = waitpid(child_process, &status, WUNTRACED | WCONTINUED);
                    if (status2 == -1){
                    perror("waitpid_error");
                    exit(EXIT_FAILURE);}
                    //check who stopped the child
                    if (WIFSTOPPED(status)){
                    printf("stopped by =%d\n", WSTOPSIG(status));
                        //printf()
                    }
                    //check exist status of child
                    else if(WIFEXITED(status))
                        printf(" exist status of child=%d\n", WEXITSTATUS(status));
                   
                    // The status field if case of terminiation
                    else if (WIFSIGNALED(status))
                        printf("killed by %d\n", WTERMSIG(status));
                    // The status field if case of continuation
                    else if (WIFCONTINUED(status))
                        printf("continue\n");
                }
                while (!WIFEXITED(status) && !WIFSIGNALED(status));
               signal(SIGINT,previously_installed_handler);
            }

            }
            return -1;}

