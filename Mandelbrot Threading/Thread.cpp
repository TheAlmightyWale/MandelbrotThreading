// (c) 2014 Media Design School
//
// File Name	: Thread.cpp
// Description	: Implements the Thread Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

//This Include
#include "Thread.h"

BaseThread::BaseThread()
:m_iDetached(0), m_iRunning(0)
{
	m_iThreadID = iThreadCount;
	iThreadCount++;
	m_thread = nullptr;
}

BaseThread::~BaseThread()
{
	delete m_thread;
	m_thread = nullptr;
}

static void* runThread(void* arg)
{
	((BaseThread*)arg)->run();
	return (arg);
}

void BaseThread::Start()
{
	m_thread = new std::thread(runThread, this);
}

void BaseThread::Join()
{
	m_thread->join();
}

void BaseThread::Detach()
{
	m_thread->detach();
}

int BaseThread::Stop()
{
	return (0);
}

bool BaseThread::isJoinable() {
	return m_thread->joinable();
}


int BaseThread::Resume()
{
	return (0);
}

unsigned int BaseThread::GetThreadID() const
{
	return (m_iThreadID);
}