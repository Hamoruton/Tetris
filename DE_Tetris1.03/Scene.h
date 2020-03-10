#pragma once
#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Color.h"
#include "GUI.h"
#include "Score.h"
#include "Transition.h"
#include "Sound.h"
#include "FPS.h"

//===============================================================
// シーンクラス
//===============================================================
class CScene
{
public:
	//ゲームの状態変数
	const enum SCENESTATUS
	{
		TITLE = 0,
		GAMEFADEOUTTRANSITION = 5,
		GAMEFADEINTRANSITION = 6,
		GAMEREADY = 7,
		GAME = 10,
		RESULTTRANSITION = 15,
		RESULT = 100,
		TITLETRANSITION = 105,
		EXIT = 1000,
	};

	SCENESTATUS m_eSceneStatus = TITLE;

public:
	//タイトルクラス
	CTitle* m_cTitle;
	//リザルトクラス
	CResult* m_cResult;
	//カラークラス
	CColor* m_cColor;
	//GUIクラス
	CGUI* m_cGUI;
	//スコアクラス
	CScore* m_cScore;
	//トランジションクラス
	CTransition* m_cTransition;
	//サウンドクラス
	CSound* m_cSound;

	//キー情報配列
	int m_iKey[256] = { 0 };

public:
	//コンストラクタ.デストラクタ
	CScene();
	~CScene();

	//更新
	void Update();

	//入力処理
	bool InputKey();
};
extern CScene* g_cScene;

#endif



