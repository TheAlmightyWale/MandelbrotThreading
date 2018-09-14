// (c) 2014 Media Design School
//
// File Name	: Thread.h
// Description	: Defines the Thread Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#ifndef __THREAD_H__
#define __THREAD_H__

//Posix threading include
#include <pthread.h>

static int iThreadCount = 0;

class Thread
{
	//Member Functions
public:
	Thread(); // Constructor of class
	virtual ~Thread(); // Virtual deconstructor

	int Start();	//This function creates the thread and then causes the thread to begin execution
	int Join();		//This function forces the calling thread to wait for the thread on which it is invoked to complete
	int Stop();		// This function stops the currently running thread
	int Resume();	// Resumes the stopped thread
	int Detach();

	virtual void* run() = 0;				//Virtual function that will be the entry point of the created thread

	unsigned int GetThreadID() const; //Function retrieves a threads ID;
	pthread_t self();

	//Member Variables
private:

	int m_iThreadID;
	int m_iRunning;
	int m_iDetached;

	pthread_t m_tid;

};

#endif // __THREAD_H__
