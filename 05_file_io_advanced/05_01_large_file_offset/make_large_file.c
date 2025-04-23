#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    int fd;
    uint64_t filesize = 5ULL * 1024 * 1024 * 1024;
    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd < 0){
        perror("open fail");
        exit(EXIT_FAILURE);
    }
    off_t offset = lseek(fd, filesize, SEEK_SET);
    if(offset == -1){
        perror("lseek fail");
        close(fd);
        exit(EXIT_FAILURE);
    }
    ssize_t bytes_write = write(fd, "hello", sizeof("hello"));
    if(bytes_write != sizeof("hello")){
        perror("write fail");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}