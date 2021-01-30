#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        write(1, "Expecting one argument, the file name.\n", 50);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    int size = ftell(file), nl_count = 0;
    while(size && nl_count < 10) {
        fseek(file, --size, SEEK_SET);
        nl_count += fgetc(file) == '\n';
    }
    
    char buf[256];
    while(fgets(buf, sizeof(buf), file)){
        printf("%s", buf);
    }
    puts("");
    return 0;
}
