#pragma once
#ifndef __FPS_H_INCLUDED__
#define __FPS_H_INCLUDED__

#include "DxLib.h"

//===============================================================
// FPSクラス
//===============================================================
class CFPS
{
private:
	int		m_iStartTime;
	int		m_iCount;
	float	m_fFps;
	int		N = 60;
	int		FPS = 60;
	int		m_iX = 0, m_iY = 0;

public:
	//コンストラクタ
	CFPS(int x = 0, int y = 0, int fps = 60)
	{
		m_iStartTime = 0;
		m_iCount = 0;
		m_fFps = 0;
		N = FPS = fps;
		m_iX = x, m_iY = y;
	}

	//更新
	void Update() 
	{
		if (m_iCount == 0) 
		{
			m_iStartTime = GetNowCount();
		}
		if (m_iCount == N) 
		{
			int t = GetNowCount();
			m_fFps = 1000.0f / ((t - m_iStartTime) / (float)N);
			m_iCount = 0;
			m_iStartTime = t;
		}
		m_iCount++;
	}

	//描画
	void Draw() 
	{
		DrawFormatString(m_iX, m_iY, GetColor(0, 0, 0), "%.2f FPS", m_fFps);
	}

	//調整
	void Wait() 
	{
		int iTookTime = GetNowCount() - m_iStartTime;
		int iWaitTime = m_iCount * 1000 / FPS - iTookTime;
		if (iWaitTime > 0) 
		{
			Sleep(iWaitTime);
		}
	}
};

#endif



