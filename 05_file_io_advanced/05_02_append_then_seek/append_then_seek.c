#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]){
    int fd;
    int opt;
    int flags = O_WRONLY | O_CREAT;
    while((opt = getopt(argc, argv, "a")) != -1){
        switch(opt){
            case 'a':
                flags |= O_APPEND;
                break;
            default:
                break;
        }
    }
    fd = open(argv[2], flags, S_IRUSR | S_IWUSR); 
    if(fd < 0){
        perror("open fail");
        return -1;
    }

    char* buf = "Michael Kerrisk has not only written a great book about Linux programming\n "
                "and how it relates to various standards, but has also taken care that bugs he\n "
                "noticed got fixed and the man pages were (greatly) improved. In all three\n "
                "ways, he has made Linux programming easier. The in-depth treatment of\n "
                "topics in The Linux Programming Interface . . . makes it a must-have reference\n "
                "for both new and experienced Linux programmers.\n\n\n\n";

    ssize_t bytes_write = write(fd, buf, strlen(buf));
    if(bytes_write != strlen(buf)){
        perror("write fail");
        close(fd);
        return -1;
    }
    off_t offset = lseek(fd, 10, SEEK_SET);
    
    char* newbuf = "When a file is opened with the O_APPEND flag, the operating system ensures that all\n "
                "write operations append data to the end of the file, regardless of the current file offset.";

    bytes_write = write(fd, newbuf, strlen(newbuf));
    if(bytes_write != strlen(newbuf)){
        perror("write fail");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}