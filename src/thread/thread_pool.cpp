#include "thread_pool.h"
#include "log.h"
#include <pthread.h>
#include <unistd.h>
#include "mutex_guard.h"

#define THREAD_POOL_NAME_DEFAULT "unknown_thread_pool"
#define LOG_THREAD_POOL "thread_pool"
#define MAX_TASK_QUEUE_SIZE 6556
#define MAX_THREAD_COUNT 256

ThreadPool::ThreadPool(string name):_running(false){
    if(name == "")
        _pool_name = THREAD_POOL_NAME_DEFAULT;
    else
        _pool_name = name;

    clear_task_queue();
    clear_threads();
}

ThreadPool::~ThreadPool(){
    clear_task_queue();
    clear_threads();
}

int ThreadPool::start(int thread_count){
    int succ_count = 0;
    if(thread_count > MAX_THREAD_COUNT){
        Log::i(LOG_THREAD_POOL, "too much threads");
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
    _running = false;
}

void ThreadPool::svc(){
    while(_running){
        //Log::i(LOG_THREAD_POOL, "in thread pool svc");
        sleep(1);
        Runner *task = take();
        if(task){
            //Log::i(LOG_THREAD_POOL, "run task");
            task->svc();
            delete task;
        }        
    }
}

bool ThreadPool::push_task(Runner *task){
    MUTEX_GUARD_RETURN(&_mutex);
    if(full()){
        Log::i(LOG_THREAD_POOL, "task queue is full");
        return false;
    }
    if(check_task(task)){
        _task_queue.push_back(task);
    }else{
        Log::i(LOG_THREAD_POOL, "task is already running");
    }
    // need to notify threads
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
    MUTEX_GUARD_RETURN(&_mutex);
    //Log::i(LOG_THREAD_POOL, "take task");
    Runner *task;
    if(_task_queue.empty()){
        return NULL;
    }
    task = _task_queue.front();
    _task_queue.pop_front();
    return task;
}

void ThreadPool::clear_task_queue(){
    //Log::i(LOG_THREAD_POOL, "task queue size:%d", _task_queue.size());
    while(!_task_queue.empty()){
        delete _task_queue.front();
        _task_queue.pop_front();
    }    
}

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

