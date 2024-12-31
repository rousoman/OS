#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    FILE *file;
    pid_t pid;

    // Open file for writing
    const char *filename = "output.txt";
    file = fopen(filename, "w");
    if (!file) 
    {
        fprintf(stderr, "Failed to open file '%s'", filename);
        return EXIT_FAILURE;
    }

    pid = fork();

    if (pid < 0)  // Fork failed
    {
        fprintf(stderr, "Fork failed\n");
        fclose(file);
        return EXIT_FAILURE;
    } 
    else if (pid == 0)  // Child process
    {
        fprintf(file, "Child process: PID = %d\n", getpid());
    } 
    else  // Parent process
    {
        fprintf(file, "Parent process: PID = %d\n", getpid());
    }

    fclose(file); // Close file
    return 0;
}

