#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    int fd[2];
    // fd[0] -> reading port
    // fd[1] -> writing port
    if (pipe(fd) == -1)
    {
        fprintf(stderr, "An error occured with opening the pipe\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "An error occured with fork\n");
        return EXIT_FAILURE;
    }
    else if (pid == 0)  // Child process
    {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            fprintf(stderr, "An error occured with reading from the pipe port %d\n", fd[0]);
        }
        close(fd[0]);

        printf("Child process got from parent process: %d\n", y);
    }
    else  // Parent process
    {
        close(fd[0]);
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            fprintf(stderr, "An error occured with writing to the pipe port %d\n", fd[1]);
            return EXIT_FAILURE;
        }
        close(fd[1]);
    }
    return EXIT_SUCCESS;
}

