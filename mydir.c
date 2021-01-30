#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        puts("Expecting one argument, the dir name");
    }
    mkdir(argv[1], 0777);
}
