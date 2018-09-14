// (c) 2014 Media Design School
//
// File Name	: Structs.h
// Description	: Defines the PixelToDraw struct and MandelbrotInfo struct.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//


#ifndef __STRUCTS_H__
#define __STRUCTS_H__

//Pixel co-ordinates of a pixel that needs to be updated
struct PixelToDraw
{
	int x;
	int y;
	int iLinesToDraw;
};

//Values used in the drawing and calculation of the mandelbrot Fractal
struct MandelbrotInfo
{
	float m_fCenterX;
	float m_fCenterY;

	float m_fZoomFactor;

	int m_iTimesZoomed;

	int m_iDivergenceLimit;

	int m_iWindowHeight;
	int m_iWindowWidth;
};


#endif //__STRUCTS_H__