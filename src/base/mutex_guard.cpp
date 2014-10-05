#include "mutex_guard.h"

MutexGuard::MutexGuard(MutexLock *mutex_lock):_mutex_lock(mutex_lock){
    _mutex_lock->lock();
}

MutexGuard::~MutexGuard(){
    _mutex_lock->unlock();
}

