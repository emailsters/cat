#ifndef _MUTEX_GUARD_H_
#define _MUTEX_GUARD_H_
#include "mutex_lock.h"

class MutexGuard{
public:
    MutexGuard(MutexLock *mutex_lock);
    ~MutexGuard();
public:
    MutexGuard(const MutexGuard &mutex_gurad){}
    MutexGuard operator=(const MutexGuard &mutex_gurad){}
private:
    MutexLock *_mutex_lock;
};

#define MUTEX_GUARD(mutex) MutexGuard guard(mutex)

#endif

