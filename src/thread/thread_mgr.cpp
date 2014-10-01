#include "thread_mgr.h"
#include "types.h"
#include "monitor_thread.h"
#include <iostream>
#include "log.h"

#define LOG_THREAD_MGR "ThreadMgr"

ThreadMgr* ThreadMgr::_thread_mgr = NULL;

ThreadMgr::ThreadMgr(){
    set_timer(1);
}

ThreadMgr* ThreadMgr::instance()
{
    if(NULL == _thread_mgr){
        _thread_mgr = new ThreadMgr;
    }
    return _thread_mgr;
}

ThreadMgr::~ThreadMgr()
{
   clear();    
    kill_timer();
}

int ThreadMgr::regist(MonThread *thread)
{
    _thread_list.push_back(thread);
    return RET_OK;
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
    if(_thread_list.empty()){
        Log::i(LOG_THREAD_MGR, "list is emtpy");
        return false;
    }
    list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        if((*itor) == thread){
            _thread_list.erase(itor);
            return RET_OK;
        }
        ++itor;
    }
    Log::i(LOG_THREAD_MGR, "can not find thread");
    return RET_ERR;
}

void ThreadMgr::clear(){
    std::list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        (*itor)->stop();
        pthread_join((*itor)->get_thread_id(), NULL);
        ++itor;
    }
    _thread_list.clear();
}

void ThreadMgr::on_timer(){
    check_threads();
}

void ThreadMgr::check_threads(){
    Log::i(LOG_THREAD_MGR, "check threads");
    std::list<MonThread*>::iterator itor = _thread_list.begin();
    while(itor != _thread_list.end()){
        if((*itor)->get_missed_hands() >= 5){
            Log::i(LOG_THREAD_MGR, "thread %d is dead", (*itor)->get_thread_id());
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

