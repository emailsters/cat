#include "memory_list.h"
#include "log.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

#define LOG_MEMLIST "memory_list"

struct MemNode{
    void *value;
    struct MemNode *next;
    struct MemNode *prev;
};

MemList::MemList():_head(NULL), _tail(NULL), _size(0){

}

MemList::~MemList(){
    clear();
}

void MemList::clear(){
    mem_node_t *mem_node = _head;
    mem_node_t *d_node = NULL;
    
    //would not free outside memory
    while(mem_node){
        d_node = mem_node;
        mem_node = mem_node->next;
        free(d_node);
        d_node = NULL;
    }
    
    _head = NULL;
    _tail = NULL;
    _size = 0;
}

bool MemList::push(void *value){
    if(value == NULL){
        Log::i(LOG_MEMLIST, "can not push NULL pointer");
        return false;
    }
    int ret = find(value);
    if(ret != -1){
        Log::i(LOG_MEMLIST, "failed to push, the memory is already in the list");
        return false;
    }
    if(_head == NULL){
        _head = (mem_node_t*)malloc(sizeof(mem_node_t));
        if(_head == NULL){
            Log::i(LOG_MEMLIST, "(%s, %u) allocate memory failed", 
                __FILE__, __LINE__);
            return false;
        }
        _head->value = value;
        _head->next = NULL;
        _head->prev = NULL;
        _tail = _head;
        ++_size;
        return true;
    }

    mem_node_t *new_node = (mem_node_t*)malloc(sizeof(mem_node_t));
    if(new_node == NULL){
        Log::i(LOG_MEMLIST, "(%s, %u) allocate memory failed", 
                __FILE__, __LINE__);
        return false;
    }
    _tail->next = new_node;
    new_node->value = value;
    new_node->prev = _tail;
    new_node->next = NULL;
    _tail = new_node;
    ++_size;
    return true;
}

unsigned int MemList::size(){
    return _size;
}

int MemList::find(void *value){
    if(value == NULL){
        Log::i(LOG_MEMLIST, "parameter can not be NULL");
        return -1;
    }
    int pos = 0;
    if(_size == 0){
        return -1;
    }
    mem_node_t *mem_node = _head;
    while(mem_node != NULL){
        if(mem_node->value == value){
            return pos;
        }
        mem_node = mem_node->next;
        ++pos;
    }
    return -1;
}

bool MemList::erase(void *value){
    if(_size == 0 || value == NULL){
        Log::i(LOG_MEMLIST, "list or parameter is NULL, can not delete anything");
        return false;
    }
    mem_node_t *mem_node = _head;
    while(mem_node != NULL){
        if(mem_node->value == value){
            if(mem_node->prev != NULL){
                mem_node->prev->next = mem_node->next;
                if(mem_node->next != NULL){
                    mem_node->next->prev = mem_node->prev;
                }else{
                    _tail = mem_node->prev;
                }
                free(mem_node);
                mem_node = NULL;
            }else{
                if(mem_node->next != NULL){
                    mem_node->next->prev = NULL;
                    _head = mem_node->next;
                    free(mem_node);
                    mem_node = NULL;
                }else{
                    _head = NULL;
                    _tail = NULL;
                }
            }
            --_size;
            return true;
        }
        mem_node = mem_node->next;
    }
    Log::i(LOG_MEMLIST, "nothing to delete");
    return true;
}

#ifdef DEBUG
void MemList::print(){
    mem_node_t *mem_node = _head;
    while(mem_node){
        std::cout<<(int)(mem_node->value)<<" ";
        mem_node = mem_node->next;
    }
    std::cout<<""<<std::endl;
}
#endif



