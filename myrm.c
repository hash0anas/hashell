#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        puts("Not enough argmuents. Run man rm for more details.");
        return 1;
    }
    int rv = remove(argv[1]);
    if(rv == -1) {
        puts("Can't remove file for some reason.");
        return 1;
    }
    return 0;
}
