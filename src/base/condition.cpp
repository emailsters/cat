#include "condition.h"

#define LOG_CONDITION "Condition"

Condition::Condition(MutexLock *mutex_lock):_mutex_lock(mutex_lock){
    (void)pthread_cond_init(&_condition, NULL);
}

Condition::~Condition(){
    (void)pthread_cond_destroy(&_condition);
}

int Condition::Wait(){
    return pthread_cond_wait(&_condition, _mutex_lock->GetMutex());
}

int Condition::Notify(){
    return pthread_cond_signal(&_condition);
}

int Condition::NotifyAll(){
    return pthread_cond_broadcast(&_condition);
}

