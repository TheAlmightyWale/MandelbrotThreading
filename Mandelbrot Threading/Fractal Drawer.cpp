// (c) 2014 Media Design School
//
// File Name	: FractalDrawer.cpp
// Description	: Implements the FractalDrawer Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

//This Include
#include "Fractal Drawer.h"

#include<cmath>

FractalDrawer::FractalDrawer(HWND _hwnd, HDC _hdc, int _winHeight, int _winWidth)
	: m_screenState(_winWidth, _winHeight, m_hwnd, m_hdc)
	, m_fFracCalcFinTime(0.0f)
	, m_fFracDrawnFinTime(0.0f)
	, m_fFracStartTime(0.0f)
	, m_bTimeShownThisDraw(false)
	, m_iThreadNumber(0)
{
	m_info.m_fCenterX = -300.0f;
	m_info.m_fCenterY = -300.0f;
	m_info.m_fZoomFactor = 0.992f;
	m_info.m_iTimesZoomed = 0;
	m_info.m_iDivergenceLimit = 18;

	m_hwnd = _hwnd;
	m_hdc = _hdc;
	m_info.m_iWindowHeight = _winHeight;
	m_info.m_iWindowWidth = _winWidth;

	//Get thread count from file
	std::ifstream f;
	std::streamsize size = 100;
	int iThreadNum = 0;
	f.open("ThreadNumber.txt");

	if (f.is_open())
	{
		while (!f.eof())
		{
			char temp[100];
			f.getline(&temp[0], size);
			f.getline(&temp[0], size);
			iThreadNum = atoi(&temp[0]);
		}
	}
	f.close();

	m_iThreadNumber = iThreadNum;

	//Create appropriate number of consumer threads based on thread count
	for (int i = 0; i < iThreadNum; i++)
	{
		ConsumerThread* pThread = new ConsumerThread(m_pixelQueue, m_info, m_screenState);
		m_consumers.push_back(pThread);
	}

	for (int i = 0; i < iThreadNum; i++)
	{
		m_consumers[i]->Start();
	}

	Draw();

}

FractalDrawer::~FractalDrawer()
{
	ReleaseDC(m_hwnd, m_hdc);

	DeleteThreads();
}

void FractalDrawer::DeleteThreads()
{
	for (int i = 0; i < m_iThreadNumber; i++)
	{
		ConsumerThread* temp = m_consumers.back();;
		m_consumers.pop_back();
		delete temp;
		temp = 0;
	}
}

void FractalDrawer::CreateThreads()
{
	for (int i = 0; i < m_iThreadNumber; i++)
	{
		ConsumerThread* pThread = new ConsumerThread(m_pixelQueue, m_info, m_screenState);
		m_consumers.push_back(pThread);
	}

	for (int i = 0; i < m_iThreadNumber; i++)
	{
		m_consumers[i]->Start();
	}
}

void FractalDrawer::Zoom(float _zoom)
{
	m_bTimeShownThisDraw = false;

	if (_zoom > 0)
	{
		m_info.m_iTimesZoomed++;
	}
	else
	{
		if (m_info.m_iTimesZoomed == 0)
		{
			m_info.m_iTimesZoomed--;
		}
	}

	float fZoomAsymptote = ((float)m_info.m_iTimesZoomed * (float)m_info.m_iTimesZoomed) / 5.0f;

	m_info.m_fZoomFactor += _zoom / fZoomAsymptote;
	Draw();
}

void FractalDrawer::TranslateHorizontally(int _translation)
{
	m_bTimeShownThisDraw = false;
	m_info.m_fCenterY += _translation;
	Draw();
}

void FractalDrawer::TranslateVertically(int _translation)
{
	m_bTimeShownThisDraw = false;
	m_info.m_fCenterX -= _translation;
	Draw();
}

void FractalDrawer::Draw()
{
	//Set Time Frac has started being calculated	
	m_timer.tick();
	m_fFracStartTime = m_timer.getGameTime();

	int iLinesToDraw = m_info.m_iWindowWidth /m_consumers.size();

	//Producer thread adds lines of pixels and consumers take pixels and calculate - add
	for (int i = 0; i < m_info.m_iWindowWidth; i += iLinesToDraw)
	{
		PixelToDraw* pPixel = new PixelToDraw();
		pPixel->x = 0;
		pPixel->y = i;
		pPixel->iLinesToDraw = iLinesToDraw;
		m_pixelQueue.AddWorkItem(pPixel);
	}
}

void FractalDrawer::UpdateScreen()
{

	for (int unsigned i = 0; i < m_consumers.size(); i++)
	{
		m_consumers[i]->Join();
	}

	m_timer.tick();

	//Queue has been processed so Fractal has finished being calculated
	m_fFracCalcFinTime = m_timer.getGameTime();

	if (!m_bTimeShownThisDraw)
	{
		m_screenState.DrawScreen();

		//Get time taken to calculate and draw
		m_timer.tick();
		m_fFracDrawnFinTime = m_timer.getGameTime();

		std::wstring calcTime = L"Calculation Time: " + std::to_wstring((long double)(m_fFracCalcFinTime - m_fFracStartTime))
			+ L"\n" + L"Calc and Draw Time: " + std::to_wstring((long double)(m_fFracDrawnFinTime - m_fFracStartTime));

		MessageBox(m_hwnd, calcTime.c_str(), L"Time Taken", NULL);
		m_bTimeShownThisDraw = true;
	}

	if (GetAsyncKeyState(VK_ADD))
	{
		Zoom(0.001f);
		DeleteThreads();
		CreateThreads();
	}

	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		Zoom(-0.001f);
		DeleteThreads();
		CreateThreads();
	}

	if (GetAsyncKeyState(VK_UP))
	{
		TranslateVertically(50);
		DeleteThreads();
		CreateThreads();
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		TranslateHorizontally(50);
		DeleteThreads();
		CreateThreads();
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		TranslateVertically(-50);
		DeleteThreads();
		CreateThreads();
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		TranslateHorizontally(-50);
		DeleteThreads();
		CreateThreads();
	}

}