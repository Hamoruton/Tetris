#include "Scene.h"

//�Q�[���N���X�ϐ�
CScene* g_cScene;
CFPS g_cFps(10, 0, 60);

//===============================================================
// �R���X�g���N�^
//===============================================================
CScene::CScene() 
{
	//�N���X�̓ǂݍ���
	m_cTitle = new CTitle;
	m_cColor = new CColor;
	m_cGUI = new CGUI;
	m_cSound = new CSound;

	//BGM�Đ�
	PlaySoundMem(m_cSound->m_iBGMTitle, DX_PLAYTYPE_LOOP);
}

//===============================================================
// �f�X�g���N�^
//===============================================================
CScene::~CScene() 
{
	//�N���X�̔j��
	delete m_cColor;
	delete m_cGUI;
	delete m_cSound;

	//DxLib�̔j��
	DxLib_End();
}

//===============================================================
// �X�V
//===============================================================
void CScene::Update() 
{
	while (!ProcessMessage())
	{
		ClearDrawScreen();

		if (!InputKey())
			break;

		if (m_eSceneStatus == EXIT)
			break;

		//�Q�[�����
		switch (m_eSceneStatus)
		{
		//�^�C�g��
		case TITLE:		
			m_cTitle->Move();
			m_cTitle->Draw();
			break;

		//�t�F�C�h�A�E�g
		case GAMEFADEOUTTRANSITION:
			if (!m_cTransition->FadeOut())
			{
				delete m_cTitle;
				g_cGame = new CGame;
				m_eSceneStatus = GAMEFADEINTRANSITION;
			}
			else
				m_cTitle->Draw();
			break;

		//�t�F�C�h�C��
		case GAMEFADEINTRANSITION:						
			if (!m_cTransition->FadeIn())
			{
				m_cGUI->Draw();
				g_cGame->Draw();
				m_eSceneStatus = GAMEREADY;
			}
			else 
			{
				m_cGUI->Draw();
				g_cGame->Draw();
			}
			break;

		//�Q�[������
		case GAMEREADY:	
			m_cTransition->CountDown();
			m_cGUI->Draw();
			g_cGame->Draw();
			break;

		//�Q�[��
		case GAME:										
			g_cGame->Move();
			m_cGUI->Draw();
			g_cGame->Draw();
			break;

		case RESULTTRANSITION:							
			m_cScore = new CScore;
			delete g_cGame;
			m_cResult = new CResult;
			m_cResult->Draw();
			m_eSceneStatus = RESULT;
			break;

		//���U���g
		case RESULT:
			m_cResult->Move();
			m_cResult->Draw();
			break;

		case TITLETRANSITION:
			delete m_cResult;
			delete m_cScore;
			m_cTitle = new CTitle;
			m_cTitle->Draw();
			m_eSceneStatus = TITLE;
			break;
		}
		//FPS
		g_cFps.Update();  
		//g_cFps.Draw();
		ScreenFlip();
		g_cFps.Wait();
	}
}

//===============================================================
// ���͏���
//===============================================================
bool CScene::InputKey() 
{
	char cTempKey[256];
	GetHitKeyStateAll(cTempKey);
	for (int i = 0; i < 256; i++)
	{
		if (cTempKey[i] != 0)
		{
			m_iKey[i]++;
		}
		else
		{
			m_iKey[i] = 0;
		}
	}
	if (m_iKey[KEY_INPUT_ESCAPE])
		return false;

	return true;
}