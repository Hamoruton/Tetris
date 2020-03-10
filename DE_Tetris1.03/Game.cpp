#include <time.h>
#include "DxLib.h"
#include "Scene.h"

//�Q�[���N���X�ϐ�
CGame* g_cGame;

//===============================================================
// �R���X�g���N�^
//===============================================================
CGame::CGame()
{
	//�E�H�[��������
	InitWall();
	//�u���b�N������
	InitBlock();

	//BGM�Đ�
	PlaySoundMem(g_cScene->m_cSound->m_iBGMGame, DX_PLAYTYPE_LOOP);
}

//===============================================================
// �f�X�g���N�^
//===============================================================
CGame::~CGame() 
{
	//BGM��~
	StopSoundMem(g_cScene->m_cSound->m_iBGMGame);
}

//===============================================================
// �E�H�[��������
//===============================================================
void CGame::InitWall() 
{
	for (int y = 1; y < STAGE_HEIGHT; y++) 
	{
		for (int x = 0; x < STAGE_WIDTH; x++) 
		{
			//���̕�
			m_iStage[y][0] = 9;

			//���̕�
			m_iStage[STAGE_HEIGHT-1][x] = 9;

			//�E�̕�
			m_iStage[y][STAGE_WIDTH - 1] = 9;
		}
	}
}

//===============================================================
// �u���b�N������
//===============================================================
void CGame::InitBlock() 
{
	//�u���b�N�̎��
	srand(time(NULL));
	m_iBlockID = rand() % 7;

	for (int y = 0; y < BLOCK_HEIGHT; y++) 
	{
		for (int x = 0; x < BLOCK_WIDTH; x++) 
		{
			m_iBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][x];
		}
	}

	//�l�N�X�g�u���b�N�̎��
	for (int i = 0; i < sizeof(m_iNextBlockID) / sizeof(int); i++) 
	{
		m_iNextBlockID[i] = rand() % 7;
	}
}

//===============================================================
// �v���C���[���͏���
//===============================================================
void CGame::CheckUserInput() 
{
	//��]
	if (g_cScene->m_iKey[KEY_INPUT_UP] == 1)
	{
		Rotate();
	}

	//��ԉ��܂ŗ���
	if (g_cScene->m_iKey[KEY_INPUT_RSHIFT] == 1)
	{
		while (IsValid()) 
		{
			m_iBlockY++;
		}
		m_iBlockY--;
	}

	//�z�[���h
	if (g_cScene->m_iKey[KEY_INPUT_RCONTROL] == 1)
	{
		HoldBlock();
	}

	//���E���ړ�
	if (g_cScene->m_iKey[KEY_INPUT_LEFT] == 1)
	{
		m_iBlockX--;
		if (!IsValid()) 
		{
			m_iBlockX++;
		}
	}
	else if (g_cScene->m_iKey[KEY_INPUT_LEFT] > 10)
	{
		m_iBlockX--;
		if (!IsValid())
		{
			m_iBlockX++;
		}
	}
	else if (g_cScene->m_iKey[KEY_INPUT_RIGHT] == 1)
	{
		m_iBlockX++;
		if (!IsValid())
		{
			m_iBlockX--;
		}
	}
	else if (g_cScene->m_iKey[KEY_INPUT_RIGHT] > 10)
	{
		m_iBlockX++;
		if (!IsValid())
		{
			m_iBlockX--;
		}
	}
	else if (g_cScene->m_iKey[KEY_INPUT_DOWN] == 1)
	{
		m_iBlockY++;
		if (!IsValid())
		{
			m_iBlockY--;
			Generate();
		}
	}
	else if (g_cScene->m_iKey[KEY_INPUT_DOWN] > 10)
	{
		m_iBlockY++;
		if (!IsValid())
		{
			m_iBlockY--;
		}
	}
}

