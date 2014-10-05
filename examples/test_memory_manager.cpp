#include "log.h"
#include "memory_list.h"
#include "memory_manager.h"
#include "memory_allocate.h"

typedef struct Hello{
    int a;
    int b;
    int c;
    char d;
}hello_t;

int main(){
    MemMgr *mem_mgr = MemManager::get_manager();
    int *a = new int;
    //cout<<"1 " << mem_mgr->size()<<endl;
    Log::i("main", "pointer in manager:%d", mem_mgr->size());
   
    int *b = new int;
    //cout<<"2 " <<mem_mgr->size()<<endl;
    Log::i("main", "pointer in manager:%d", mem_mgr->size());

    
    hello_t *hello = new hello_t;
    //cout<<"3 " <<mem_mgr->size()<<endl;
    Log::i("main", "pointer in manager:%d", mem_mgr->size());
   

    
    delete a;
    //cout<<"4 " <<mem_mgr->size()<<endl;
     Log::i("main", "pointer in manager:%d", mem_mgr->size());
    //Log::i("main", "pointer in manager:%d", mem_mgr->size());
    
    delete hello;
    //cout<<"5 " <<mem_mgr->size()<<endl;
    Log::i("main", "pointer in manager:%d", mem_mgr->size());
    delete b;
    //cout<<"6 " <<mem_mgr->size()<<endl;
    Log::i("main", "pointer in manager:%d", mem_mgr->size());

    return 0;
}




