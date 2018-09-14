// (c) 2014 Media Design School
//
// File Name	: ScreenState.cpp
// Description	: Implements the ScreenState Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#include "ScreenState.h"

ScreenState::ScreenState(int _iScreenWidth, int _iScreenHeight, HWND& _rHwnd, HDC& _rHDC)
: m_rHDC(_rHDC)
, m_rHWND(_rHwnd)
{

	m_iScreenHeight = _iScreenHeight;
	m_iScreenWidth = _iScreenWidth;

	for (int i = 0; i < _iScreenHeight * _iScreenWidth; i++)
	{
		COLORREF color = RGB(0, 0, 0);
		m_colors.push_back(color);
	}
}

ScreenState::~ScreenState()
{
}

void ScreenState::DrawScreen()
{
	for (int i = 0; i < m_iScreenHeight; i++)
	{
		for (int j = 0; j < m_iScreenWidth; j++)
		{
			SetPixel(m_rHDC, i, j, m_colors[j + i * m_iScreenHeight]);
		}
	}
}

void ScreenState::SetPixelColour(int _x, int _y, COLORREF _color)
{
	m_colors[_x + _y * m_iScreenHeight] = _color;
}