#pragma once
#ifndef __SOUND_H_INCLUDED__
#define __SOUND_H_INCLUDED__

//BGM
#define BGM_TITLE		"Assets/Sounds/BGMTitle.mp3"
#define BGM_GAME		"Assets/Sounds/BGMGame.mp3"
#define BGM_RESULT      "Assets/Sounds/BGMResult.mp3"

//SE
#define SE_BLOCK_MOVE   "Assets/Sounds/SEBlockMove.mp3"
#define SE_BLOCK_DOWN   "Assets/Sounds/SEBlockDown.mp3"
#define SE_BLOCK_CLEAR  "Assets/Sounds/SEBlockClear.mp3"
#define SE_LEVEL_UP     "Assets/Sounds/SELevelUp.mp3"
#define SE_COUNT_DOWN   "Assets/Sounds/SECountDown.mp3"

#define SE_DECISION     "Assets/Sounds/SEDecision.mp3"
#define SE_CURSOR_MOVE  "Assets/Sounds/SECursorMove.mp3"

//===============================================================
// トランジションクラス
//===============================================================
class CSound
{
public:
	//BGMハンドル
	int m_iBGMTitle;
	int m_iBGMGame;
	int m_iBGMResult;

	//SEハンドル
	int m_iSEBlockMove;
	int m_iSEBlockDown;
	int m_iSEBlockClear;
	int m_iSELevelUp;
	int m_iSECountDown;
	
	int m_iSEDecision;
	int m_iSECursorMove;

public:
	//コンストラクタ.デストラクタ
	CSound();
	~CSound();
};

#endif



