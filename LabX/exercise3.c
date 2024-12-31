#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int sig) 
{
    printf("Child process received signal %d from parent\n", sig);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) 
{
    pid_t pid;

    pid = fork();

    if (pid < 0)  // Fork failed
    {
        fprintf(stderr, "Fork failed\n");
        return EXIT_FAILURE;
    } 
    else if (pid == 0)  // Child process
    {
        signal(SIGUSR1, signal_handler); // Set up signal handler
        while (1)
        {
            printf("Child process: PID = %d, waiting for signal...\n", getpid());
            sleep(1);
        }
    } 
    else  // Parent process
    {
        sleep(5); // Give the child process time to set up the signal handler
        printf("Parent process: PID = %d, sending signal to child (PID = %d)\n", getpid(), pid);
        kill(pid, SIGUSR1); // Send signal to child
    }

    return EXIT_SUCCESS;
}

