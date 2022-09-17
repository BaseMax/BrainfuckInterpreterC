#include <stdio.h>
#include <stdlib.h>

char* read_file(char* file_path)
{
    char* data = NULL;
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    data = malloc(file_size + 1);
    fread(data, file_size, 1, file);
    data[file_size] = '\0';

    fclose(file);
    return data;
}

char* interpret(char* bf)
{
    char* data = malloc(30000);
    char* ptr = data;
    char* output = malloc(30000);
    char* out_ptr = output;

    while (*bf != '\0') {
        switch (*bf) {
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '.':
                *out_ptr = *ptr;
                out_ptr++;
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                if (*ptr == 0) {
                    int depth = 1;
                    while (depth > 0) {
                        bf++;
                        if (*bf == '[') {
                            depth++;
                        } else if (*bf == ']') {
                            depth--;
                        }
                    }
                }
                break;
            case ']':
                if (*ptr != 0) {
                    int depth = 1;
                    while (depth > 0) {
                        bf--;
                        if (*bf == ']') {
                            depth++;
                        } else if (*bf == '[') {
                            depth--;
                        }
                    }
                }
                break;
        }
        bf++;
    }

    return output;
}

int main(int argc, char** argv)
{
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
