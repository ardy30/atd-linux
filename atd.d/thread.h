// thread.h
#ifndef __thread_h__
#define __thread_h__
#include "atd.h"
using namespace atd;
#include <pthread.h>
#include <semaphore.h>
struct mutex : public object
{
	pthread_mutex_t mx;
	mutex();
	~mutex();
	void lock();
	void unlock();
};
struct semaphore : public object
{
	sem_t sm;
	semaphore();
	~semaphore();
	void post();
	void wait();
};
struct cond : public object
{
	pthread_cond_t cd;
	cond();
	~cond();
	void signal();
	void wait();
};
struct thread : public object
{
	typedef generic::function<void, void> function;
	pthread_t th;
	thread(const function &func);
	~thread();
	void *kernel();
	void join();
};
#endif//__thread_h__



