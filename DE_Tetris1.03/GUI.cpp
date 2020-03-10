#include "DxLib.h"
#include "Scene.h"

//===============================================================
// コンストラクタ
//===============================================================
CGUI::CGUI()
{
	//背景画像読み込み
	m_iGHBackGround = LoadGraph(BACK_CHIP);

	//キーボタン画像読み込み
	m_iGHKeyArrow = LoadGraph(KEY_ARROW_CHIP);
	m_iGHKeyShift = LoadGraph(KEY_SHIFT_CHIP);
	m_iGHKeyCtrl = LoadGraph(KEY_CTRL_CHIP);
	m_iGHKeyP = LoadGraph(KEY_P_CHIP);

	//フォント読み込み
	m_iFontHandle = CreateFontToHandle(FONT_CHIP, 15, 3);
	m_iMinFontHandle = CreateFontToHandle(FONT_CHIP, 10, 3);
	m_iMaxFontHandle = CreateFontToHandle(FONT_CHIP, 25, 10);
	m_iPauseFontHandle = CreateFontToHandle(FONT_CHIP, 60, 3);
	m_iMinPauseFontHandle = CreateFontToHandle(FONT_CHIP, 20, 3);
}

//===============================================================
// デストラクタ
//===============================================================
CGUI::~CGUI() 
{
	//画像破棄
	DeleteGraph(m_iGHBackGround);
	DeleteGraph(m_iGHKeyArrow);
	DeleteGraph(m_iGHKeyShift);
	DeleteGraph(m_iGHKeyCtrl);
	DeleteGraph(m_iGHKeyP);

	//フォント破棄
	DeleteFontToHandle(m_iFontHandle);
	DeleteFontToHandle(m_iMinFontHandle);
	DeleteFontToHandle(m_iMaxFontHandle);
	DeleteFontToHandle(m_iPauseFontHandle);
	DeleteFontToHandle(m_iMinPauseFontHandle);
}

//===============================================================
// 描画
//===============================================================
void CGUI::Draw() 
{
	if (!g_cGame->m_bPause) 
	{
		//背景描画
		BackGround();

		//キーボタン画像
		KeyGraphic();

		//UIテキスト描画
		UIText();

		//スコア描画
		ScoreText();
	}
	else
	{
		//背景描画
		BackGround();
	}
}

//===============================================================
// 背景描画
//===============================================================
void CGUI::BackGround() 
{
	DrawRotaGraph(SCREEN_WIDTH / 2 + 15, SCREEN_HEIGHT / 2 + 35, 0.55, 0, m_iGHBackGround, TRUE);
}

//===============================================================
// キーボタン画像描画
//===============================================================
void CGUI::KeyGraphic() 
{
	DrawRotaGraph(KEY_CHIP_X, KEY_CHIP_Y, 0.1, PI, m_iGHKeyArrow, TRUE);
	DrawRotaGraph(KEY_CHIP_X, KEY_CHIP_Y + 20, 0.1, 0, m_iGHKeyArrow, TRUE);
	DrawRotaGraph(KEY_CHIP_X, KEY_CHIP_Y + 40, 0.1, -PI / 2, m_iGHKeyArrow, TRUE);
	DrawRotaGraph(KEY_CHIP_X, KEY_CHIP_Y + 60, 0.1, PI / 2, m_iGHKeyArrow, TRUE);
	DrawRotaGraph(KEY_CHIP_X - 18, KEY_CHIP_Y + 80, 0.15, 0, m_iGHKeyShift, TRUE);
	DrawRotaGraph(KEY_CHIP_X - 8, KEY_CHIP_Y + 105, 0.15, 0, m_iGHKeyCtrl, TRUE);
	DrawRotaGraph(KEY_CHIP_X, KEY_CHIP_Y + 125, 0.1, 0, m_iGHKeyP, FALSE);
}

//===============================================================
// UIテキスト描画
//===============================================================
void CGUI::UIText() 
{
	//ネクストテキスト
	DrawStringToHandle(NEXT_TEXT_X, NEXT_TEXT_Y, "NEXT", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);

	//ホールドテキスト
	DrawStringToHandle(HOLD_TEXT_X, HOLD_TEXT_Y, "HOLD", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);

	//スコアテキスト
	DrawStringToHandle(10, SCORE_TEXT_Y, "LEVEL", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);
	DrawStringToHandle(10, SCORE_TEXT_Y + 20, "LINES", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);
	DrawStringToHandle(10, SCORE_TEXT_Y + 40, "SCORE", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);

	//操作方法テキスト
	DrawStringToHandle(50, HELP_TEXT_Y - 30, "H E L P", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y, "RIGHT", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y + 20, "LEFT", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y + 40, "BUTTOM", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y + 60, "TURN", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y + 80, "DOWN", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y + 100, "HOLD", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);
	DrawStringToHandle(10, HELP_TEXT_Y + 120, "PAUSE", g_cScene->m_cColor->GetBlackColor(), m_iMinFontHandle);

	//プレイテトリステキスト
	DrawStringToHandle(245, SCREEN_HEIGHT - 45, "PLAY TETRIS !", g_cScene->m_cColor->GetBlackColor(), m_iFontHandle);

	//テトリステキスト
	TextFlash();
}

//===============================================================
// スコアテキスト描画
//===============================================================
void CGUI::ScoreText() 
{
	//レベル表示（0～9まで）
	if (g_cGame->m_iLevel > 9) 
	{
		g_cGame->m_iLevel = 9;
	}
	DrawFormatStringToHandle(120, SCORE_TEXT_Y, g_cScene->m_cColor->GetBlackColor(), m_iFontHandle, "%05d", g_cGame->m_iLevel);

	//ライン表示（0～99999まで）
	if (g_cGame->m_iFullLines > 99999)
	{
		g_cGame->m_iFullLines = 99999;
	}
	DrawFormatStringToHandle(120, SCORE_TEXT_Y + 20, g_cScene->m_cColor->GetBlackColor(), m_iFontHandle, "%05d", g_cGame->m_iFullLines);

	//スコア表示（0～99999まで）
	if (g_cGame->m_iScore > 99999)
	{
		g_cGame->m_iScore = 99999;
	}
	DrawFormatStringToHandle(120, SCORE_TEXT_Y + 40, g_cScene->m_cColor->GetBlackColor(), m_iFontHandle, "%05d", g_cGame->m_iScore);
}

//===============================================================
// テトリステキスト描画（5秒間点滅）
//===============================================================
void CGUI::TextFlash() 
{
	if (g_cGame->m_bTextFlash) 
	{
		//タイマー
		m_iBlendTimer++;
		if (m_iBlendTimer > 300) 
		{
			g_cGame->m_bTextFlash = false;
			m_iBlendTimer = 0;
		}

		//点滅
		if (!m_bBlendLimitMax)
		{
			m_iBlendCount += TEXT_FLASH_SPEED;
			if (m_iBlendCount > 255)
				m_bBlendLimitMax = true;
		}
		else
		{
			m_iBlendCount -= TEXT_FLASH_SPEED;
			if (m_iBlendCount < 0)
				m_bBlendLimitMax = false;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_iBlendCount);
		DrawStringToHandle(500, 150, "TETRIS", g_cScene->m_cColor->GetBlackColor(), m_iMaxFontHandle);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}