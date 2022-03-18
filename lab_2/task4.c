//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <errno.h>
//#include <limits.h>
//
//int main(int argc, char *argv[]) {
//    if (argc != 3) {
//        perror("Unexpected number of parameters.\nUsage: [file_name] [number_of_lines]");
//        return -1;
//    }
//
//    char *endptr;
//    long numLines = strtol(argv[2], &endptr, 10);
//
//    if ((errno == ERANGE && (numLines == LONG_MAX || numLines == LONG_MIN))
//        || (errno != 0 && numLines == 0)) {
//        perror("strtol");
//        exit(EXIT_FAILURE);
//    }
//
//    if (endptr == argv[2]) {
//        fprintf(stderr, "No digits were found\n");
//        exit(EXIT_FAILURE);
//    }
//
//    FILE* file;
//    file = fopen(argv[1], "r");
//    if (file == NULL) {
//        perror("Error during opening file");
//        return -1;
//    }
//
//    char symbol = (char) fgetc(file);
//    int lines = 0;
//    while (symbol != EOF) {
//        if (symbol == '\n') {
//            lines++;
//        }
//        if (lines == numLines && numLines != 0) {
//            getc(stdin);
//            lines = 0;
//        }
//        fputc(symbol, stdout);
//        symbol = (char) fgetc(file);
//    }
//
//    if (fclose(file)) {
//        perror("Error during closing file");
//        return -1;
//    }
//
//}
//
