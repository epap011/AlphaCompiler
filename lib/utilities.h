#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef DISABLE_NEWLINE_PRINTING
#define FORMAT_NEWLINES(x) format_newlines(x)
#else
#define FORMAT_NEWLINES(x) x
#endif

char* format_newlines(char* str);

#endif /*UTILITIES_H*/