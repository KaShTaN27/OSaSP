#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "dirent.h"
#include "sys/stat.h"
#include "errno.h"
#include "limits.h"

int seenFiles = 0;

int checkDirectory(char *name, int min, int max, FILE* file) {
    DIR *directory = opendir(name);

    if (directory == NULL) {
        perror("Error during opening directory");
        return -1;
    }

    int nameLength = (int) strlen(name);
    struct stat fileStat;
    struct dirent *dirent = readdir(directory);
    while (dirent != NULL) {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            dirent = readdir(directory);
            continue;
        }
        name[nameLength] = '/';
        name[nameLength + 1] = '\0';
        strcat(name, dirent->d_name);
        if (lstat(name, &fileStat)) {
            perror("Error during getting info of file");
            dirent = readdir(directory);
            continue;
        }
        if (S_ISDIR(fileStat.st_mode)) {
            checkDirectory(name, min, max, file);
        } else {
            seenFiles++;
            if (fileStat.st_size >= min && fileStat.st_size <= max) {
                fprintf(file, "Path: %s\nName: %s\nSize: %ld\n\n", name, dirent->d_name, fileStat.st_size);
            }
        }

        dirent = readdir(directory);
    }
    if (closedir(directory)) {
        perror("Error during closing directory");
        return -1;
    }

    return 0;
}

long stringToLong(char *num) {
    char *endptr;
    long res = strtol(num, &endptr, 10);

    if ((errno == ERANGE && (res == LONG_MAX || res == LONG_MIN))
        || (errno != 0 && res == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == num) {
        fprintf(stderr, "No digits were found\n");
        exit(EXIT_FAILURE);
    }
    return res;
}

int main(int argc, char *argv[]) {

    if (argc != 5) {
        perror("Unexpected number of parameters");
        return -1;
    }

    long min = stringToLong(argv[2]);
    long max = stringToLong(argv[3]);

    FILE* file = fopen(argv[4], "w");
    if (file == NULL) {
        perror("Error during opening file");
        return -1;
    }

    char *buffer = (char *) malloc(PATH_MAX * sizeof(char));
    strcpy(buffer, argv[1]);

    checkDirectory(buffer, min, max, file);

    printf("Seen files: %d", seenFiles);

    if (fclose(file)) {
        perror("Error during closing file");
        return -1;
    }
}