#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <iostream>
#include <vector>
#include <list>
#include "runner.h"
#include "thread.h"
#include "mutex_lock.h"
#include "condition.h"

using namespace std;

class ThreadPool : public Runner{
public:
    ThreadPool(string name);
    ~ThreadPool();
    
    //return successfully started thread count
    int start(int thread_ount);

    void stop();

    //free memory inside
    bool push_task(Runner *task);

    bool full() const;

    int tasks_in_queue() const;

private:
    // void clear_task_queue();

    //所有线程执行完毕才会结束
    void clear_threads();

    Runner* take();

    void svc();

    bool check_task(Runner *task);
    
private:
    string _pool_name;
    
    list<Runner*> _task_queue;
    
    MutexLock _mutex;

    Condition _condition;

    bool _running;

    vector<Thread*> _threads;
};

#endif

