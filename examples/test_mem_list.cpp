#include "memory_list.h"
#include "log.h"

int main(){
    LogInit();
    MemList list;
    list.push((void *)1);
    list.push((void *)2);
    list.push((void *)3);
    list.push((void *)4);
    list.push((void *)5);
    list.push((void *)6);
    list.push((void *)7);

    list.push((void *)7);
    list.print();
    
    LogDebug("list size:%d", list.size());
    list.print();
    list.erase((void*)3);
    LogDebug("list size:%d", list.size());
    list.print();

    list.erase((void*)1);
    LogDebug("list size:%d", list.size());
    list.print();

    list.erase((void*)7);
    LogDebug("list size:%d", list.size());
    list.print();

    
    list.clear();
    LogDebug("list size:%d", list.size());
    LogFini();
    return 0;
}

