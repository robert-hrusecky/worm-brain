
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// TODO update so it only runs tasks once. Match code in ~/tmp/test.cpp

namespace EvolutionSimulator
{

template <typename T> class ThreadPool
{
public:
	ThreadPool(std::function<void(T)> task) : m_task(task) {}
	virtual ~ThreadPool()
	{
		if (isRunning())
		{
			stop(true); 
		}
	}

	void start(unsigned int numThreads = 0);
	bool isDone();
	bool isRunning();
	void stop(bool force = false);
	void enqueue(const std::vector<T>& data);

private:
	void workerThread();

	std::function<void(T)> m_task;

	std::vector<std::thread> m_threads;

	std::queue<T> m_queue;
	bool m_isRunning = false;
	bool m_forceStop = false;
	unsigned int m_tasksLeft = 0;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};

} /* namespace EvolutionSimulator */

#include "ThreadPool.tpp"

#endif /* THREADPOOL_H_ */