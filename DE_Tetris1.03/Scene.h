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
// �V�[���N���X
//===============================================================
class CScene
{
public:
	//�Q�[���̏�ԕϐ�
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
	//�^�C�g���N���X
	CTitle* m_cTitle;
	//���U���g�N���X
	CResult* m_cResult;
	//�J���[�N���X
	CColor* m_cColor;
	//GUI�N���X
	CGUI* m_cGUI;
	//�X�R�A�N���X
	CScore* m_cScore;
	//�g�����W�V�����N���X
	CTransition* m_cTransition;
	//�T�E���h�N���X
	CSound* m_cSound;

	//�L�[���z��
	int m_iKey[256] = { 0 };

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CScene();
	~CScene();

	//�X�V
	void Update();

	//���͏���
	bool InputKey();
};
extern CScene* g_cScene;

#endif



