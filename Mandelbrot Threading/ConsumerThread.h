// (c) 2014 Media Design School
//
// File Name	: ConsumerThread.h
// Description	: Implements the ConsumerThread Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#ifndef __CONSUMER_THREAD_H__
#define __CONSUMER_THREAD_H__

#include<Windows.h>

#include "Thread.h"
#include "WorkQueue.h"
#include "ScreenState.h"


class ConsumerThread : public BaseThread
{
public:

	//Create Consumer thread
	ConsumerThread(WorkQueue<PixelToDraw*>& _rQueue, MandelbrotInfo& _rInfo, ScreenState& _rScreenState);

	//Calculate if pixel taken from m_rQueue is within the mandelbrot fractal or not. Then set the colour of the pixel int m_rScreenState based on this
	void* run();

private:

	COLORREF ColorFromHSV(float _hue, float _saturation, float _value);

	WorkQueue<PixelToDraw*> &m_rQueue;

	MandelbrotInfo& m_rInfo;
	ScreenState& m_rScreenState;

};

#endif //__CONSUMER_THREAD_H__