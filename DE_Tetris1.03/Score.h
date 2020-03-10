#pragma once
#ifndef __SCORE_H_INCLUDED__
#define __SCORE_H_INCLUDED__

#include "Game.h"

//===============================================================
// スコアクラス
//===============================================================
class CScore
{
public:
	//スコア
	int m_iLevel = 0;
	int m_iLines = 0;
	int m_iScore = 0;

public:
	//コンストラクタ.デストラクタ
	CScore();
	~CScore();

private:
	//セッター
	inline void SetLevel() { m_iLevel = g_cGame->m_iLevel; }
	inline void SetLines() { m_iLines = g_cGame->m_iFullLines; }
	inline void SetScore() { m_iScore = g_cGame->m_iScore; }

public:
	//ゲッター
	int GetLevel() { SetLevel(); return m_iLevel; }
	int GetLines() { SetLines(); return m_iLines; }
	int GetScore() { SetScore(); return m_iScore; }
};

#endif 



