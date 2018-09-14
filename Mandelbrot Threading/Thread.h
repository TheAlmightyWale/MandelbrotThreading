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
#include <thread>

static int iThreadCount = 0;

class BaseThread
{
	//Member Functions
public:
	BaseThread(); // Constructor of class
	virtual ~BaseThread(); // Virtual deconstructor

	void Start();	//This function creates the thread and then causes the thread to begin execution
	void Join();		//This function forces the calling thread to wait for the thread on which it is invoked to complete
	int Stop();		// This function stops the currently running thread
	int Resume();	// Resumes the stopped thread
	void Detach();
	bool isJoinable();

	virtual void* run() = 0;				//Virtual function that will be the entry point of the created thread

	unsigned int GetThreadID() const; //Function retrieves a threads ID;

	//Member Variables
private:

	int m_iThreadID;
	int m_iRunning;
	int m_iDetached;

	std::thread* m_thread;

};

#endif // __THREAD_H__
