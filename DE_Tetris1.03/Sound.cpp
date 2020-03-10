#include "DxLib.h"
#include "Scene.h"

//===============================================================
// �R���X�g���N�^
//===============================================================
CSound::CSound() 
{
	//BGM
	m_iBGMTitle = LoadSoundMem(BGM_TITLE);
	m_iBGMGame = LoadSoundMem(BGM_GAME);
	m_iBGMResult = LoadSoundMem(BGM_RESULT);

	//SE
	m_iSEBlockMove = LoadSoundMem(SE_BLOCK_MOVE);
	m_iSEBlockDown = LoadSoundMem(SE_BLOCK_DOWN);
	m_iSEBlockClear = LoadSoundMem(SE_BLOCK_CLEAR);
	m_iSELevelUp = LoadSoundMem(SE_LEVEL_UP);
	m_iSECountDown = LoadSoundMem(SE_COUNT_DOWN);

	m_iSEDecision = LoadSoundMem(SE_DECISION);
	m_iSECursorMove = LoadSoundMem(SE_CURSOR_MOVE);
}

//===============================================================
// �f�X�g���N�^
//===============================================================
CSound::~CSound() 
{
	//���f�[�^�j��
	InitSoundMem();
}