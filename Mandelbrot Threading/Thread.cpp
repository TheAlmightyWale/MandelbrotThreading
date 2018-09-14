// (c) 2014 Media Design School
//
// File Name	: Thread.cpp
// Description	: Implements the Thread Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

//This Include
#include "Thread.h"

Thread::Thread()
:m_iDetached(0), m_iRunning(0)
{
	m_iThreadID = iThreadCount;
	iThreadCount++;
}

Thread::~Thread()
{
	if (m_iRunning == 1 && m_iDetached == 0)
	{
		pthread_detach(m_tid);
	}
	if (m_iRunning == 1)
	{
		pthread_cancel(m_tid);
	}
}

static void* runThread(void* arg)
{

	((Thread*)arg)->run();
	return (arg);
}

int Thread::Start()
{
	int result = pthread_create(&m_tid, NULL, runThread, this);

	if (result == 0)
	{
		m_iRunning = 1;
	}

	return (result);
}

int Thread::Join()
{
	int result = -1;

	if (m_iRunning == 1)
	{
		result = pthread_join(m_tid, NULL);

		if (result == 0)
		{
			m_iDetached = 1;
		}
	}

	return (result);
}

int Thread::Detach()
{
	int result = -1;

	if (m_iRunning == 1 && m_iDetached == 0)
	{
		result = pthread_detach(m_tid);
		if (result == 0)
		{
			m_iDetached = 0;
		}
	}

	return (result);
}

int Thread::Stop()
{
	return (0);
}


int Thread::Resume()
{
	return (0);
}

unsigned int Thread::GetThreadID() const
{
	return (m_iThreadID);
}

pthread_t Thread::self()
{
	return (m_tid);
}