#ifndef _THREAD_H_
#define _THREAD_H_
#include <pthread.h>
#include "runner.h"

struct HookParam;

typedef struct HookParam hook_param_t;

/*
  *使用thread有两种方式
  *一种是继承thread，重写svc方法
  *另一种是实现runner接口，创建thread的时候传入
*/

class Thread{
public:
    Thread();
    
    Thread(Runner *thread_runner);
    
    virtual ~Thread();

    virtual void start();

    virtual void join();

    virtual void set_runner(Runner *runner);

    virtual void svc();

    pthread_t get_thread_id();

protected:
        pthread_t _thread_id;

private:    
    bool _started;
    
    Runner *_runner;

    hook_param_t *_hook_param;
};

#endif

