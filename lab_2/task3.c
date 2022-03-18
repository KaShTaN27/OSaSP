#include <stdio.h>
#define CTRL_F 6

int main(int argc, char *argv[]) {

    if (argc != 2) {
        perror("Unexpected number of parameters.");
        return -1;
    }

    FILE* file;
    file = (fopen(argv[1], "w"));
    if (file == NULL){
        perror("Error during opening file");
        return -1;
    }

    char symbol;
    symbol = (char) getc(stdin);
    while (symbol != CTRL_F) {
        fputc(symbol, file);
        symbol = (char) getc(stdin);
    }

    if (fclose(file)) {
        perror("Error during closing file");
        return -1;
    }
    return 0;
}
