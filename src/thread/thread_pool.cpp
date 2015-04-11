#include "thread_pool.h"
#include "log.h"
#include <pthread.h>
#include <unistd.h>
#include "mutex_guard.h"

#define THREAD_POOL_NAME_DEFAULT "unknown_thread_pool"
#define LOG_THREAD_POOL "thread_pool"
#define MAX_TASK_QUEUE_SIZE 6556
#define MAX_THREAD_COUNT 256

ThreadPool::ThreadPool(string name):_running(false), _condition(&_mutex){
    if(name == "")
        _pool_name = THREAD_POOL_NAME_DEFAULT;
    else
        _pool_name = name;

    _task_queue.clear();
    _threads.clear();
}

ThreadPool::~ThreadPool(){
    _task_queue.clear();
}

int ThreadPool::start(int thread_count){
    int succ_count = 0;
    if(thread_count > MAX_THREAD_COUNT){
        LogDebug("too much threads");
        return 0;
    }
    _running = true;    
    for(int i = 0; i < thread_count; ++i){
        Thread *thread = new Thread(this);
        if(thread != NULL){
            thread->start();
            _threads.push_back(thread);
            ++succ_count;
        }
    }
    return succ_count;
}

void ThreadPool::stop(){
    {
        MUTEX_GUARD(&_mutex);
        LogDebug("stop thread pool");
        _running = false;
        _condition.NotifyAll();
    }
    clear_threads();
    
    LogDebug("stop thread pool end");
}

void ThreadPool::svc(){
    while(_running){
        sleep(1);
        Runner *task = take();
        if(task){
            task->svc();
            //task由外部释放
            //delete task;
        }
    }
}

bool ThreadPool::push_task(Runner *task){
    MUTEX_GUARD(&_mutex);
    if(full()){
        LogDebug("task queue is full");
        return false;
    }
    if(check_task(task)){
        _task_queue.push_back(task);
    }else{
        LogDebug("task is already running");
        return false;
    }
    LogDebug("push task, notify all");
    _condition.NotifyAll();
    return true;
}

bool ThreadPool::check_task(Runner *task){
    list<Runner*>::iterator itor = _task_queue.begin();
    while(itor != _task_queue.end()){
        if(task == (*itor)){
            return false;
        }
        ++itor;
    }
    return true;
}

Runner* ThreadPool::take(){
    MUTEX_GUARD(&_mutex);
    Runner *task = NULL;
    while(_task_queue.empty() && _running){
        LogDebug("queue is empty waiting");
        _condition.Wait();
    }
    if(!_task_queue.empty()){
        LogDebug("take task");
        task = _task_queue.front();
        _task_queue.pop_front();
    }
    return task;
}

/* task应该由外部进行释放
void ThreadPool::clear_task_queue(){
    while(!_task_queue.empty()){
        delete _task_queue.front();
        _task_queue.pop_front();
    }    
}
*/

void ThreadPool::clear_threads(){
    vector<Thread*>::iterator itor = _threads.begin();
    while(itor != _threads.end()){
        (*itor)->join();
        delete (*itor);
        ++itor;
    }
    _threads.clear();
}

bool ThreadPool::full() const{
    return (_task_queue.size() > MAX_TASK_QUEUE_SIZE);
}

int ThreadPool::tasks_in_queue() const{
    return _task_queue.size();
}

