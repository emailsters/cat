#ifndef _CONDITION_H_
#define _CONDITION_H_
#include <pthread.h>
#include "mutex_lock.h"

class Condition{
public:
    explicit Condition(MutexLock *mutex_lock);
    ~Condition();

    void wait();

    void notify();

    void notify_all();
private:
    MutexLock *_mutex_lock;

    pthread_cond_t _condition;
};

#endif

