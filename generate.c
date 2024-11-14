#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif

void generate_file(const char *filename, const int size) {
    FILE *file = fopen(filename, "w");

    if (!file) {
        fprintf(stderr, "Unable to open [%s] for writing.\n", filename);
        return;
    }

    for (int i = 0; i < size; ++i) {
        const int random_number = rand() % 65536;
        fprintf(file, "%d", random_number);

        if (i < size - 1) {
            fprintf(file, " ");
        }
    }

    fclose(file);
}

int main() {
    const struct {
        int size;
        const char *label;
    } generation_info[] = {
        {10000, "10_000"},
        {100000, "100_000"},
        {1000000, "1_000_000"},
        {10000000, "10_000_000"},
        {100000000, "100_000_000"}
    };

    const char *generated_path = "." DIR_SEPARATOR "generated" DIR_SEPARATOR;
    const char *generation_base_path_name = "numbers";

    srand((unsigned int) time(NULL));

    for (int i = 0; i < sizeof(generation_info) / sizeof(generation_info[0]); i++) {
        const int size = generation_info[i].size;
        const char *current_sub_path_name = generation_info[i].label;

        for (int j = 1; j <= 50; j++) {
            char filepath[256];
            snprintf(
                filepath,
                sizeof(filepath),
                "%s%s%s%s_%d.txt",
                generated_path,
                current_sub_path_name,
                DIR_SEPARATOR,
                generation_base_path_name,
                j
            );
            generate_file(filepath, size);
        }
    }

    return 0;
}
