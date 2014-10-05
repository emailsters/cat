#include "condition.h"
#include "mutex_lock.h"
#include "mutex_guard.h"
#include "thread.h"
#include "runner.h"
#include "log.h"
#include <unistd.h>
#include <pthread.h>

class Task : public Runner{
public:
	Task():_condition(&_mutex_lock){}
	~Task(){}

    void svc(){
        MUTEX_GUARD_RETURN(&_mutex_lock);
		Log::i("task", "sleep");
		sleep(3);
		Log::i("task", "sleep end");
		Log::i("task", "thead wait");
		_condition.wait();
		Log::i("task", "wait end");
		sleep(3);
		Log::i("task", "hello world");
    }
	
	void notify(){
		MUTEX_GUARD_RETURN(&_mutex_lock);
		_condition.notify_all();
	}
private:
	MutexLock _mutex_lock;
	Condition _condition;
};

int main(){
	Task *runner = new Task;
	Thread *thread1 = new Thread(runner);
	Thread *thread2 = new Thread(runner);
	thread1->start();
	thread2->start();
	Log::i("main", "start thread");
	sleep(10);

	Log::i("main", "notify");
	runner->notify();
	//runner->notify();
	sleep(3);
	//Log::i("main", "notify");
	
	//sleep(3);
	thread1->join();
	thread2->join();
	return 0;
}