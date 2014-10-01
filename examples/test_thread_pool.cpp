#include "thread_pool.h"
#include "runner.h"
#include "log.h"
#include <unistd.h>

class MyTask1 : public Runner{
public:
    void svc(){
        int i = 0;
        while(i < 20){
            sleep(2);
            Log::i("MyTask 1", "MyTask 1");
            ++i;
        }        
    }
};

class MyTask2 : public Runner{
public:
    void svc(){
        int i = 0;
        while(i < 3){
            sleep(3);
            Log::i("MyTask 2", "MyTask 2");
            ++i;
        }
    }
};

class MyTask3 : public Runner{
public:
    void svc(){
        int i = 0;
        while(i < 3){
            sleep(1);
            Log::i("MyTask 3", "MyTask 3");
            ++i;
        }
    }
};

class MyTask4 : public Runner{
public:
    void svc(){
        int i = 0;
        while(i < 3){
            sleep(2);
            Log::i("MyTask 4", "MyTask 4");
            ++i;
        }
    }
};


int main(){
    ThreadPool *tp = new ThreadPool("thead pool");
    tp->start(2);
    Runner *task1 = new MyTask1;
    Runner *task2 = new MyTask2;
    Runner *task3 = new MyTask3;
    Runner *task4 = new MyTask4;
    tp->push_task(task1);
    Log::i("main", "1 task in queue:%d", tp->tasks_in_queue());
    tp->push_task(task2);
    Log::i("main", "2 task in queue:%d", tp->tasks_in_queue());
    tp->push_task(task3);
    Log::i("main", "3 task in queue:%d", tp->tasks_in_queue());
    tp->push_task(task4);
    Log::i("main", "4 task in queue:%d", tp->tasks_in_queue());
    sleep(10);
    Log::i("main", "5 task in queue:%d", tp->tasks_in_queue());
    sleep(30);
    Log::i("main", "6 task in queue:%d", tp->tasks_in_queue());
    sleep(100);
    Log::i("main", "7 task in queue:%d", tp->tasks_in_queue());
    tp->stop();
    delete tp; //释放资源会等待线程执行完毕，如果Runner类的svc方法是死循环，这里会导致线程挂死
    return 0;
}

