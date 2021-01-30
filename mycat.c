#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> /* defines types used by sys/stat.h */  
#include <sys/stat.h> /* defines S_IREAD & S_IWRITE */  


int main(int argc, char* argv[]) {
    if(argc != 2) {
        puts("Expected 1 argument, only the file name");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        write(1, "Can't find the file with the given name, sorry.\n", 50);
        return 1;
    }
    char line[1000] = "";
    int read_count;
    while((read_count = read(fd, line, 1000)) > 0) {
        write(1, line, read_count);
    }
    close(fd);
    return 0;
}
