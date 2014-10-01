#ifndef _TYPES_H_
#define _TYPES_H_
#include <iostream>
#include <stdlib.h>
#include "memory_manager.h"
#include "log.h"

#define RET_OK 0
#define RET_ERR 1

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
