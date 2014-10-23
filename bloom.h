#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include<stdlib.h>

typedef unsigned int (*hashfunc_t)(const char *, unsigned int len);
typedef struct {
    size_t size; 
    unsigned char *a; 
    size_t nfuncs;  
    hashfunc_t *funcs;  
} BF;

BF *bloom_create(size_t size, size_t nfuncs, ...);
int bloom_destroy(BF *bloom);
int bloom_add(BF *bloom, const char *s);
int bloom_check(BF *bloom, const char *s);


#endif
