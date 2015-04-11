#include <iostream>
#include "log.h"
int main(){
    LogInit();
    LogDebug("hello world %d", 10);
    LogDebug("(%s, %u), count:%d", __FILE__, __LINE__, 200);
    LogFini();
    return 0;
}


