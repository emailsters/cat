#ifndef _MEMORY_ALLOCATE_H_
#define _MEMORY_ALLOCATE_H_
#include <iostream>
#include <stdlib.h>
#include "memory_manager.h"
#include "log.h"

inline void *operator new(size_t size, const char *file, unsigned int line){
    void *p = (void *)malloc(size);
    if(p == NULL){
        Log::i("new", "allocate memory failed");
        return NULL;
    }
    MemMgr *mem_mgr = MemManager::get_manager();
    mem_mgr->push(p);
    return p;
}

inline void operator delete(void *p){
    MemMgr *mem_mgr = MemManager::get_manager();
    mem_mgr->erase(p);
    free(p);
    p = NULL;
}

#define new new(__FILE__, __LINE__)
#endif

