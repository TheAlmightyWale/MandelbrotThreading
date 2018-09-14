// (c) 2014 Media Design School
//
// File Name	: Fractal Drawer.h
// Description	: Header for the FractalDrawer Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#ifndef __FRACTAL_DRAWER_H__
#define __FRACTAL_DRAWER_H__

#include<Windows.h>
#include<vector>
#include<string>
#include<fstream>
#include<iostream>

#include "WorkQueue.h"
#include "ConsumerThread.h"
#include "Timer.h"


class FractalDrawer
{
	//Member Functions
public:
	FractalDrawer(HWND _hwnd, HDC _hdc, int _winHeight, int _winWidth);
	~FractalDrawer();

	//Draws the current screen with the data held in m_screenState
	void UpdateScreen();
	
	//Zoom or translate the mandelbrot picture before calling draw
	void Zoom(float _zoomAmount);
	void TranslateHorizontally(int _translation);
	void TranslateVertically(int _translation);

private:
	//Add pixels to be calculated by consumer threads to the work queue based on current mandelbrot Info within m_Info
	void Draw();
	void DeleteThreads();
	void CreateThreads();

	//Member Variables
private:

	HWND m_hwnd;
	HDC m_hdc;

	WorkQueue<PixelToDraw*> m_pixelQueue;

	std::vector<ConsumerThread*> m_consumers;

	MandelbrotInfo m_info;

	ScreenState m_screenState;

	GameTimer m_timer;

	float m_fFracStartTime;
	float m_fFracCalcFinTime;
	float m_fFracDrawnFinTime;

	//Prevent Time message continuously appearing while app is idle
	bool m_bTimeShownThisDraw;

	int m_iThreadNumber;

};



#endif // !__FRACTAL_DRAWER_H__
