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
    hook_param_t *param = reinterpret_cast<hook_param_t*>(args);
    bool has_runner = param->has_runner;
    void *func = param->hook_ptr;
    if(has_runner){
        //Log::i(THREAD_LOG, "has not runner");
        reinterpret_cast<Thread*>(func)->svc();
    }else{
        //Log::i(THREAD_LOG, "has runner");
        reinterpret_cast<Runner*>(func)->svc();
    }
    return NULL;
}

Thread::Thread():_runner(NULL){
    _hook_param = new hook_param_t;
}

Thread::Thread(Runner *runner):_started(false){
    _runner = runner;
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
        Log::i(THREAD_LOG, "thread is already started, could not set runner");
        return;
    }
    _runner = runner;
}

void Thread::start(){
    if(_started){
        Log::i(THREAD_LOG, "thread is already started");
        return;
    }
    if(_hook_param == NULL){
        Log::i(THREAD_LOG, "_hook_param is null");
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
    if(err != 0){
        Log::i(THREAD_LOG, "create thread failed");
        return;
    }
    _started = true;
}

void Thread::svc(){
    Log::i(THREAD_LOG, "(%s, %u) in thread svc", __FILE__, __LINE__);
}

pthread_t Thread::get_thread_id(){
    return _thread_id;
}

void Thread::join(){
    int err = pthread_join(_thread_id, NULL);
    if(err != 0){
        Log::i(THREAD_LOG, "thread join failed");
    }
}


