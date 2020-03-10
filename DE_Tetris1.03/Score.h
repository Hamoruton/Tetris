#pragma once
#ifndef __SCORE_H_INCLUDED__
#define __SCORE_H_INCLUDED__

#include "Game.h"

//===============================================================
// �X�R�A�N���X
//===============================================================
class CScore
{
public:
	//�X�R�A
	int m_iLevel = 0;
	int m_iLines = 0;
	int m_iScore = 0;

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CScore();
	~CScore();

private:
	//�Z�b�^�[
	inline void SetLevel() { m_iLevel = g_cGame->m_iLevel; }
	inline void SetLines() { m_iLines = g_cGame->m_iFullLines; }
	inline void SetScore() { m_iScore = g_cGame->m_iScore; }

public:
	//�Q�b�^�[
	int GetLevel() { SetLevel(); return m_iLevel; }
	int GetLines() { SetLines(); return m_iLines; }
	int GetScore() { SetScore(); return m_iScore; }
};

#endif 



