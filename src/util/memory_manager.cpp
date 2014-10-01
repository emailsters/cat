#include "memory_manager.h"

namespace MemManager{
    MemList g_list;

    MemMgr* get_manager(){
        return &g_list;
    }
}

