#include "condition.h"
#include "mutex_lock.h"
#include "mutex_guard.h"
#include "thread.h"
#include "runner.h"
#include "log.h"
#include <unistd.h>
#include <pthread.h>

class Task : public Runner{
public:
    Task():_condition(&_mutex_lock){}
    ~Task(){}

    void svc(){
        MUTEX_GUARD(&_mutex_lock);
        LogDebug("sleep");
        sleep(3);
        LogDebug("sleep end");
        LogDebug("thead wait");
        _condition.Wait();
        LogDebug("wait end");
        sleep(3);
        LogDebug("hello world");
    }
    
    void notify(){
        MUTEX_GUARD(&_mutex_lock);
        _condition.NotifyAll();
    }
private:
    MutexLock _mutex_lock;
    Condition _condition;
};

int main(){
    LogInit();
    Task *runner = new Task;
    Thread *thread1 = new Thread(runner);
    Thread *thread2 = new Thread(runner);
    thread1->start();
    thread2->start();
    LogDebug("start thread");
    sleep(10);

    LogDebug("notify");
    runner->notify();
    //runner->notify();
    sleep(3);

    //sleep(3);
    thread1->join();
    thread2->join();
    LogFini();
    return 0;
}
