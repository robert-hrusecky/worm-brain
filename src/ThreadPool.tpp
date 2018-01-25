
#include "ThreadPool.h"
#include <exception>

namespace EvolutionSimulator
{

template <typename T> void ThreadPool<T>::start(unsigned int numThreads)
{
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		if (m_isRunning)
		{
			throw std::logic_error("Threads already started.");
		}
	}

	if (numThreads == 0)
	{
		numThreads = std::thread::hardware_concurrency();
	}

	m_isRunning = true;

	m_threads.reserve(numThreads);
	for (unsigned int i = 0; i < numThreads; i++)
	{
		m_threads.emplace_back(&ThreadPool::workerThread, this);
	}
}

template <typename T> bool ThreadPool<T>::isDone() {
	std::lock_guard<std::mutex> locker(m_mutex);
	return m_tasksLeft == 0;
}

template <typename T> bool ThreadPool<T>::isRunning() {
	std::lock_guard<std::mutex> locker(m_mutex);
	return m_isRunning;
}

template <typename T> void ThreadPool<T>::stop()
{
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		if (!m_isRunning)
		{
			throw std::logic_error("Threads not started yet.");
		}
		m_isRunning = false;
	}
	m_condition.notify_all();
	for (auto& thread : m_threads)
	{
		thread.join();
	}
}

template <typename T> void ThreadPool<T>::enqueue(const std::vector<T>& data)
{
	{
		std::lock_guard<std::mutex> locker(m_mutex);
		for (const auto& datum : data)
		{
			m_queue.push(datum);
		}
		m_tasksLeft += data.size();
	}
	m_condition.notify_all();
}

template <typename T> void ThreadPool<T>::workerThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> locker(m_mutex);
		m_condition.wait(locker, [=]() { return !m_queue.empty() || !m_isRunning; });
		if (!m_isRunning && m_queue.empty())
		{
			break;
		}
		T task = m_queue.front();
		m_queue.pop();
		locker.unlock();

		m_task(task);

		locker.lock();
		m_tasksLeft--;
		locker.unlock();
	}
}
}