#include "thread_pool.h"
#include "runner.h"
#include "log.h"
#include <unistd.h>

class MyTask : public Runner{
public:
    MyTask(string name):_name(name){}
    
    void svc(){
        int i = 0;
        while(i < 3){
            sleep(1);
            LogDebug("Task");
            ++i;
        }        
    }
    
private:
    string _name;
};

class MyTask2 : public Runner{
public:
    MyTask2(string name):_name(name){}
    
    void svc(){
        int i = 0;
        while(i < 3){
            sleep(2);
            LogDebug("Task");
            ++i;
        }        
    }
    
private:
    string _name;
};


int main(){
    LogInit();
    ThreadPool *tp = new ThreadPool("thead pool");
    tp->start(3);
    Runner *task1 = new MyTask("task 1");
    //Runner *task2 = new MyTask("task 2");
    Runner *task3 = new MyTask("task 3");
    Runner *task4 = new MyTask("task 4");
    Runner *task5 = new MyTask("task 5");
    Runner *task6 = new MyTask("task 6");
    Runner *task2 = new MyTask2("task 7");
    
    tp->push_task(task1);

    tp->push_task(task2);

    sleep(5);
    
    tp->push_task(task3);
    sleep(5);
    tp->push_task(task4);
    sleep(6);
    LogDebug("task in queue:%d", tp->tasks_in_queue());
    tp->push_task(task5);
    tp->push_task(task6);
    //tp->push_task(task7);

    LogDebug("task in queue:%d", tp->tasks_in_queue());

    //sleep(30);
    tp->stop(); //释放资源会等待线程执行完毕，如果Runner类的svc方法是死循环，这里会导致线程挂死
    delete tp; 
    LogDebug("end");
    LogFini();
    return 0;
}

