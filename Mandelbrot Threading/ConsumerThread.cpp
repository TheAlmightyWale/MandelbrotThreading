// (c) 2014 Media Design School
//
// File Name	: ConsumerThread.cpp
// Description	: Implements the ConsumerThread Class.
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//

#include "ConsumerThread.h"

ConsumerThread::ConsumerThread(WorkQueue<PixelToDraw*>& _rQueue, MandelbrotInfo& _rInfo, ScreenState& _rScreenState )
	:m_rQueue(_rQueue)
	, m_rInfo(_rInfo)
	, m_rScreenState(_rScreenState)
{
}

void* ConsumerThread::run()
{
		PixelToDraw* px = m_rQueue.RemoveWorkItem();

		for(int i = 0; i < px->iLinesToDraw ; i++)
		{
			for(int j = 0; j < m_rInfo.m_iWindowWidth; j++)
			{

				//Variables for calculating the iterations
				float a1 = 0.0f;
				float b1 = 0.0f;
				float a2 = 0.0f;
				float b2 = 0.0f;

				//Actual position of pixel in relation to the mandelbrot set.
				float aX = 0.0f;
				float aY = 0.0f;

				//Convergence limit
				int iConvergenceLimit = 0;

				//Mathematical value of the point
				aX = (m_rInfo.m_fCenterX + px->x + j) * (1 - m_rInfo.m_fZoomFactor);
				aY = (m_rInfo.m_fCenterY + px->y + i) * (1 - m_rInfo.m_fZoomFactor);

				a1 = aX;
				b1 = aY;

				while (iConvergenceLimit < 256 && ((a1*a1) + (b1*b1) < m_rInfo.m_iDivergenceLimit))
				{
					iConvergenceLimit++;

					a2 = (a1*a1) - (b1*b1) + aX;
					b2 = (2 * a1 * b1) + aY;

					a1 = a2;
					b1 = b2;
				}

				if (iConvergenceLimit > 255)
				{
					m_rScreenState.SetPixelColour(px->x + j, px->y + i, RGB(0, 0, 0));
				}
				else
				{
					float fModulus = std::sqrtf((a1*a1) + (b1 * b1));
					float mu = (float)(iConvergenceLimit++ - (log(log(abs(fModulus)))) / log(2.0));
					float hue = 0.95f + (20.0f * mu); //Adjustment for aesthetic presentation

					//HSV function expects a value from 0 to 360
					while (hue > 360.0f)
					{
						hue -= 360.0f;
					}

					while (hue < 0.0f)
					{
						hue += 360.0f;
					}

					m_rScreenState.SetPixelColour(px->x + j, px->y + i, ColorFromHSV(hue, 0.8f, 255.0f));
				}
			}
		}

		delete px;
		px = 0;


	return (0);
}


//Taken from http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
COLORREF ConsumerThread::ColorFromHSV(float _hue, float _saturation, float _value)
{
	double      hh, p, q, t, ff;
	long        i;
	COLORREF out;

	if (_saturation <= 0.0) {       // < is bogus, just shuts up warnings
		out = RGB(_value, _value, _value);
	}
	hh = (double)_hue;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = _value * (1.0 - _saturation);
	q = _value * (1.0 - (_saturation * ff));
	t = _value * (1.0 - (_saturation * (1.0 - ff)));

	switch (i) {
	case 0:
		out = RGB(_value, t, p);
		break;
	case 1:
		out = RGB(q, _value, p);
		break;
	case 2:
		out = RGB(p, _value, t);
		break;

	case 3:
		out = RGB(p, q, _value);
		break;
	case 4:
		out = RGB(t, p, _value);
		break;
	case 5:
	default:
		out = RGB(_value, p, q);
		break;
	}

	return (out);
}