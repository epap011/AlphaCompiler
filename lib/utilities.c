#include "utilities.h"
#include <stdlib.h>
#include <string.h>

char* format_newlines(char* str) {
    int len = strlen(str);
    int newline_count = 0;
    int i;
    // count newlines in input string
    for (int i = 0; i < len; i++) {
        if (str[i] == '\n') {
            newline_count++;
        }
    }
    // allocate memory for output string
    char* out_str = malloc((len + newline_count + 1) * sizeof(char));
    if (out_str == NULL) {
        return NULL; // error: unable to allocate memory
    }
    // copy input string to output string, replacing newlines with "\n"
    for (i=0; i < len; i++) {
        if (str[i] == '\n') {
            out_str[i++] = '\\';
            out_str[i] = 'n';
        } else {
            out_str[i] = str[i];
        }
    }
    out_str[i] = '\0'; // terminate output string with null character
    return out_str;
}