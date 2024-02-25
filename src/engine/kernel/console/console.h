//
// Created by alexander on 2/24/24.
//

#ifndef ECON_RPG_CONSOLE_H
#define ECON_RPG_CONSOLE_H



#define C_RESET     "\x1B[0m"
#define C_BLACK     "\x1B[30m"
#define C_RED       "\x1B[31m"
#define C_GREEN     "\x1B[32m"
#define C_YELLOW    "\x1B[33m"
#define C_BLUE      "\x1B[34m"
#define C_MAGENTA   "\x1B[35m"
#define C_CYAN      "\x1B[36m"
#define C_WHITE     "\x1B[37m"

#define LOG_VERBOSE 1
#define LOG_INFO 1
#define LOG_WARN 1
#define LOG_ERROR 1


#include <stdarg.h>
#include <stdio.h>

inline void log_verbose(const char * format, ...) {
#ifdef LOG_VERBOSE
    va_list args;
    va_start(args, format);
    printf("[Verbose] ");
    vprintf(format, args);
    va_end(args);
#endif
}

inline void log_info(const char * format, ...) {
#ifdef LOG_INFO
    va_list args;
    va_start(args, format);
    printf("[Info] ");
    vprintf(format, args);
    va_end(args);
#endif
}

inline void log_warn(const char * format, ...) {
#ifdef LOG_WARN
    va_list args;
    va_start(args, format);
    printf("%s[Warn] ", C_YELLOW);
    vprintf(format, args);
    printf(C_RESET);
    va_end(args);
#endif
}

inline void log_error(const char * format, ...) {
#ifdef LOG_ERROR
    va_list args;
    va_start(args, format);
    fprintf(stderr, "[Error] ");
    vfprintf(stderr, format, args);
    va_end(args);
#endif
}



#endif //ECON_RPG_CONSOLE_H
