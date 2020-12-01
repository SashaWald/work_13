#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

static void signal_handler(int signo){
    if (signo == SIGINT){
        printf("Program exited due to SIGINT\n");
        int i = open("signal.out", O_APPEND | O_WRONLY | O_CREAT, 0644);
        char exit_message[] = "Program exited due to SIGINT\n";
        write(i,exit_message,strlen(exit_message));
        close(i);
        exit(0);
    }
    if (signo == SIGUSR1){
        printf("PPID: \t%d\n",getppid());
    }
}
int main(){
    signal(SIGINT, signal_handler);
    signal(SIGUSR1, signal_handler);
    while(1){
        printf("PID: \t%d\n",getpid());
        sleep(1);
    }
}