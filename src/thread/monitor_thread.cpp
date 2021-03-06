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
    _not_exit = false;
}

void MonThread::shake(int direction){
   MUTEX_GUARD(&_mutex);
    if(SHAKE == direction){
        _missed_hands= 0;
    }else{
        ++_missed_hands;
    }
}

int MonThread::get_missed_hands(){
    return _missed_hands;
}

