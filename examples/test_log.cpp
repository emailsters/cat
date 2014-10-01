#include <iostream>
#include "log.h"
int main(){
    Log::i("main", "hello world %d", 10);
    Log::i("main", "(%s, %u), count:%d", __FILE__, __LINE__, 200);
    return 0;
}


