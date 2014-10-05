#include "mutex_lock.h"
#include <pthread.h>
#include "log.h"

#define LOG_MUTEX_LOCK "MutexLock"

MutexLock::MutexLock(){
    int ret = pthread_mutex_init(&_mutex, NULL);
    if(ret != 0){
        Log::i(LOG_MUTEX_LOCK, "failed to init mutex. err code:%d", ret);
    }
}

MutexLock::~MutexLock(){
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret != 0){
        Log::i(LOG_MUTEX_LOCK, "failed to destroy mutex. err code:%d", ret);
    }
}

void MutexLock::lock(){
    int ret = pthread_mutex_lock(&_mutex);
    if(ret != 0){
        Log::i(LOG_MUTEX_LOCK, "failed to lock mutex. err code:%d", ret);
    }
}

void MutexLock::unlock(){
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret != 0){
        Log::i(LOG_MUTEX_LOCK, "failed to unlock mutex. err code:%d", ret);
    }
}

pthread_mutex_t *MutexLock::get_mutex(){
    return &_mutex;
}

