//
// Created by Quintin Dunn on 12/12/24.
//

#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include "vertex.h"
#include <stdlib.h>

face* binary_stl_parser(const char* content, size_t size);
void print_face(face triangle);
#endif //BINARY_PARSER_H
