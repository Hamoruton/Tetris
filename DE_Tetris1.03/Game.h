#pragma once
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_COLOR   32

#define BLOCK_WIDTH		4
#define BLOCK_HEIGHT	4

#define BLOCK_NEXT_NUM  5
#define BLOCK_NEXT_X  430
#define BLOCK_NEXT_Y   70

#define BLOCK_HOLD_X  130
#define BLOCK_HOLD_Y  100

#define STAGE_WIDTH		12
#define STAGE_HEIGHT	23
#define STAGE_CENTER_X	SCREEN_WIDTH/3
#define STAGE_CENTER_Y	30

#define BLOCK_INTERVAL		17
#define BLOCK_NEXT_INTERVAL 60

//===============================================================
// �Q�[���N���X
//===============================================================
class CGame
{
private:
	//�X�e�[�W�z��i�u���b�N�̏��������Ă����ŏI�I�ȕ`��̏��������j
	int m_iStage[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };

	//�u���b�N�z��
	int m_iBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };

	//��]��̃u���b�N�z��i��]��̃u���b�N�����ꎞ�I�ɕۊǂ������蔻��̗L�����݂邽�߂̕ϐ��j
	int m_iRotateBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };

	//�l�N�X�g�u���b�N�z��
	int m_iNextBlockID[BLOCK_NEXT_NUM] = { 0 };

	//�u���b�N���W
	int m_iBlockX = 5;
	int m_iBlockY = 0;
	int m_iGhostBlockY = 0;

	//1��u���b�N�N���A����Y���W
	int m_iClearLineY = 0;
public:
	//1��u���b�N���N���A�������v��
	int m_iFullLines = 0;

private:
	//�u���b�NID�i7��m_iTetrimino�z�����؂邽�߂̕ϐ��j
	int m_iBlockID = 0;
	//�^�[���ϐ� (4�p�^�[����m_iTetrimino�z�����؂邽�߂̕ϐ�)
	int m_iTurn = 0;

	//�u���b�N�̎��R�����𒲐�����ϐ�
	int m_iDropCount = 0;
	int m_iLimitCount = 60;

public:
	//���x���i10��u���b�N���N���A���邲�ƂɃ��x���A�b�v�j
	int m_iLevel = 0;
private:
	//����:0�ȊO��10�̔{��
	bool m_bLevelUpStart = false;
	//����:10�̔{���ɂȂ�����1�x����
	bool m_bLevelUp = false;

public:
	//�|�[�Y
	bool m_bPause = false;
private:
	bool m_bReturnGame = true;
	const int m_iPauseIconBlock[4][4] =
	{
		0, 0, 0, 0,
		0, 9, 9, 0,
		0, 9, 9, 0,
		0, 0, 0, 0,
	};

public:
	//�X�R�A
	int m_iScore = 0;

	//����:�e�g���X�i4�񓯎������j�Ńe�L�X�g�\��
	bool m_bTextFlash = false;
private:
	int m_iLineCount = 0;
	
	//�z�[���h
	int m_iHoldBlockID = 0;
	int m_iHoldCount = 0;
	bool m_bFirstHold = false;

	//�e�g���~�m�z��
	const int m_iTetrimino[BLOCK_HEIGHT * 7][BLOCK_WIDTH * 4] =
	{
		//O
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
		{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

		//I
		{0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0},
		{0,0,0,0,0,0,2,0,2,2,2,2,0,2,0,0},
		{2,2,2,2,0,0,2,0,0,0,0,0,0,2,0,0},
		{0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0},

		//S
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,3,3,0,0,3,0,0,0,0,0,0,3,0,0,0},
		{3,3,0,0,0,3,3,0,0,3,3,0,3,3,0,0},
		{0,0,0,0,0,0,3,0,3,3,0,0,0,3,0,0},

		//Z
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{4,4,0,0,0,0,4,0,0,0,0,0,0,4,0,0},
		{0,4,4,0,0,4,4,0,4,4,0,0,4,4,0,0},
		{0,0,0,0,0,4,0,0,0,4,4,0,4,0,0,0},

		//L
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,5,0,0,5,0,0,0,0,0,0,5,5,0,0},
		{5,5,5,0,0,5,0,0,5,5,5,0,0,5,0,0},
		{0,0,0,0,0,5,5,0,5,0,0,0,0,5,0,0},

		//J
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{6,0,0,0,0,6,6,0,0,0,0,0,0,6,0,0},
		{6,6,6,0,0,6,0,0,6,6,6,0,0,6,0,0},
		{0,0,0,0,0,6,0,0,0,0,6,0,6,6,0,0},

		//T
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,7,0,0,0,7,0,0,0,0,0,0,0,7,0,0},
		{7,7,7,0,0,7,7,0,7,7,7,0,7,7,0,0},
		{0,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0},
	};

public:
	//�R���X�g���N�^.�f�X�g���N�^
	CGame();
	~CGame();

private:
	//������
	void InitWall();
	void InitBlock();

	//���͏���
	void CheckUserInput();		    //�v���C���[���͏���
	bool Pause();					//�|�[�Y

public:
	//���쏈��
	void Move();
private:
	void FreeDrop();				//�u���b�N���R����
	void Generate();				//�u���b�N����
	void ExchangeNextBlocks();		//�l�N�X�g�u���b�N
	void HoldBlock();				//�z�[���h�u���b�N
	bool IsValid();					//�u���b�N�L���͈�
	bool IsGhostValid();			//�S�[�X�g�u���b�N�L���͈�
	void Rotate();					//�u���b�N��]
	bool IsClear();					//�u���b�N�N���A
	void AffterClear();				//�u���b�N�N���A��̗���
	void LevelUp();					//���x���A�b�v
	void AddScore();				//�X�R�A�̉��Z
	bool IsGameOver();				//�Q�[���I�[�o�[

public:
	//�`�揈��
	void Draw();
private:
	void DrawBlock(int array, int x, int y);					//�u���b�N�`��
	void DrawGhostBlock(int array, int x, int y);				//�S�[�X�g�u���b�N�`��
	void DrawStage(int array, int x, int y);					//�X�e�[�W�`��
	void DrawNextBlocks(const int array, int x, int y, int h);	//�l�N�X�g�u���b�N�`��
	void DrawHoldBlock(const int array, int x, int y);			//�z�[���h�u���b�N�`��
	void DrawPause();											//�|�[�Y�`��
	void DrawPauseIcon(const int array, int x, int y);			//�|�[�Y�A�C�R���`��
};
extern CGame* g_cGame;

#endif

