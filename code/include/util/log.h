#ifndef LOG_H
#define LOG_H

#define LOG(fmt, ...) logm(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

void logm(const char* file, const char* func, int line, const char* fmt, ...);
#endif