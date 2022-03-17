#include "stdio.h"
#include "sys/stat.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        perror("Unexpected number of parameters");
        return -1;
    }

    FILE *inputFile, *outputFile;
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    if (inputFile == NULL) {
        perror("Error with opening input file");
        return -1;
    }
    if (outputFile == NULL) {
        perror("Error with opening output file");
        return -1;
    }

    char symbol = (char) fgetc(inputFile);
    while (symbol != EOF) {
        fputc(symbol, outputFile);
        symbol = (char) fgetc(inputFile);
    }

    struct stat fileStat;
    stat(argv[1], &fileStat);
    chmod(argv[2], fileStat.st_mode);

    if (fclose(inputFile)) {
        perror("Error during closing input file");
        return -1;
    }

    if (fclose(outputFile)) {
        perror("Error during closing output file");
        return -1;
    }
}
