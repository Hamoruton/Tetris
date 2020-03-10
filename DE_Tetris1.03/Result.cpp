#include "DxLib.h"
#include "Scene.h"

//===============================================================
// コンストラクタ
//===============================================================
CResult::CResult()
{
	//フォント読み込み
	m_iResultFontHandle = CreateFontToHandle(FONT_CHIP, 40, 3);

	//BGM再生
	PlaySoundMem(g_cScene->m_cSound->m_iBGMResult, DX_PLAYTYPE_LOOP);
}

//===============================================================
// デストラクタ
//===============================================================
CResult::~CResult() 
{
	//フォント破棄
	DeleteFontToHandle(m_iResultFontHandle);

	//BGM停止
	StopSoundMem(g_cScene->m_cSound->m_iBGMResult);

	//BGM再生
	PlaySoundMem(g_cScene->m_cSound->m_iBGMTitle, DX_PLAYTYPE_LOOP, TRUE);
}

//===============================================================
// プレイヤー入力処理
//===============================================================
void CResult::CheckUserInput() 
{
	if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1)
	{
		//タイトル画面
		g_cScene->m_eSceneStatus = g_cScene->TITLETRANSITION;
	}
}

//===============================================================
// 動作処理
//===============================================================
void CResult::Move() 
{
	//プレイヤー入力処理
	CheckUserInput();
}

//===============================================================
// 描画
//===============================================================
void CResult::Draw() 
{
	//背景描画
	g_cScene->m_cGUI->BackGround();

	//リザルトUI描画
	ResultUI();
}

//===============================================================
// リザルトUI描画
//===============================================================
void CResult::ResultUI() 
{
	//アイコン
	DrawBox(140, 120, 500, 360, g_cScene->m_cColor->GetBlackColor(), FALSE);

	//スコア
	DrawFormatStringToHandle(150, 160, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "LEVEL");
	DrawFormatStringToHandle(360, 160, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "%05d", g_cScene->m_cScore->m_iLevel);
	DrawFormatStringToHandle(150, 230, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "LINES");
	DrawFormatStringToHandle(360, 230, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "%05d", g_cScene->m_cScore->m_iLines);
	DrawFormatStringToHandle(150, 300, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "SCORE");
	DrawFormatStringToHandle(360, 300, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "%05d", g_cScene->m_cScore->m_iScore);

	//テキスト
	DrawStringToHandle(120, 60, "RESULT", g_cScene->m_cColor->GetBlackColor(), m_iResultFontHandle);
	TextFlash();
}

//===============================================================
// テキスト点滅（Push Key Enter）
//===============================================================
void CResult::TextFlash() 
{
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
	DrawStringToHandle(240, 400, "Push Key Enter", g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iFontHandle);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}