#ifndef _THREAD_MGR_H_
#define _THREAD_MGR_H_
#include "monitor_thread.h"
#include <iostream>
#include <list>
#include "timer_thread.h"

using namespace std;

class ThreadMgr : public CTimerThread
{
public:
    static ThreadMgr* instance();
    
    int regist(MonThread *thread);
    
    int unregist(MonThread *thread);
    
    void clear();
    
    void on_timer();

    int thread_count();
    
#ifdef DEBUG
    void print();
#endif

private:
    ThreadMgr();
    
    ~ThreadMgr();
    
    ThreadMgr(const ThreadMgr &thread_mgr);
    
    ThreadMgr operator=(const ThreadMgr &thread_mgr);
    
    void check_threads();

    class Garbo{
    public:
        ~Garbo(){
            if(ThreadMgr::_thread_mgr != NULL){
                delete ThreadMgr::_thread_mgr;
                ThreadMgr::_thread_mgr = NULL;
            }                
        }
    };
    static Garbo _garbo;
    
private:
    list<MonThread*> _thread_list;
    
    static ThreadMgr *_thread_mgr;
    
};

#endif

