#include "monitor_thread.h"
#include "thread_mgr.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "log.h"

#define LOG_MONTHREAD "MonThread"

MonThread::MonThread():_missed_hands(0){
    int err = pthread_mutex_init(&_mutex, NULL);
    if(err != 0){
        Log::i(LOG_MONTHREAD, "init mutex failed");
        return;
    }
    ThreadMgr* thread_mgr = ThreadMgr::instance();
    if(NULL != thread_mgr){
        thread_mgr->regist(this);
    }
}

MonThread::~MonThread()
{
    int err = pthread_mutex_destroy(&_mutex);
    if(err != 0){
        Log::i(LOG_MONTHREAD, "failed to destory mutex");
    }
    ThreadMgr* thread_mgr = ThreadMgr::instance();
    if(NULL != thread_mgr){
        thread_mgr->unregist(this);
    }    
}

void MonThread::svc(){
    while(_not_exit){
        sleep(1);
        shake(SHAKE);
        do_task();
    }
}

void MonThread::start(){
    _not_exit = true;
    Thread::start();
}

void MonThread::stop(){
    //Log::i(LOG_MONTHREAD, "stop MonThread");
    _not_exit = false;
}

void MonThread::shake(int direction){
    pthread_mutex_lock(&_mutex);
    //Log::i(LOG_MONTHREAD, "%d get lock", get_thread_id());
    if(SHAKE == direction){
        _missed_hands= 0;
        //Log::i(LOG_MONTHREAD, "shake hand");
    }else{
        ++_missed_hands;
        //Log::i(LOG_MONTHREAD, "unshake hand");
    }        
    pthread_mutex_unlock(&_mutex);
    //Log::i(LOG_MONTHREAD, "%d release lock", get_thread_id());
}

int MonThread::get_missed_hands(){
    return _missed_hands;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                 