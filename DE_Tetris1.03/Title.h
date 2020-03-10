#pragma once
#ifndef __TITLE_H_INCLUDED__
#define __TITLE_H_INCLUDED__

//===============================================================
// �^�C�g���N���X
//===============================================================
class CTitle
{
private:
	//�t�H���g
	int m_iTitleFontHandle;
	int m_iMinTitleFontHandle;

	//�v���C���C�����
	bool m_bPlayLineState = true;

	const int m_iIconBlock[4][4] =
	{
		0, 0, 0, 0,
		0, 9, 9, 0,
		0, 9, 9, 0,
		0, 0, 0, 0,
	};

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CTitle();
	~CTitle();

private:
	//���͏���
	void CheckUserInput();

public:
	//���쏈��
	void Move();

	//�`�揈��
	void Draw();
private:
	void LineState();
	void DrawIcon(const int* p, int x, int y);
	void IconState();
};

#endif



