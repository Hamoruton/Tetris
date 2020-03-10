#include "DxLib.h"
#include "Scene.h"

//===============================================================
// �R���X�g���N�^
//===============================================================
CResult::CResult()
{
	//�t�H���g�ǂݍ���
	m_iResultFontHandle = CreateFontToHandle(FONT_CHIP, 40, 3);

	//BGM�Đ�
	PlaySoundMem(g_cScene->m_cSound->m_iBGMResult, DX_PLAYTYPE_LOOP);
}

//===============================================================
// �f�X�g���N�^
//===============================================================
CResult::~CResult() 
{
	//�t�H���g�j��
	DeleteFontToHandle(m_iResultFontHandle);

	//BGM��~
	StopSoundMem(g_cScene->m_cSound->m_iBGMResult);

	//BGM�Đ�
	PlaySoundMem(g_cScene->m_cSound->m_iBGMTitle, DX_PLAYTYPE_LOOP, TRUE);
}

//===============================================================
// �v���C���[���͏���
//===============================================================
void CResult::CheckUserInput() 
{
	if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1)
	{
		//�^�C�g�����
		g_cScene->m_eSceneStatus = g_cScene->TITLETRANSITION;
	}
}

//===============================================================
// ���쏈��
//===============================================================
void CResult::Move() 
{
	//�v���C���[���͏���
	CheckUserInput();
}

//===============================================================
// �`��
//===============================================================
void CResult::Draw() 
{
	//�w�i�`��
	g_cScene->m_cGUI->BackGround();

	//���U���gUI�`��
	ResultUI();
}

//===============================================================
// ���U���gUI�`��
//===============================================================
void CResult::ResultUI() 
{
	//�A�C�R��
	DrawBox(140, 120, 500, 360, g_cScene->m_cColor->GetBlackColor(), FALSE);

	//�X�R�A
	DrawFormatStringToHandle(150, 160, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "LEVEL");
	DrawFormatStringToHandle(360, 160, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "%05d", g_cScene->m_cScore->m_iLevel);
	DrawFormatStringToHandle(150, 230, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "LINES");
	DrawFormatStringToHandle(360, 230, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "%05d", g_cScene->m_cScore->m_iLines);
	DrawFormatStringToHandle(150, 300, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "SCORE");
	DrawFormatStringToHandle(360, 300, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMaxFontHandle, "%05d", g_cScene->m_cScore->m_iScore);

	//�e�L�X�g
	DrawStringToHandle(120, 60, "RESULT", g_cScene->m_cColor->GetBlackColor(), m_iResultFontHandle);
	TextFlash();
}

//===============================================================
// �e�L�X�g�_�ŁiPush Key Enter�j
//===============================================================
void CResult::TextFlash() 
{
	//�_��
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