#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int flags = O_RDWR | O_CREAT;
    int byteSize = atoi(argv[2]);
    int write_bytes = 0;
    char *buf = "*";
    if(argv[3] == "&"){
        flags |= O_APPEND;
        strcpy(buf, "a");
    }
    int fd = open(argv[1], flags, 0644);
    for(long i = 0; i < byteSize; i++){
        write(fd, buf, 1);
    }
    return 0;
}