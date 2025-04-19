#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    int opt = 0;
    bool append_mode = false;
    int open_flags = O_WRONLY | O_CREAT;
    char buf[4096];
    ssize_t numRead;

    while((opt = getopt(argc, argv, "a")) != -1){
        switch (opt){
            case 'a':
                printf("APPEND Mode\n");
                append_mode = true;
                break;
            default:
                dprintf(STDERR_FILENO, "Usage: %s [-a] <file>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }    

    open_flags |= append_mode ? O_APPEND : O_TRUNC;
    int fd = open(argv[optind], open_flags, 0644);

    while((numRead = read(STDIN_FILENO, buf, 4096)) > 0){
        int numWrite = write(STDOUT_FILENO, buf, numRead);
        if(numWrite != numRead){
            exit(EXIT_FAILURE);
        }
        numWrite = write(fd, buf, numRead);
        if(numWrite != numRead){
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
    return 0;
}