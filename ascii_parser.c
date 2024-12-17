//
// Created by Quintin Dunn on 12/13/24.
//

#include "ascii_parser.h"
#include <stdio.h>
#include <string.h>

#include "binary_parser.h"
#include "vertex.h"
#include "walkable_string.h"

stl* parse_ascii(char* content) {
    const size_t face_count = get_face_count(content);
    face* faces = malloc(sizeof(face) * face_count);

    walkable_string* w_str = construct_walkable_string(content);

    // Basic validation.
    if (!stream_contains(w_str, "solid")) {
        perror("Invalid file!");
        return NULL;
    }

    // Get the name / attributes of the STL file.
    move_to_token(w_str, "solid");
    w_str->current_idx += 5;
    int has_name = 0;
    if (w_str->buffer[w_str->current_idx] != '\n') {
        has_name = 1;
    }
    if (has_name) {
        w_str->current_idx ++;
        const size_t name_length = get_start_next_line_idx(w_str) - 1; // -1 to go back to nl char and -6 "solid " | len = 6
        char* name = consume_n(w_str, name_length); // Not used but would have name / top attributes.
    }


    // Iterate through each triangle.
    int face_idx = 0;
    while (!line_contains(w_str, "endsolid")) {
        face triangle = {};

        // If there's no more facets, break the loop.
        if (move_to_token(w_str, "facet normal") == -1) {
            break;
        };

        // filter out only the normal vector.
        char* normal_vector = consume_n(w_str, get_start_next_line_idx(w_str));

        // filter out only the vertices.
        move_to_token(w_str, "outer loop");
        const size_t outer_loop_start = w_str->current_idx + get_start_next_line_idx(w_str);
        move_to_token(w_str, "endloop");
        const size_t outer_loop_end = w_str->current_idx;
        w_str->current_idx = outer_loop_start;
        const char* vertices_raw = consume_n(w_str, outer_loop_end-outer_loop_start);

        // parse the vertices
        parse_vertices(vertices_raw, &triangle);
        parse_normal_vector(normal_vector, &triangle);

        faces[face_idx++] = triangle;
    }

    const stl output = {
        face_count,
        faces,
    };

    return &output;
}

size_t get_face_count(char* content) {
    walkable_string* w_str = construct_walkable_string(content);
    size_t count = 0;

    while (move_to_token(w_str, "endfacet") == 1) {
        w_str->current_idx ++;
        count++;
    }
    return count;
}

void parse_normal_vector(const char* normal_vector_raw, face *triangle) {
    float positions[3];
    sscanf(normal_vector_raw, "facet normal %f %f %f", &positions[0], &positions[1], &positions[2]);
    triangle->normal_vector = (vector3) { positions[0], positions[1], positions[2] };
}


void parse_vertices(const char *vertices_raw, face *triangle) {
    float positions[9];
    sscanf(vertices_raw, "vertex %f %f %f\nvertex %f %f %f\nvertex %f %f %f",
        &positions[0], &positions[1], &positions[2], &positions[3], &positions[4], &positions[5], &positions[6], &positions[7], &positions[8]);

    triangle->a = (vector3) { positions[0], positions[1], positions[2] };
    triangle->b = (vector3) { positions[3], positions[4], positions[5] };
    triangle->c = (vector3) { positions[6], positions[7], positions[8] };
}