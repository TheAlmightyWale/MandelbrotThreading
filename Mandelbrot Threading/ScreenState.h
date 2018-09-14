// (c) 2014 Media Design School
//
// File Name	: ScreenState.h
// Description	: Header for the ScreenState Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#ifndef __SCREEN_STATE_H__
#define __SCREEN_STATE_H__

#include<Windows.h>
#include<vector>

//Class needed as SetPixel function can only be accessed by the main thread
// meaning we have to store the calculated colours and then draw them using the main thread


class ScreenState
{
public:
	ScreenState();
	ScreenState(int _iScreenWidth, int _iScreenHeight, HWND& _rHwnd, HDC& _rHDC);
	~ScreenState();

	//Draw Screen based on data held in m_colors
	void DrawScreen();

	//Sets the pixel at _x,_y with the color defined by _color
	void SetPixelColour(int _x, int _y, COLORREF _color);

private:
	//Vector holding the color of each pixel within the window
	std::vector<COLORREF> m_colors;

	HWND& m_rHWND;
	HDC& m_rHDC;

	int m_iScreenHeight;
	int m_iScreenWidth;

};

#endif //__SCREEN_STATE_H__