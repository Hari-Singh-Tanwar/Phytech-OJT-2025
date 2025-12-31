#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS ---
        printf("Child (PID: %d): I am going to become 'ls -l' now!\n", getpid());
        
        // execlp(program, arg0, arg1, ..., NULL);
        // "ls" is the program name.
        // "ls" (again) is argv[0] (convention).
        // "-l" is the argument.
        // NULL marks the end of arguments.
        execlp("ls", "ls", "-l", NULL);

        // !!! IF WE REACH HERE, EXEC FAILED !!!
        // Because exec replaces the code, these lines never run if exec succeeds.
        perror("Exec failed");
        exit(1);
    } 
    else {
        // --- PARENT PROCESS ---
        printf("Parent (PID: %d): Waiting for child...\n", getpid());
        wait(NULL); // Wait for the child (which is now 'ls') to finish
        printf("Parent: Child finished.\n");
    }

    return 0;
}