//===============================================================
// �|�[�Y
//===============================================================
bool CGame::Pause() 
{
	//�|�[�Y
	if (g_cScene->m_iKey[KEY_INPUT_P] == 1)
	{
		//���]
		m_bPause = !m_bPause;
	}

	if (m_bPause) 
	{
		if (m_bReturnGame) 
		{
			if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1)
			{
				//�Q�[�����
				m_bPause = !m_bPause;
			}
			else if (g_cScene->m_iKey[KEY_INPUT_DOWN] == 1)
			{
				//SE
				PlaySoundMem(g_cScene->m_cSound->m_iSECursorMove, DX_PLAYTYPE_BACK);

				m_bReturnGame = false;
			}
		}
		else
		{
			if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1) 
			{
				//�^�C�g�����
				g_cScene->m_cTitle = new CTitle;
				g_cScene->m_eSceneStatus = g_cScene->TITLE;

				//BGM
				StopSoundMem(g_cScene->m_cSound->m_iBGMGame);
				PlaySoundMem(g_cScene->m_cSound->m_iBGMTitle, DX_PLAYTYPE_LOOP);
			}
			else if (g_cScene->m_iKey[KEY_INPUT_UP] == 1) 
			{
				//SE
				PlaySoundMem(g_cScene->m_cSound->m_iSECursorMove, DX_PLAYTYPE_BACK);

				m_bReturnGame = true;
			}
		}
		return true;
	}
	
	return false;
}

//===============================================================
// ���쏈��
//===============================================================
void CGame::Move() 
{
	//�|�[�Y
	if (Pause())
		return;

	//�v���C���[���͏���
	CheckUserInput();

	//�u���b�N���R����
	FreeDrop();
}

//===============================================================
// �u���b�N���R����
//===============================================================
void CGame::FreeDrop() 
{
	//��������
	m_iDropCount++;
	if (m_iDropCount > m_iLimitCount)
	{
		m_iBlockY++;
		if (!IsValid())
		{
			m_iBlockY--;
			Generate();
		}
		m_iDropCount = 0;
	}
}

//===============================================================
// �u���b�N����
//===============================================================
void CGame::Generate()
{
	//�Q�[���I�[�o�[
	if (IsGameOver())
	{
		g_cScene->m_eSceneStatus = g_cScene->RESULTTRANSITION;
		return;
	}

	//�u���b�N�̍��W���X�e�[�W�ɕۑ�
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			m_iStage[m_iBlockY + y][m_iBlockX + x] += m_iBlock[y][x];
		}
	}

	//�u���b�N�N���A
	while(IsClear()) 
	{
		AffterClear();
		m_iLineCount++;
	}
	AddScore();

	//�u���b�N����ւ�
	ExchangeNextBlocks();

	//�u���b�N���W������
	m_iBlockX = 5;
	m_iBlockY = 0;
	m_iDropCount = 0;
	m_iHoldCount = 0;
}

//===============================================================
// �l�N�X�g�u���b�N
//===============================================================
void CGame::ExchangeNextBlocks() 
{
	//�u���b�N����ւ�
	m_iBlockID = m_iNextBlockID[0];

	for (int i = 0; i < BLOCK_NEXT_NUM - 1; i++) 
	{
		m_iNextBlockID[i] = m_iNextBlockID[i + 1];
	}

	srand(time(NULL));
	m_iNextBlockID[BLOCK_NEXT_NUM - 1] = rand() % 7;

	//�l�N�X�g�u���b�N��o�^
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			m_iBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][x];
		}
	}
}

//===============================================================
// �z�[���h�u���b�N
//===============================================================
void CGame::HoldBlock() 
{
	int tempID = 0;

	if (m_bFirstHold) 
	{
		//�z�[���h����
		m_iHoldCount++;
		if (m_iHoldCount > 1)
		{
			return;
		}

		//ID����ւ�
		tempID = m_iBlockID;
		m_iBlockID = m_iHoldBlockID;
		m_iHoldBlockID = tempID;

		//�z�[���h�u���b�N�o�^
		for (int y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < BLOCK_WIDTH; x++)
			{
				m_iBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][x];
			}
		}

		//�u���b�N���W������
		m_iBlockX = 5;
		m_iBlockY = 0;
		m_iDropCount = 0;

	}
	else 
	{
		//ID�ۑ�
		m_iHoldBlockID = m_iBlockID;

		//�u���b�N����ւ�
		ExchangeNextBlocks();

		//�u���b�N���W������
		m_iBlockX = 5;
		m_iBlockY = 0;
		m_iDropCount = 0;

		//�z�[���h����
		m_bFirstHold = true;
	}
}

