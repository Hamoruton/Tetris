#include "DxLib.h"
#include "Scene.h"

//===============================================================
// コンストラクタ
//===============================================================
CTransition::CTransition()
	:m_iFadeOutTimer(255), m_iFadeInTimer(0), m_iCountDownTimer(0), m_iCount(0)
{
}

//===============================================================
// デストラクタ
//===============================================================
CTransition::~CTransition() 
{
}

//===============================================================
// フェイドアウト
//===============================================================
bool CTransition::FadeOut() 
{
	SetDrawBright(m_iFadeOutTimer, m_iFadeOutTimer, m_iFadeOutTimer);
	DrawBox(0, 0, 640, 480, g_cScene->m_cColor->GetWhiteColor(), TRUE);
	m_iFadeOutTimer -= 2;
	if (m_iFadeOutTimer < 0) 
	{
		SetDrawBright(0, 0, 0);
		return false;
	}
	return true;
}

//===============================================================
// フェイドイン
//===============================================================
bool CTransition::FadeIn() 
{
	SetDrawBright(m_iFadeInTimer, m_iFadeInTimer, m_iFadeInTimer);
	DrawBox(0, 0, 640, 480, g_cScene->m_cColor->GetWhiteColor(), TRUE);
	m_iFadeInTimer += 2;
	if (m_iFadeInTimer > 255) 
	{
		SetDrawBright(255, 255, 255);
		return false;
	}
	return true;
}
//===============================================================
// ゲーム開始カウントダウン
//===============================================================
void CTransition::CountDown() 
{
	m_iCountDownTimer++;
	m_iCount = m_iCountDownTimer / 60;
	switch (m_iCount) 
	{
	case 0:		//3
		DrawFormatStringFToHandle(COUNT_DOWN_TEXT_X, COUNT_DOWN_TEXT_Y, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "3");
		break;

	case 1:		//2
		DrawFormatStringFToHandle(COUNT_DOWN_TEXT_X, COUNT_DOWN_TEXT_Y, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "2");
		break;

	case 2:		//1
		DrawFormatStringFToHandle(COUNT_DOWN_TEXT_X, COUNT_DOWN_TEXT_Y, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "1");
		break;

	case 3:		//START!
		DrawFormatStringFToHandle(COUNT_DOWN_TEXT_X - 50, COUNT_DOWN_TEXT_Y, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "START!");
		break;

	default:
		g_cScene->m_eSceneStatus = g_cScene->GAME;
		delete g_cScene->m_cTransition;
		break;
	}
}