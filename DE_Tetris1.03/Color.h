#pragma once
#ifndef __COLOR_H_INCLUDED__
#define __COLOR_H_INCLUDED__

#include "DxLib.h"

//===============================================================
// カラークラス
//===============================================================
class CColor
{
private:
	//カラー変数
	int m_iRed;
	int m_iOrange;
	int m_iYellow;
	int m_iGreen;
	int m_iPink;
	int m_iBlue;
	int m_iCyan;
	int m_iBlack;
	int m_iWhite;

public:
	//コンストラクタ.デストラクタ
	CColor();
	~CColor();

private:
	//セッター
	inline void SetRedColor() { m_iRed = GetColor(255, 0, 0); }
	inline void SetOrangeColor() { m_iOrange = GetColor(255, 165, 0); }
	inline void SetYellowColor() { m_iYellow = GetColor(255, 255, 0); }
	inline void SetGreenColor() { m_iGreen = GetColor(0, 255, 0); }
	inline void SetPinkColor() { m_iPink = GetColor(255, 0, 255); }
	inline void SetBlueColor() { m_iBlue = GetColor(0, 0, 255); }
	inline void SetCyanColor() { m_iCyan = GetColor(0, 255, 255); }
	inline void SetBlackColor() { m_iBlack = GetColor(0, 0, 0); }
	inline void SetWhiteColor() { m_iWhite = GetColor(255, 255, 255); }

public:
	//ゲッター
	int GetRedColor() { SetRedColor(); return m_iRed; }
	int GetOrangeColor() { SetOrangeColor(); return m_iOrange; }
	int GetYellowColor() { SetYellowColor(); return m_iYellow; }
	int GetGreenColor() { SetGreenColor(); return m_iGreen; }
	int GetPinkColor() { SetPinkColor(); return m_iPink; }
	int GetBlueColor() { SetBlueColor(); return m_iBlue; }
	int GetCyanColor() { SetCyanColor(); return m_iCyan; }
	int GetBlackColor() { SetBlackColor(); return m_iBlack; }
	int GetWhiteColor() { SetWhiteColor(); return m_iWhite; }
};

#endif