//===============================================================
// �u���b�N�L���͈�
//===============================================================
bool CGame::IsValid()
{
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			if (m_iBlock[y][x] != 0)
			{
				if (m_iStage[m_iBlockY + y][m_iBlockX + x] != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

//===============================================================
// �S�[�X�g�u���b�N�L���͈�
//===============================================================
bool CGame::IsGhostValid()
{
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			if (m_iBlock[y][x] != 0)
			{
				if (m_iStage[m_iGhostBlockY + y][m_iBlockX + x] != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

//===============================================================
// �u���b�N��]
//===============================================================
void CGame::Rotate()
{
	bool isTurn = true;
	m_iTurn++;

	//��]��u���b�N
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			m_iRotateBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][(m_iTurn % 4)*BLOCK_WIDTH + x];
		}
	}

	//�����蔻��
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			if (m_iRotateBlock[y][x] != 0)
			{
				if (m_iStage[m_iBlockY + y][m_iBlockX + x] != 0)
				{
					m_iTurn--;
					isTurn = false;
				}
			}
		}
	}

	//��]��u���b�N���
	if (isTurn)
	{
		for (int y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < BLOCK_WIDTH; x++)
			{
				m_iBlock[y][x] = m_iRotateBlock[y][x];
			}
		}
	}
}

//===============================================================
// �u���b�N�N���A
//===============================================================
bool CGame::IsClear() 
{
	//�u���b�N�̐�����1��10�ŃN���A
	int count = 0;

	for (int y = 1; y < STAGE_HEIGHT - 1; y++)
	{
		for (int x = 1; x < STAGE_WIDTH - 1; x++)
		{
			if (m_iStage[y][x] != 0) 
			{
				count++;
				if (count == 10) 
				{
					m_iFullLines++;
					LevelUp();
					m_iClearLineY = y;
					count = 0;
					return true;
				}
			}
		}
		count = 0;
	}
	return false;
}

//===============================================================
// �u���b�N�N���A��̗���
//===============================================================
void CGame::AffterClear() 
{
	PlaySoundMem(g_cScene->m_cSound->m_iSEBlockClear, DX_PLAYTYPE_BACK);

	//�u���b�N�N���A
	for (int x = 1; x < STAGE_WIDTH - 1; x++)
	{
		m_iStage[m_iClearLineY][x] = 0;
	}

	//�u���b�N����
	for (int y = m_iClearLineY; y > 0; y--)
	{
		for (int x = 1; x < STAGE_WIDTH - 1; x++)
		{
			m_iStage[y][x] = m_iStage[y - 1][x];
		}
	}
	m_iClearLineY = 0;
}

//===============================================================
// ���x���A�b�v
//===============================================================
void CGame::LevelUp() 
{
	//0�ȊO��10�̔{������
	if (m_iFullLines != 0)
	{
		m_bLevelUpStart = true;
	}

	//���x���A�b�v����
	if (m_bLevelUpStart)
	{
		if (m_iFullLines % 10 == 0)
		{
			if (!m_bLevelUp) 
			{
				m_iLevel++;
				m_iLimitCount -= 6;
				if (m_iLevel >= 9) 
				{
					m_iLimitCount = 10;
				}
				else
				{
					PlaySoundMem(g_cScene->m_cSound->m_iSELevelUp, DX_PLAYTYPE_BACK);
				}
				m_bLevelUp = true;
			}
		}
		else
			m_bLevelUp = false;
	}
}

