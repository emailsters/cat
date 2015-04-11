#include "mutex_lock.h"
#include <pthread.h>

#define LOG_MUTEX_LOCK "MutexLock"

MutexLock::MutexLock(){
    (void)pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock(){
    (void)pthread_mutex_destroy(&_mutex);
}

int MutexLock::Lock(){
    return pthread_mutex_lock(&_mutex);
}

int MutexLock::Unlock(){
    return pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t *MutexLock::GetMutex(){
    return &_mutex;
}

