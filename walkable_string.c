//
// Created by Quintin Dunn on 12/13/24.
//

#include "walkable_string.h"

#include <stdlib.h>
#include <string.h>

walkable_string* construct_walkable_string(char* content) {
    walkable_string* w_str = malloc(sizeof(walkable_string));
    w_str->buffer = content;
    w_str->length = strlen(content);
    w_str->current_idx = 0;
    return w_str;
}

char peek(const walkable_string *w_str) {
    return w_str->buffer[w_str->current_idx+1];
}

int next_token_is(const walkable_string *w_str, const char* needle) {
    int needle_len = strlen(needle);
    // Check the needle wouldn't exceed
    if (w_str->current_idx + needle_len > w_str->length) {
        return -1;
    }

    for (int i = 0; i < needle_len; i++) {
        if (w_str->buffer[w_str->current_idx+i] != needle[i]) {
            // printf("Non equiv char\n");
            return 0;
        }
    }
    return 1;
}

int line_contains(walkable_string *w_str, const char* needle) {
    const size_t needle_len = strlen(needle);
    const size_t start_idx = w_str->current_idx;
    while (w_str->buffer[w_str->current_idx] != '\n' && w_str->current_idx + needle_len <= w_str->length) {
        int nti = next_token_is(w_str, needle);
        if (nti == 1) {
            w_str->current_idx = start_idx;
            return 1;
        }
        if (nti == -1) {
            w_str->current_idx = start_idx;
            return -1;
        }
        w_str->current_idx++;
    }
    w_str->current_idx = start_idx;
    return 0;
}

int stream_contains(walkable_string *w_str, const char* needle) {
    const size_t needle_len = strlen(needle);
    const size_t start_idx = w_str->current_idx;
    while (w_str->current_idx + needle_len <= w_str->length) {
        int nti = next_token_is(w_str, needle);
        if (nti == 1) {
            w_str->current_idx = start_idx;
            return 1;
        }
        if (nti == -1) {
            w_str->current_idx = start_idx;
            return -1;
        }
        w_str->current_idx++;
    }
    w_str->current_idx = start_idx;
    return 0;
}

size_t get_start_next_line_idx(walkable_string *w_str) {
    const size_t start_idx = w_str->current_idx;
    while (w_str->buffer[w_str->current_idx] != '\n' && w_str->current_idx != w_str->length) {
        w_str->current_idx++;
    }
    if (w_str->current_idx == w_str->length) {
        w_str->current_idx = start_idx;
        return -1;
    }
    size_t idx = w_str->current_idx - start_idx;
    w_str->current_idx = start_idx;
    return ++idx;
}

int move_to_token(walkable_string *w_str, const char* needle) {
    size_t fallback = w_str->current_idx;
    int nti = next_token_is(w_str, needle);
    while (nti != 1) {
        if (nti == -1) {
            return -1;
        }
        w_str->current_idx++;
        if (w_str->current_idx > w_str->length-1) {
            w_str->current_idx = fallback;
            printf("fail!");
            return 0;
        }
        nti = next_token_is(w_str, needle);
    }
    return 1;
}

char* consume_n(walkable_string *w_str, size_t n) {
    if (n == -1) {
        const size_t ref = w_str->current_idx;
        w_str->current_idx = w_str->length-1;
        return &w_str->buffer[ref];

    }
    char* buff = malloc(sizeof(char) * n + 1);

    for (int i = 0; i < n; i++) {
        buff[i] = w_str->buffer[w_str->current_idx];
        w_str->current_idx ++;
    }
    buff[n] = '\0';

    return buff;
}