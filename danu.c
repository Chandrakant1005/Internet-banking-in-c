#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void search_string_in_file(const char *filename, const char *search_string) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strstr(line, search_string) != NULL) {
            printf("Found \"%s\" in file: %s\n", search_string, filename);
            fclose(file);
            return;
        }
    }

    printf("String \"%s\" not found in file: %s\n", search_string, filename);
    fclose(file);
}

int main() {
    const char *filename = "example.txt";
    const char *search_string = "target";

    search_string_in_file(filename, search_string);

    return 0;
}
