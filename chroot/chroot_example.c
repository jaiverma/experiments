#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// python is installed in the chroot environment
// testint if chroot is active by running and returning output
// of 'python -c "print(42)"'

int main() {
    pid_t pid = 0;
    int pipefd[2];
    FILE *output;
    char line[256];
    int status;

    if (pipe(pipefd) < 0) {
        printf("Failed to create a pipe to communicate with process inside chroot\n");
        exit(1);
    }

    pid = fork();
    if (pid == 0) {
        printf("inside fork\n");
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        
        chdir("/mnt/ccc/xenial");
        if (chroot("/mnt/ccc/xenial") != 0) {
            printf("Couldn't chroot to /mnt/ccc/xenial\n");
            exit(1);
        }

        const char *env[] = { "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$PATH", (char *)0 };
        execle("/bin/bash", "/bin/bash", "-c", "/root/run.sh", (char *)0, env);
        printf("execle failed\n");
        perror("exec");
        exit(1); // stop child process if execle fails
    }
    else {
        printf("inside parent\n");
        close(pipefd[1]);
        output = fdopen(pipefd[0], "r");

        while (fgets(line, sizeof(line), output)) {
            printf("output from chroot: %s\n", line);
        }

        waitpid(pid, &status, 0);
        printf("Child exit status : %d\n", WEXITSTATUS(status)); 
        fclose(output);
        return 0;
    }
}
