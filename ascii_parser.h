//
// Created by Quintin Dunn on 12/13/24.
//

#ifndef ASCII_PARSER_H
#define ASCII_PARSER_H
#include <stdlib.h>
#include "vertex.h"

stl* parse_ascii(char* content);
void parse_vertices(const char* vertices_raw, face *triangle);
void parse_normal_vector(const char* normal_vector_raw, face *triangle);
size_t get_face_count(char* content);
#endif //ASCII_PARSER_H
