#include "thread.h"
#include <pthread.h>
#include "log.h"
#include "runner.h"

#define THREAD_LOG "Thread"

struct HookParam{
    bool has_runner;
    void *hook_ptr;
};

void *hook(void *args){
    if(args == NULL)
        return NULL;
    hook_param_t *param = static_cast<hook_param_t*>(args);
    bool has_runner = param->has_runner;
    void *func = param->hook_ptr;
    if(has_runner){
        static_cast<Thread*>(func)->svc();
    }else{
        static_cast<Runner*>(func)->svc();
    }
    return NULL;
}

Thread::Thread():_runner(NULL), _started(false), _thread_id(0){
    _hook_param = new hook_param_t;
}

Thread::Thread(Runner *runner):_runner(runner), _started(false), 
    _thread_id(0){
    _hook_param = new hook_param_t;
}

Thread::~Thread(){
    if(_hook_param){
        delete _hook_param;
        _hook_param = NULL;
    }
}

void Thread::set_runner(Runner *runner){
    if(_started){
        LogDebug("thread is already started, could not set runner");
        return;
    }
    _runner = runner;
}

void Thread::start(){
    if(_started){
        LogDebug("thread is already started");
        return;
    }
    if(_hook_param == NULL){
        LogDebug("_hook_param is null");
        return;
    }
    int err = 1;
    if(_runner != NULL){
        _hook_param->has_runner = false;
        _hook_param->hook_ptr = _runner;
    }else{
        _hook_param->has_runner = true;
        _hook_param->hook_ptr = this;
    }
    err = pthread_create(&_thread_id, NULL, hook, _hook_param);
    LogDebug("create thread %d", _thread_id);
    if(err != 0){
        LogDebug("create thread failed");
        return;
    }
    _started = true;
}

void Thread::svc(){
    LogDebug("(%s, %u) in thread svc", __FILE__, __LINE__);
}

pthread_t Thread::get_thread_id(){
    return _thread_id;
}

void Thread::join(){
    if(_thread_id == 0){
        LogDebug("no thread to join");
        return;
    }
    int err = pthread_join(_thread_id, NULL);
    if(err != 0){
        LogDebug("thread %d join failed, return code:%d", _thread_id, err);
    }
}


