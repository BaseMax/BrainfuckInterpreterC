#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <file>", argv[0]);
        return 1;
    }
    else {
        char* code = read_file(argv[1]);
        if (code == NULL) {
            printf("File not found");
            return 1;
        }
        else {
            char* result = interpret(code);
            printf("%s", result);

            free(code);
            free(result);
        }
    }
    return 0;
}
