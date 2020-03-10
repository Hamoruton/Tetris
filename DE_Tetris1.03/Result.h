#pragma once
#ifndef __RESULT_H_INCLUDED__
#define __RESULT_H_INCLUDED__

//===============================================================
// ���U���g�N���X
//===============================================================
class CResult
{
private:
	//�t�H���g�n���h��
	int m_iResultFontHandle;

	//�e�L�X�g�_��
	int m_iBlendCount = 0;
	//����:255�ȏォ�ǂ���
	bool m_bBlendLimitMax = false;
	//�^�C�}�[
	int m_iBlendTimer = 0;

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CResult();
	~CResult();

private:
	//���͏���
	void CheckUserInput();

public:
	//���쏈��
	void Move();

	//�`�揈��
	void Draw();
private:
	void ResultUI();
	void TextFlash();
};

#endif



