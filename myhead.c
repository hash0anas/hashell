#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        write(1, "Expecting one argument, no more, no less.\n", 50);
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        write(1, "Make sure the file does exist.\n", 50);
        return 1;
    }
    
    char buff[100000], out[100000];
    int len = read(fd, buff, sizeof(buff)), newlines_count = 0, i;
    for(i = 0; i < len && newlines_count < 10; ++i) {
        out[i] = buff[i];
        if(buff[i] == '\n') ++newlines_count;
    }
    out[i] = '\0';
    write(1, out, i+1);
    close(fd);
    return 0;
}
