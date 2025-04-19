#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int is_all_zero(char *buf, ssize_t size) {
    for (ssize_t i = 0; i < size; i++) {
        if (buf[i] != 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){
    char buf[4096];
    ssize_t bytes_read;
    mode_t filePerms;

    int src_fd = open(argv[1], O_RDONLY);
    if(src_fd < 0){
        perror("open source file fail");
        exit(EXIT_FAILURE);
    }

    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    int dest_fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, filePerms);

    if(dest_fd < 0){
        perror("open destination file fail");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    while((bytes_read = read(src_fd, buf, 4096)) > 0){
        if(is_all_zero(buf, bytes_read)){
            off_t offset = lseek(dest_fd, bytes_read, SEEK_CUR);
            if(offset == -1){
                perror("lseek");
                break;
            }
        }
        else{
            ssize_t bytes_write = write(dest_fd, buf, bytes_read);
            if(bytes_write != bytes_read){
                perror("write fail");
                break;
            }
        }
    }
    close(src_fd);
    close(dest_fd);
    return 0;
}