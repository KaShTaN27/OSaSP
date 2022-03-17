#include "stdio.h"
#include "dirent.h"

int readDirectories(char *name) {
    DIR *directory = opendir(name);
    if (directory == NULL) {
        perror("Error during opening directory");
        return -1;
    }

    struct dirent *dirent = readdir(directory);
    while (dirent != NULL) {
        printf("%s\n", dirent->d_name);
        dirent = readdir(directory);
    }

    if (closedir(directory)) {
        perror("Error during closing directory");
        return -1;
    }

    return 0;
}

int main() {
    printf("Directory / :\n-------------\n");
    readDirectories("/");
    printf("\n\nDirectory ./ :\n--------------\n");
    readDirectories("./");
}
