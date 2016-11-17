#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* map(void* base, size_t n, size_t si, size_t so, void* (*fnc)(const void*)){
    void* out = malloc(n * so);
    
    int i = 0;
    for (i; i < n; i ++){
        void* re = fnc((void*)((char*)base + i*si));
        memcpy((char*)out + so*i, re, so);
    }
    return out;
}

void* filter(void* base, size_t n, size_t si, int (*fnc)(const void*)){
    void* tm = malloc(n * si);
    
    int i = 0, k = 0;
    for (i; i < n; i++){
        if (fnc((void*)((char*)base + i*si)) > 0){
            memcpy((char*)tm + si*(k++), (char*)base + i*si, si);
        }
    }
    
    tm = realloc(tm,(k+1)*si);
    return tm;
}

void* fold(void* base, size_t n, size_t si, void* in, void* (*fnc)(const void*, const void*)){
    int i = 0;
    for (i = 0; i < n; i++){
        in = fnc(in, (void*)((char*)base + i*si));
    }
    return in;
}

void* inc(const void* a){
    int* ia = (int*)a;
    *ia += 1;
    return (void*)ia;
}

void printA (void* a, size_t s){
    int i = 0;
    for (i; i < sizeof(a)/s; i++){
    }
}

int filterF (const void* a){
    if (*((char*)a) == 'l')
        return 1;
    else return 0;
}

void* sumF (const void* base, const void* a){
    int* b = (int*) base;
    *b = *b + *((int*) a);
    return (void*)b;
}

void mapTest(){
    int ia[] = {1,2,3,4,5};
    int* ma = (int*)map((void*)ia, sizeof(ia)/sizeof(int), sizeof(int), sizeof(int), &inc);
    
    printf("%p\n", ia);
    for (int i = 0; i < sizeof(ia)/sizeof(int) ; i++){
        printf("%d ", ia[i]);
    }
    
    printf("\n%p\n", ma);
    for (int i = 0; i < sizeof(ia)/sizeof(int) ; i++){
        printf("%d ", ma[i]);
    }
}

void filterTest(){
    char* text = "hello";
    char* ftext = (char*)filter((void*) text, sizeof(text)/sizeof(char), sizeof(char), filterF);
    
    printf("%s %s\n", text, ftext);
}

void foldTest(){
    int ia[] = {1,2,3,4,5};
    int sum = 0;
    fold((void*)ia, sizeof(ia)/sizeof(int), sizeof(int), (void*)(&sum), sumF);
    printf("%d", sum);
}

void* charToInt(const void* a){
    char* c = (char*) a;
    int* i;
    *i = (int)(*c);
    return (void*)i;
}

int main() {
    char* text = "Hello";
    int* ia = map((void*)text, sizeof(text)/sizeof(char), sizeof(char), sizeof(int), charToInt)
    int sum;
    fold((void*) ia, 5, sizeof(int), sumF);
    printf("%d", sum);
    return 0;
}