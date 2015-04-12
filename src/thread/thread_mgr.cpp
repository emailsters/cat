#include "thread_mgr.h"
#include "monitor_thread.h"
#include <iostream>
#include "log.h"

#define LOG_THREAD_MGR "ThreadMgr"

ThreadMgr* ThreadMgr::_thread_mgr = NULL;
MutexLock ThreadMgr::_mutex;

ThreadMgr::ThreadMgr(){
    set_timer(1);
}

ThreadMgr* ThreadMgr::instance()
{
    _mutex.Lock();
    if(NULL == _thread_mgr){
        _thread_mgr = new ThreadMgr;
    }
    _mutex.Unlock();
    return _thread_mgr;
}

ThreadMgr::~ThreadMgr()
{
   clear();    
    kill_timer();
}

int ThreadMgr::regist(MonThread *thread)
{
    _mutex.Lock();
    _thread_list.push_back(thread);
    _mutex.Unlock();
    return 0;
}

/*
int ThreadMgr::pop(MonThread *thread)
{
    if(!_thread_list.empty()){
        thread = _thread_list.back();
        _thread_list.pop_back();
    }
}
*/

int ThreadMgr::unregist(MonThread *thread){
    _mutex.Lock();
    if(_thread_list.empty()){
        LogDebug("list is emtpy");
        _mutex.Unlock();
        return false;
    }
    list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        if((*itor) == thread){
            _thread_list.erase(itor);
            _mutex.Unlock();
            return 0;
        }
        ++itor;
    }
    LogDebug("can not find thread");
    _mutex.Unlock();
    return -1;
}

void ThreadMgr::clear(){
    _mutex.Lock();
    std::list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        (*itor)->stop();
        pthread_join((*itor)->get_thread_id(), NULL);
        ++itor;
    }
    _thread_list.clear();
    _mutex.Unlock();
}

void ThreadMgr::on_timer(){
    check_threads();
}

void ThreadMgr::check_threads(){
    LogDebug("check threads");
    std::list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        if((*itor)->get_missed_hands() >= 5){
            LogDebug("thread %d is dead", (*itor)->get_thread_id());
        }else{
            (*itor)->shake(UNSHAKE);
        }
        ++itor;
    }
}

int ThreadMgr::thread_count(){
    return _thread_list.size();
}

#ifdef DEBUG
void ThreadMgr::print(){
    std::list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        (*itor)->shake(SHAKE);
        ++itor;
    }
}
#endif

