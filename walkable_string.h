//
// Created by Quintin Dunn on 12/13/24.
//

#ifndef WALKABLE_STRING_H
#define WALKABLE_STRING_H

#include <stdio.h>

struct walkable_string {
    char* buffer;
    size_t length;
    size_t current_idx;
};

typedef struct walkable_string walkable_string;

walkable_string* construct_walkable_string(char* content);


char peek(const walkable_string *w_str);

// char* consume(walkable_string wstr, size_t count);
int next_token_is(const walkable_string *w_str, const char* needle);
int line_contains(walkable_string *w_str, const char* needle);
int stream_contains(walkable_string *w_str, const char* needle);
int move_to_token(walkable_string *w_str, const char* needle);
size_t get_start_next_line_idx(walkable_string *w_str);
char* consume_n(walkable_string *w_str, size_t n);

#endif //WALKABLE_STRING_H
