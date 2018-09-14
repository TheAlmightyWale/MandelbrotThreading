// (c) 2014 Media Design School
//
// File Name	: WorkQueue.h
// Description	: Defines the WorkQueue Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#ifndef __WORK_QUEUE_H__
#define __WORK_QUEUE_H__

//Local includes
#include "Thread.h"
#include "Structs.h"

//Library Includes
#include <list>
#include <mutex>

//Class implmentation
template <typename T>
class WorkQueue
{

private:
	std::list<T> m_queue;
	std::mutex m_mutex;
	pthread_cond_t m_condv;

public:
	WorkQueue()
	{
		pthread_cond_init(&m_condv, NULL);
	}

	~WorkQueue()
	{
		pthread_cond_destroy(&m_condv);
	}

	//Adds a work item to the queue, while blocking consumers from accessing it
	//Also calls consumers threads to wake if the queue was previously empty
	void AddWorkItem(T item)
	{
		m_mutex.lock();
		m_queue.push_back(item);
		pthread_cond_signal(&m_condv);
		m_mutex.unlock();
	}

	//Removes a work item from the queue, while blocking other threads from accessing it
	//Also puts consumer threads to sleep if queue is empty
	T RemoveWorkItem()
	{
		m_mutex.lock();

		while (m_queue.size() == 0)
		{
			pthread_cond_wait(&m_condv, &m_mutex);
		}

		T item = m_queue.front();
		m_queue.pop_front();

		m_mutex.unlock();

		return (item);
	}

	int GetSize()
	{
		return (m_queue.size());
	}


};


#endif // !__WORK_QUEUE_H__
