#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("%s\n", getcwd((char*)NULL, 1024));
}
