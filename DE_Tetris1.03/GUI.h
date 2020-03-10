#pragma once
#ifndef __GUI_H_INCLUDED__
#define __GUI_H_INCLUDED__

#define PI		3.1415926

//�摜
#define BACK_CHIP "Assets/Sprites/BG01.png"

#define KEY_ARROW_CHIP "Assets/Sprites/KeyArrow.png"
#define KEY_SHIFT_CHIP "Assets/Sprites/KeyShift.png"
#define KEY_CTRL_CHIP  "Assets/Sprites/KeyCtrl.png"
#define KEY_P_CHIP	   "Assets/Sprites/KeyP.png"

//�t�H���g
#define FONT_CHIP "GAU_font_PRIVAtE"

//���W
#define SCORE_TEXT_Y  10

#define NEXT_TEXT_X  430
#define NEXT_TEXT_Y   50

#define HOLD_TEXT_X	 130
#define HOLD_TEXT_Y	  85

#define HELP_TEXT_Y  200

#define KEY_CHIP_X  160
#define KEY_CHIP_Y  200

//�e�L�X�g�_�ŃX�s�[�h
#define TEXT_FLASH_SPEED  5

//===============================================================
// GUI�N���X
//===============================================================
class CGUI
{
private:
	//�w�i�摜�n���h��
	int m_iGHBackGround;

	//�L�[�{�^���摜�n���h��
	int m_iGHKeyArrow;
	int m_iGHKeyShift;
	int m_iGHKeyCtrl;
	int m_iGHKeyP;

public:
	//�t�H���g�n���h��
	int m_iFontHandle;
	int m_iMinFontHandle;
	int m_iMaxFontHandle;
	int m_iPauseFontHandle;
	int m_iMinPauseFontHandle;

private:
	//�e�L�X�g�_��
	int m_iBlendCount = 0;
	//����:255�ȏォ�ǂ���
	bool m_bBlendLimitMax = false;
	//�^�C�}�[
	int m_iBlendTimer = 0;

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CGUI();
	~CGUI();

	//�`�揈��
	void Draw();
	void BackGround();		//�w�i�摜
	void KeyGraphic();		//�L�[�{�^���摜
	void UIText();			//�e�L�X�g
	void ScoreText();		//�X�R�A�e�L�X�g
	void TextFlash();		//�_�Ńe�L�X�g�i4�񓯎��N���A�Ńe�g���X�e�L�X�g�\���j
};

#endif



