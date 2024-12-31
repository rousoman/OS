#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int nprocs = 3;  // Number of processes created from parent process
    printf("Parent process: PID = %d\n", getpid());

    for (int i = 0; i < nprocs; i++) 
    {
        pid_t pid = fork();

        if (pid < 0)  // Fork failed
        {
            fprintf(stderr, "Fork failed");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0)  // Child process
        {
            printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);  // Ensure child process does not continue the loop
        }
    }

    // Parent process waits for child processes to complete
    // even though exit() is called inside the loop in order to
    // handle zombie processes
    for (int i = 0; i < nprocs; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}

