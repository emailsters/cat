#ifndef _MUTEX_LOCK_H_
#define _MUTEX_LOCK_H_
#include <pthread.h>

class MutexLock{
public:
    MutexLock();
    ~MutexLock();

    void lock();

    void unlock();

    pthread_mutex_t *get_mutex();

private:
    MutexLock(const MutexLock &mutex_lock){}
    MutexLock operator=(const MutexLock &mutex_lock){}
    
private:
    pthread_mutex_t _mutex;
};

#endif
