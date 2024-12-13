#include <stdio.h>
#include <stdlib.h>

#include "binary_parser.h"

struct file_contents {
    size_t length;
    char* buffer;
};

typedef struct file_contents file_contents;

file_contents* get_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        perror("Error opening file!");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    const size_t size = ftell(file); // Get the size of the file
    rewind(file); // Reset the file pointer to the beginning

    char* buffer = malloc(size);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    size_t bytesRead = fread(buffer, 1, size, file);
    if (bytesRead != size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file); // Close the file

    file_contents* contents = malloc(sizeof(contents));
    contents->length = size;
    contents->buffer = buffer;

    return contents;
}

int main(void)
{
    file_contents *contents = get_file("../Sample.stl");
    if (contents == NULL) {
        perror("Error reading file...");
        return 1;
    }
    const face* faces = binary_stl_parser(contents->buffer, contents->length);

    free(contents->buffer);
    free(contents);

    print_face(faces[0]);
    return 0;
}
