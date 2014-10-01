#include "timer_thread.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>

int CTimerThread::_interval = 0;
bool CTimerThread::_not_exit = false;

CTimerThread::CTimerThread():_thread_id(0),_started(false)
{
}

CTimerThread::~CTimerThread(){
    exit();
}

int CTimerThread::set_timer(int interval){
    if(_started || interval <= 0){
        return 0;
    }
    
    _interval = interval;
    _not_exit = true;
    int err = pthread_create(&_thread_id, NULL, hook, this);
    if(err != 0){
        // failed to create timer thread
    }
    return 0;
}

void* CTimerThread::hook(void *args){
    while(_not_exit){
        sleep(_interval);
        reinterpret_cast<CTimerThread*>(args)->on_timer();
    }
}

void CTimerThread::kill_timer(){
    exit();
}

void CTimerThread::exit(){
    _started = false;
    _not_exit = false;
    pthread_join(_thread_id, NULL);
    std::cout<<"exit timer thread"<<std::endl;
}

