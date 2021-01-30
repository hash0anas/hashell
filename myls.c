#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char* argv[]) {
	if(argc < 1) return 1;

    struct dirent **file_list;
    int count = scandir(".", &file_list, NULL, alphasort); 
	assert(count >= 0);

    for(int i = 2; i < count; ++i) { // From 2 to skip the parent and the current dirs.
        printf("%s  ", file_list[i]->d_name); 
        free(file_list[i]); 
    }
    puts("");
    free(file_list); 
	return 0; 
}
