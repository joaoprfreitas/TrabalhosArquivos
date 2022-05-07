#include <file.h>

FILE *createFile(char *fileName) {
    FILE *f = fopen(fileName, "wb");

    return f;
}