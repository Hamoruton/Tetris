#include "DxLib.h"
#include "Scene.h"

//===============================================================
// コンストラクタ
//===============================================================
CTitle::CTitle() 
{
	//DxLib初期化
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(255, 255, 255);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	//フォント読み込み
	m_iTitleFontHandle = CreateFontToHandle(FONT_CHIP, 80, 3);
	m_iMinTitleFontHandle = CreateFontToHandle(FONT_CHIP, 20, 3);
}

//===============================================================
// デストラクタ
//===============================================================
CTitle::~CTitle() 
{
	//フォント破棄
	DeleteFontToHandle(m_iTitleFontHandle);
	DeleteFontToHandle(m_iMinTitleFontHandle);

	//BGM停止
	StopSoundMem(g_cScene->m_cSound->m_iBGMTitle);
}

//===============================================================
// プレイヤー入力処理
//===============================================================
void CTitle::CheckUserInput() 
{
	//次のシーン状態選択
	if (g_cScene->m_iKey[KEY_INPUT_UP] == 1)
	{
		//SE
		PlaySoundMem(g_cScene->m_cSound->m_iSECursorMove, DX_PLAYTYPE_BACK);

		if (!m_bPlayLineState)
			m_bPlayLineState = true;
	}
	else if (g_cScene->m_iKey[KEY_INPUT_DOWN] == 1)
	{
		//SE
		PlaySoundMem(g_cScene->m_cSound->m_iSECursorMove, DX_PLAYTYPE_BACK);

		if (m_bPlayLineState)
			m_bPlayLineState = false;
	}

	//シーン遷移
	if (m_bPlayLineState) 
	{
		if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1)
		{
			//SE
			PlaySoundMem(g_cScene->m_cSound->m_iSEDecision, DX_PLAYTYPE_NORMAL);

			//ゲームシーン
			g_cScene->m_eSceneStatus = g_cScene->GAMEFADEOUTTRANSITION;
			g_cScene->m_cTransition = new CTransition;
		}
	}
	else 
	{
		if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1)
		{
			//ゲーム終了
			g_cScene->m_eSceneStatus = g_cScene->EXIT;
		}
	}
}

//===============================================================
// 動作処理
//===============================================================
void CTitle::Move() 
{
	//プレイヤー入力処理
	CheckUserInput();
}

//===============================================================
// 描画処理
//===============================================================
void CTitle::Draw() 
{
	//背景画像
	g_cScene->m_cGUI->BackGround();

	//アイコン
	DrawBox(100, 40, 540, 180, g_cScene->m_cColor->GetBlackColor(), FALSE);
	IconState();

	//テキスト
	DrawFormatStringToHandle(130, 80, g_cScene->m_cColor->GetBlackColor(), m_iTitleFontHandle, "TETRIS");
	DrawFormatStringToHandle(230, 250, g_cScene->m_cColor->GetBlackColor(), m_iMinTitleFontHandle, "P L A Y  G A M E");
	DrawFormatStringToHandle(230, 310, g_cScene->m_cColor->GetBlackColor(), m_iMinTitleFontHandle, "E X I T  G A M E");

	//ライン描画
	LineState();
}

//===============================================================
// ライン状態
//===============================================================
void CTitle::LineState() 
{
	if (m_bPlayLineState) 
	{
		//PLAY
		DrawLine(190, 280, 460, 280, g_cScene->m_cColor->GetBlackColor());
	}
	else 
	{
		//EXIT
		DrawLine(190, 340, 460, 340, g_cScene->m_cColor->GetBlackColor());
	}
}

//===============================================================
// アイコン描画
//===============================================================
void CTitle::DrawIcon(const int* p,int x,int y) 
{
	if (*p != 0) 
	{
		if (m_bPlayLineState)
		{
			//black
			DrawFormatString(x*BLOCK_INTERVAL + 170, y*BLOCK_INTERVAL + 225, g_cScene->m_cColor->GetBlackColor(), "■");
		}
		else
			//black
			DrawFormatString(x*BLOCK_INTERVAL + 170, y*BLOCK_INTERVAL + 285, g_cScene->m_cColor->GetBlackColor(), "■");
	}
}

//===============================================================
// アイコン状態
//===============================================================
void CTitle::IconState() 
{
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++) 
		{
			DrawIcon(&m_iIconBlock[y][x], x, y);
		}
	}
}