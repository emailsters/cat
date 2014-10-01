#ifndef _CTIMER_THREAD_
#define _CTIMER_THREAD_
#include <pthread.h>

class CTimerThread {
public:
    CTimerThread();
    
    ~CTimerThread();
    
    virtual int set_timer(int interval);
    
    virtual void kill_timer();
    
    virtual void on_timer() = 0;
    
private:
    static void* hook(void *args);
    
    void exit();
    
private:
    pthread_t _thread_id;
    
    static int _interval;
    
    bool _started;

    static bool _not_exit;
   
};

#endif


