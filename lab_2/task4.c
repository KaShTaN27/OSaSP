#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        perror("Unexpected number of parameters.\nUsage: <file_name> <number_of_lines>");
        return -1;
    }

    int numLines = atoi(argv[2]);
    if (numLines < 0) {
        perror("Error, please, enter an integer");
        return -1;
    }

    FILE* file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error during opening file");
        return -1;
    }

    char symbol = (char) fgetc(file);
    int lines = 0;
    while (symbol != EOF) {
        if (symbol == '\n') {
            lines++;
        }
        if (lines == numLines && numLines != 0)
            getc(stdin);
        fputc(symbol, stdout);
        symbol = (char) fgetc(file);
    }

    if (fclose(file)) {
        perror("Error during closing file");
        return -1;
    }

}

