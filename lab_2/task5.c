#include "stdio.h"
#include "sys/stat.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Unexpected number of parameters\n");
        return -1;
    }

    FILE *inputFile, *outputFile;
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    if (inputFile == NULL) {
        fprintf(stderr, "Error with opening input file\n");
        return -1;
    }
    if (outputFile == NULL) {
        fprintf(stderr, "Error with opening input file\n");
        return -1;
    }

    char symbol = (char) fgetc(inputFile);
    while (symbol != EOF) {
        fputc(symbol, outputFile);
        symbol = (char) fgetc(inputFile);
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) == -1) {
        fprintf(stderr, "Error during reading information about file\n");
        return -1;
    }
    
    if (chmod(argv[2], fileStat.st_mode) == -1) {
        fprintf(stderr, "Error during changing access rights\n");
        return -1;
    }

    if (fclose(inputFile)) {
        fprintf(stderr, "Error during closing input file\n");
        return -1;
    }

    if (fclose(outputFile)) {
        fprintf(stderr, "Error during closing input file\n");
        return -1;
    }
}
