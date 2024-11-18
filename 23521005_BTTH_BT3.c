#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int loop_forever = 1;
void on_sigint(){
    printf("\ncount.sh has stoppped\n");
    loop_forever = 0;
} 
int main(){
    signal(SIGINT, on_sigint);
    printf("Welcome to IT007, I am 23521005!\n");
    __pid_t pid;
    pid = fork();
    if (pid > 0)
        {
        while(loop_forever){}
        wait(NULL);
        }
    if (pid == 0)
        {
        execl("./count.sh", "./count.sh", "120", NULL);
        }
    
    
    return 0;
}