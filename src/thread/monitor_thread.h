#ifndef _MONITOR_THREAD_H_
#define _MONITOR_THREAD_H_
#include <pthread.h>
#include "runner.h"
#include "thread.h"
#include "mutex_lock.h"

#define SHAKE 1
#define UNSHAKE 0

class MonThread : public Thread
{
public:
    MonThread();
    
    ~MonThread();

    void start();
    
    void stop();

    int get_missed_hands();

    void shake(int direction);

    void svc();
    
protected:
    virtual void do_task() = 0;

private:
    bool _not_exit;

    MutexLock _mutex;
    
    int _missed_hands;
};
#endif