//===============================================================
// �X�R�A�̉��Z�i����:���C�����i���x����*���_�j�j
//===============================================================
void CGame::AddScore() 
{
	switch (m_iLineCount) 
	{
	case 1:		//1��
		m_iScore += ((m_iLevel + 1) * 10);
		break;

	case 2:		//2��
		m_iScore += ((m_iLevel + 1) * 20);
		break;

	case 3:		//3��
		m_iScore += ((m_iLevel + 1) * 30);
		break;

	case 4:		//Tetris
		m_iScore += ((m_iLevel + 1) * 100);
		m_bTextFlash = true;
		break;
	}
	m_iLineCount = 0;
}

//===============================================================
// �Q�[���I�[�o�[
//===============================================================
bool CGame::IsGameOver()
{
	//�X�e�[�W�O�Ńu���b�N�ƏՓ˂������ǂ���
	for (int x = 0; x < STAGE_WIDTH; x++)
	{
		if (m_iBlockY <= 0)
		{
			return true;
		}
	}
	return false;
}

//===============================================================
// �`�揈��
//===============================================================
void CGame::Draw() 
{
	if (!m_bPause) {
		//�u���b�N�`��
		for (int y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < BLOCK_WIDTH; x++)
			{
				if (m_iBlock[y][x] != 0)
				{
					DrawBlock(m_iBlock[y][x], x, y);
				}
			}
		}

		//�S�[�X�g�u���b�N�`��
		for (int y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < BLOCK_WIDTH; x++)
			{
				if (m_iBlock[y][x] != 0)
				{
					DrawGhostBlock(m_iBlock[y][x], x, y);
				}
			}
		}

		//�X�e�[�W�`��
		for (int y = 0; y < STAGE_HEIGHT; y++)
		{
			for (int x = 0; x < STAGE_WIDTH; x++)
			{
				if (m_iStage[y][x] != 0)
				{
					DrawStage(m_iStage[y][x], x, y);
				}
			}
		}

		//�l�N�X�g�u���b�N�`��
		for (int h = 0; h < BLOCK_NEXT_NUM; h++)
		{
			for (int y = 0; y < BLOCK_HEIGHT; y++)
			{
				for (int x = 0; x < BLOCK_WIDTH; x++)
				{
					if (m_iTetrimino[(m_iNextBlockID[h] * BLOCK_HEIGHT) + y][x] != 0)
					{
						DrawNextBlocks(m_iTetrimino[(m_iNextBlockID[h] * BLOCK_HEIGHT) + y][x], x, y, h);
					}
				}
			}
		}

		//�z�[���h�u���b�N�`��
		if (m_bFirstHold)
		{
			for (int y = 0; y < BLOCK_HEIGHT; y++)
			{
				for (int x = 0; x < BLOCK_WIDTH; x++)
				{
					if (m_iTetrimino[(m_iHoldBlockID * BLOCK_HEIGHT) + y][x] != 0)
					{
						DrawHoldBlock(m_iTetrimino[(m_iHoldBlockID * BLOCK_HEIGHT) + y][x], x, y);
					}
				}
			}
		}
	}
	else 
	{
		DrawPause();
	}
}

//===============================================================
// �u���b�N�`��
//===============================================================
void CGame::DrawBlock(int array, int x, int y)
{
	switch (array) 
	{
	case 1:		//yellow
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetYellowColor(), "��");
		break;

	case 2:		//red
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetRedColor(), "��");
		break;

	case 3:		//pink
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetPinkColor(), "��");
		break;

	case 4:		//green
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetGreenColor(), "��");
		break;

	case 5:		//orange
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetOrangeColor(), "��");
		break;

	case 6:		//blue
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlueColor(), "��");
		break;

	case 7:		//cyan
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetCyanColor(), "��");
		break;
	}
}

