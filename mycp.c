#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> /* defines types used by sys/stat.h */  
#include <sys/stat.h> /* defines S_IREAD & S_IWRITE */  


int main(int argc, char* argv[]) {
    if(argc != 3) {
        write(1, "Expected 2 arguments, the source file, followed by the destination\n", 70);
        return 1;
    }

    int fd_source = open(argv[1], O_RDONLY);
    if(fd_source == -1) {
        write(1, "Can't find the source file with the given name, sorry.\n", 50);
        return 1;
    }

    // When cp command has to create the dest file, it gives it the same permissions as the source.
    // So this program must do the same.
    struct stat res;
    if(fstat(fd_source, &res) == -1) return 1;
    mode_t permission_bits = res.st_mode; //permissions of the source file
    int fd_dest = open(argv[2], O_WRONLY | O_CREAT, permission_bits);
    if(fd_dest == -1) {
        write(1, "Can't open or create the destination file with the given name, sorry.\n", 70);
        return 1;
    }

    char line[100000] = "";
    int read_count;
    while((read_count = read(fd_source, line, 100000)) > 0) {
        write(fd_dest, line, read_count);
    }
    close(fd_source);
    close(fd_dest);
    return 0;
}
