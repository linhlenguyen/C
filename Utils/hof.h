#ifndef HOF
#define HOF

void* map(void* base, size_t n, size_t s, void* (*fnc)(const void*));
void* filter(void* base, size_t n, size_t s, bool (*fnc)(const void*));
void* fold(void *base, size_t n, size_t s, void* (*fnc)(const void*, const void*));

#endif