#include "memory_list.h"
#include "log.h"

int main(){
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
    
    Log::i("main", "list size:%d", list.size());
    list.print();
    list.erase((void*)3);
    Log::i("main", "list size:%d", list.size());
    list.print();

    list.erase((void*)1);
    Log::i("main", "list size:%d", list.size());
    list.print();

    list.erase((void*)7);
    Log::i("main", "list size:%d", list.size());
    list.print();

    
    list.clear();
    Log::i("main", "list size:%d", list.size());
    return 0;
}

