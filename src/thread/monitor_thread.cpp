#include "monitor_thread.h"
#include "thread_mgr.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "log.h"
#include "mutex_guard.h"

#define LOG_MONTHREAD "MonThread"

MonThread::MonThread():_missed_hands(0){
    ThreadMgr* thread_mgr = ThreadMgr::instance();
    if(NULL != thread_mgr){
        thread_mgr->regist(this);
    }
}

MonThread::~MonThread()
{
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
   MUTEX_GUARD_RETURN(&_mutex);
    //Log::i(LOG_MONTHREAD, "%d get lock", get_thread_id());
    if(SHAKE == direction){
        _missed_hands= 0;
        //Log::i(LOG_MONTHREAD, "shake hand");
    }else{
        ++_missed_hands;
        //Log::i(LOG_MONTHREAD, "unshake hand");
    }
}

int MonThread::get_missed_hands(){
    return _missed_hands;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                 