//===============================================================
// �S�[�X�g�u���b�N�`��
//===============================================================
void CGame::DrawGhostBlock(int array, int x, int y)
{
	//Y���W
	m_iGhostBlockY = m_iBlockY;
	while (IsGhostValid()) 
	{
		m_iGhostBlockY++;
	}
	m_iGhostBlockY--;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	switch (array)
	{
	case 1:		//yellow
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetYellowColor(), "��");
		break;

	case 2:		//red
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetRedColor(), "��");
		break;

	case 3:		//pink
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetPinkColor(), "��");
		break;

	case 4:		//green
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetGreenColor(), "��");
		break;

	case 5:		//orange
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetOrangeColor(), "��");
		break;

	case 6:		//blue
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlueColor(), "��");
		break;

	case 7:		//cyan
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetCyanColor(), "��");
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//===============================================================
// �X�e�[�W�`��
//===============================================================
void CGame::DrawStage(int array, int x, int y) 
{
	switch (array)
	{
	case 1:		//yellow
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetYellowColor(), "��");
		break;

	case 2:		//red
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetRedColor(), "��");
		break;

	case 3:		//pink
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetPinkColor(), "��");
		break;

	case 4:		//green
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetGreenColor(), "��");
		break;

	case 5:		//orange
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetOrangeColor(), "��");
		break;

	case 6:		//blue
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlueColor(), "��");
		break;

	case 7:		//cyan
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetCyanColor(), "��");
		break;

	case 9:		//black
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlackColor(), "��");
		break;
	}
}

//===============================================================
// �l�N�X�g�u���b�N�`��
//===============================================================
void CGame::DrawNextBlocks(const int array, int x, int y,int h)
{
	switch (array) 
	{
	case 1:		//yellow
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetYellowColor(), "��");
		break;

	case 2:		//red
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetRedColor(), "��");
		break;

	case 3:		//pink
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetPinkColor(), "��");
		break;

	case 4:		//green
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetGreenColor(), "��");
		break;

	case 5:		//orange
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetOrangeColor(), "��");
		break;

	case 6:		//blue
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetBlueColor(), "��");
		break;

	case 7:		//cyan
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetCyanColor(), "��");
		break;
	}
}

//===============================================================
// �z�[���h�u���b�N�`��
//===============================================================
void CGame::DrawHoldBlock(const int array, int x, int y)
{
	switch (array)
	{
	case 1:		//yellow
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetYellowColor(), "��");
		break;

	case 2:		//red
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetRedColor(), "��");
		break;

	case 3:		//pink
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetPinkColor(), "��");
		break;

	case 4:		//green
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetGreenColor(), "��");
		break;

	case 5:		//orange
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetOrangeColor(), "��");
		break;

	case 6:		//blue
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetBlueColor(), "��");
		break;

	case 7:		//cyan
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetCyanColor(), "��");
		break;
	}
}

//===============================================================
// �|�[�Y�`��
//===============================================================
void CGame::DrawPause() 
{
	DrawFormatStringToHandle(190, 100, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iPauseFontHandle, "PAUSE");
	DrawFormatStringToHandle(230, 210, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMinPauseFontHandle, "RETURN GAME");
	DrawFormatStringToHandle(230, 290, g_cScene->m_cColor->GetBlackColor(), g_cScene->m_cGUI->m_iMinPauseFontHandle, "RETURN TITLE");

	if (m_bReturnGame) 
	{
		//RETURN GAME
		DrawLine(190, 250, 460, 250, g_cScene->m_cColor->GetBlackColor());
	}
	else
	{
		//RETURN TITLE
		DrawLine(190, 330, 460, 330, g_cScene->m_cColor->GetBlackColor());
	}

	for (int y = 0; y < BLOCK_HEIGHT; y++) 
	{
		for (int x = 0; x < BLOCK_WIDTH; x++) 
		{
			DrawPauseIcon(m_iPauseIconBlock[y][x], x, y);
		}
	}
}

//===============================================================
// �|�[�Y�A�C�R���`��
//===============================================================
void CGame::DrawPauseIcon(const int array, int x, int y) 
{
	if (array != 0)
	{
		if (m_bReturnGame)
		{
			//black
			DrawFormatString(x*BLOCK_INTERVAL + 170, y*BLOCK_INTERVAL + 190, g_cScene->m_cColor->GetBlackColor(), "��");
		}
		else
			//black
			DrawFormatString(x*BLOCK_INTERVAL + 170, y*BLOCK_INTERVAL + 270, g_cScene->m_cColor->GetBlackColor(), "��");
	}
}