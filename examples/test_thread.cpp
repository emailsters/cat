#include <iostream>
#include "log.h"
#include "thread.h"
#include "runner.h"
#include <unistd.h>
#include "monitor_thread.h"
#include "thread_mgr.h"

class MyRunner : public Runner{
public:
    void svc(){
        while(1){
            sleep(2);
            LogDebug("my runner is running");
        }
    }
};

class MyThread : public Thread{
public:
    void svc(){
        while(1){
            sleep(2);
            LogDebug("my thread is running");
        }
    }
};

class MyMonThread : public MonThread{
public:
    void do_task(){
        sleep(1);
        LogDebug("doing task");
    }
};

int main(){
    /*
    Runner *runner = new MyRunner();
    Thread *thread = new Thread(runner);

    MyThread *my_thread = new MyThread;
    my_thread->start();
    
    thread->start();

    thread->join();

    my_thread->join();
    delete my_thread;
    delete thread;
    delete runner;
    */
    LogInit();
    MyMonThread *thread1 = new MyMonThread;
    MyMonThread *thread2 = new MyMonThread;
    MyMonThread *thread3 = new MyMonThread;
    MyMonThread *thread4 = new MyMonThread;
    MyMonThread *thread5 = new MyMonThread;
    ThreadMgr *thread_mgr = ThreadMgr::instance();
    LogDebug("thread cout:%d", thread_mgr->thread_count());
    
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
    thread5->start();
    sleep(20);
    thread1->stop();
    thread2->stop();
    thread3->stop();
    thread4->stop();
    thread5->stop();
    
    thread1->join();
    thread2->join();
    thread3->join();
    thread4->join();
    thread5->join();
    
    delete thread1;
    delete thread2;
    delete thread3;
    delete thread4;
    delete thread5;
    LogFini();
    return 0;
}

