#pragma once
#ifndef __TRANSITION_H_INCLUDED__
#define __TRANSITION_H_INCLUDED__

#define COUNT_DOWN_TEXT_X  300
#define COUNT_DOWN_TEXT_Y  200

//===============================================================
// �g�����W�V�����N���X
//===============================================================
class CTransition
{
private:
	//�t�F�C�h�A�E�g.�t�F�C�h�C���^�C�}�[
	int m_iFadeOutTimer;
	int m_iFadeInTimer;

	//�J�E���g�_�E���^�C�}�[
	int m_iCountDownTimer;
	int m_iCount;

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CTransition();
	~CTransition();

	//�`��
	bool FadeOut();		//�t�F�C�h�A�E�g
	bool FadeIn();		//�t�F�C�h�C��

	void CountDown();	//�Q�[���J�n�J�E���g�_�E��
};

#endif


