#include "condition.h"
#include "log.h"

#define LOG_CONDITION "Condition"

Condition::Condition(MutexLock *mutex_lock):_mutex_lock(mutex_lock){
    int ret = pthread_cond_init(&_condition, NULL);
    if(ret != 0){
        Log::i(LOG_CONDITION, "condition init failed");
    }
}

Condition::~Condition(){
    int ret = pthread_cond_destroy(&_condition);
    if(ret != 0){
        Log::i(LOG_CONDITION, "condition destroy failed");
    }
}

void Condition::wait(){
    //进入wait后会自动释放锁
    int ret = pthread_cond_wait(&_condition, _mutex_lock->get_mutex());
    if(ret != 0){
        Log::i(LOG_CONDITION, "condition wait failed");
    }
}

void Condition::notify(){
    int ret = pthread_cond_signal(&_condition);
    if(ret != 0){
        Log::i(LOG_CONDITION, "condition notify failed");
    }
}

void Condition::notify_all(){
    int ret = pthread_cond_broadcast(&_condition);
    if(ret != 0){
        Log::i(LOG_CONDITION, "condition notify all failed");
    }
}

