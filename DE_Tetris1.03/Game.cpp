#include <time.h>
#include "DxLib.h"
#include "Scene.h"

//ゲームクラス変数
CGame* g_cGame;

//===============================================================
// コンストラクタ
//===============================================================
CGame::CGame()
{
	//ウォール初期化
	InitWall();
	//ブロック初期化
	InitBlock();

	//BGM再生
	PlaySoundMem(g_cScene->m_cSound->m_iBGMGame, DX_PLAYTYPE_LOOP);
}

//===============================================================
// デストラクタ
//===============================================================
CGame::~CGame() 
{
	//BGM停止
	StopSoundMem(g_cScene->m_cSound->m_iBGMGame);
}

//===============================================================
// ウォール初期化
//===============================================================
void CGame::InitWall() 
{
	for (int y = 1; y < STAGE_HEIGHT; y++) 
	{
		for (int x = 0; x < STAGE_WIDTH; x++) 
		{
			//左の壁
			m_iStage[y][0] = 9;

			//下の壁
			m_iStage[STAGE_HEIGHT-1][x] = 9;

			//右の壁
			m_iStage[y][STAGE_WIDTH - 1] = 9;
		}
	}
}

//===============================================================
// ブロック初期化
//===============================================================
void CGame::InitBlock() 
{
	//ブロックの種類
	srand(time(NULL));
	m_iBlockID = rand() % 7;

	for (int y = 0; y < BLOCK_HEIGHT; y++) 
	{
		for (int x = 0; x < BLOCK_WIDTH; x++) 
		{
			m_iBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][x];
		}
	}

	//ネクストブロックの種類
	for (int i = 0; i < sizeof(m_iNextBlockID) / sizeof(int); i++) 
	{
		m_iNextBlockID[i] = rand() % 7;
	}
}

//===============================================================
// プレイヤー入力処理
//===============================================================
void CGame::CheckUserInput() 
{
	//回転
	if (g_cScene->m_iKey[KEY_INPUT_UP] == 1)
	{
		Rotate();
	}

	//一番下まで落下
	if (g_cScene->m_iKey[KEY_INPUT_RSHIFT] == 1)
	{
		while (IsValid()) 
		{
			m_iBlockY++;
		}
		m_iBlockY--;
	}

	//ホールド
	if (g_cScene->m_iKey[KEY_INPUT_RCONTROL] == 1)
	{
		HoldBlock();
	}

	//左右下移動
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
// ポーズ
//===============================================================
bool CGame::Pause() 
{
	//ポーズ
	if (g_cScene->m_iKey[KEY_INPUT_P] == 1)
	{
		//反転
		m_bPause = !m_bPause;
	}

	if (m_bPause) 
	{
		if (m_bReturnGame) 
		{
			if (g_cScene->m_iKey[KEY_INPUT_RETURN] == 1)
			{
				//ゲーム画面
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
				//タイトル画面
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
// 動作処理
//===============================================================
void CGame::Move() 
{
	//ポーズ
	if (Pause())
		return;

	//プレイヤー入力処理
	CheckUserInput();

	//ブロック自由落下
	FreeDrop();
}

//===============================================================
// ブロック自由落下
//===============================================================
void CGame::FreeDrop() 
{
	//落下処理
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
// ブロック生成
//===============================================================
void CGame::Generate()
{
	//ゲームオーバー
	if (IsGameOver())
	{
		g_cScene->m_eSceneStatus = g_cScene->RESULTTRANSITION;
		return;
	}

	//ブロックの座標をステージに保存
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			m_iStage[m_iBlockY + y][m_iBlockX + x] += m_iBlock[y][x];
		}
	}

	//ブロッククリア
	while(IsClear()) 
	{
		AffterClear();
		m_iLineCount++;
	}
	AddScore();

	//ブロック入れ替え
	ExchangeNextBlocks();

	//ブロック座標初期化
	m_iBlockX = 5;
	m_iBlockY = 0;
	m_iDropCount = 0;
	m_iHoldCount = 0;
}

//===============================================================
// ネクストブロック
//===============================================================
void CGame::ExchangeNextBlocks() 
{
	//ブロック入れ替え
	m_iBlockID = m_iNextBlockID[0];

	for (int i = 0; i < BLOCK_NEXT_NUM - 1; i++) 
	{
		m_iNextBlockID[i] = m_iNextBlockID[i + 1];
	}

	srand(time(NULL));
	m_iNextBlockID[BLOCK_NEXT_NUM - 1] = rand() % 7;

	//ネクストブロックを登録
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			m_iBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][x];
		}
	}
}

//===============================================================
// ホールドブロック
//===============================================================
void CGame::HoldBlock() 
{
	int tempID = 0;

	if (m_bFirstHold) 
	{
		//ホールド制限
		m_iHoldCount++;
		if (m_iHoldCount > 1)
		{
			return;
		}

		//ID入れ替え
		tempID = m_iBlockID;
		m_iBlockID = m_iHoldBlockID;
		m_iHoldBlockID = tempID;

		//ホールドブロック登録
		for (int y = 0; y < BLOCK_HEIGHT; y++)
		{
			for (int x = 0; x < BLOCK_WIDTH; x++)
			{
				m_iBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][x];
			}
		}

		//ブロック座標初期化
		m_iBlockX = 5;
		m_iBlockY = 0;
		m_iDropCount = 0;

	}
	else 
	{
		//ID保存
		m_iHoldBlockID = m_iBlockID;

		//ブロック入れ替え
		ExchangeNextBlocks();

		//ブロック座標初期化
		m_iBlockX = 5;
		m_iBlockY = 0;
		m_iDropCount = 0;

		//ホールド制限
		m_bFirstHold = true;
	}
}

//===============================================================
// ブロック有効範囲
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
// ゴーストブロック有効範囲
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
// ブロック回転
//===============================================================
void CGame::Rotate()
{
	bool isTurn = true;
	m_iTurn++;

	//回転後ブロック
	for (int y = 0; y < BLOCK_HEIGHT; y++)
	{
		for (int x = 0; x < BLOCK_WIDTH; x++)
		{
			m_iRotateBlock[y][x] = m_iTetrimino[(m_iBlockID*BLOCK_HEIGHT) + y][(m_iTurn % 4)*BLOCK_WIDTH + x];
		}
	}

	//当たり判定
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

	//回転後ブロック代入
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
// ブロッククリア
//===============================================================
bool CGame::IsClear() 
{
	//ブロックの数→横1列10個でクリア
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
// ブロッククリア後の落下
//===============================================================
void CGame::AffterClear() 
{
	PlaySoundMem(g_cScene->m_cSound->m_iSEBlockClear, DX_PLAYTYPE_BACK);

	//ブロッククリア
	for (int x = 1; x < STAGE_WIDTH - 1; x++)
	{
		m_iStage[m_iClearLineY][x] = 0;
	}

	//ブロック落下
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
// レベルアップ
//===============================================================
void CGame::LevelUp() 
{
	//0以外の10の倍数条件
	if (m_iFullLines != 0)
	{
		m_bLevelUpStart = true;
	}

	//レベルアップ処理
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
// スコアの加算（条件:ライン数（レベル数*加点））
//===============================================================
void CGame::AddScore() 
{
	switch (m_iLineCount) 
	{
	case 1:		//1列
		m_iScore += ((m_iLevel + 1) * 10);
		break;

	case 2:		//2列
		m_iScore += ((m_iLevel + 1) * 20);
		break;

	case 3:		//3列
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
// ゲームオーバー
//===============================================================
bool CGame::IsGameOver()
{
	//ステージ外でブロックと衝突したかどうか
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
// 描画処理
//===============================================================
void CGame::Draw() 
{
	if (!m_bPause) {
		//ブロック描画
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

		//ゴーストブロック描画
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

		//ステージ描画
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

		//ネクストブロック描画
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

		//ホールドブロック描画
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
// ブロック描画
//===============================================================
void CGame::DrawBlock(int array, int x, int y)
{
	switch (array) 
	{
	case 1:		//yellow
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetYellowColor(), "■");
		break;

	case 2:		//red
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetRedColor(), "■");
		break;

	case 3:		//pink
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetPinkColor(), "■");
		break;

	case 4:		//green
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetGreenColor(), "■");
		break;

	case 5:		//orange
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetOrangeColor(), "■");
		break;

	case 6:		//blue
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlueColor(), "■");
		break;

	case 7:		//cyan
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetCyanColor(), "■");
		break;
	}
}

//===============================================================
// ゴーストブロック描画
//===============================================================
void CGame::DrawGhostBlock(int array, int x, int y)
{
	//Y座標
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
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetYellowColor(), "■");
		break;

	case 2:		//red
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetRedColor(), "■");
		break;

	case 3:		//pink
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetPinkColor(), "■");
		break;

	case 4:		//green
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetGreenColor(), "■");
		break;

	case 5:		//orange
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetOrangeColor(), "■");
		break;

	case 6:		//blue
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlueColor(), "■");
		break;

	case 7:		//cyan
		DrawFormatString((m_iBlockX + x)*BLOCK_INTERVAL + STAGE_CENTER_X, (m_iGhostBlockY + y)*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetCyanColor(), "■");
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

//===============================================================
// ステージ描画
//===============================================================
void CGame::DrawStage(int array, int x, int y) 
{
	switch (array)
	{
	case 1:		//yellow
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetYellowColor(), "■");
		break;

	case 2:		//red
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetRedColor(), "■");
		break;

	case 3:		//pink
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetPinkColor(), "■");
		break;

	case 4:		//green
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetGreenColor(), "■");
		break;

	case 5:		//orange
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetOrangeColor(), "■");
		break;

	case 6:		//blue
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlueColor(), "■");
		break;

	case 7:		//cyan
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetCyanColor(), "■");
		break;

	case 9:		//black
		DrawFormatString(x*BLOCK_INTERVAL + STAGE_CENTER_X, y*BLOCK_INTERVAL + STAGE_CENTER_Y, g_cScene->m_cColor->GetBlackColor(), "■");
		break;
	}
}

//===============================================================
// ネクストブロック描画
//===============================================================
void CGame::DrawNextBlocks(const int array, int x, int y,int h)
{
	switch (array) 
	{
	case 1:		//yellow
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetYellowColor(), "■");
		break;

	case 2:		//red
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetRedColor(), "■");
		break;

	case 3:		//pink
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetPinkColor(), "■");
		break;

	case 4:		//green
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetGreenColor(), "■");
		break;

	case 5:		//orange
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetOrangeColor(), "■");
		break;

	case 6:		//blue
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetBlueColor(), "■");
		break;

	case 7:		//cyan
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_NEXT_X, y*BLOCK_INTERVAL + BLOCK_NEXT_Y + h * BLOCK_NEXT_INTERVAL, g_cScene->m_cColor->GetCyanColor(), "■");
		break;
	}
}

//===============================================================
// ホールドブロック描画
//===============================================================
void CGame::DrawHoldBlock(const int array, int x, int y)
{
	switch (array)
	{
	case 1:		//yellow
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetYellowColor(), "■");
		break;

	case 2:		//red
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetRedColor(), "■");
		break;

	case 3:		//pink
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetPinkColor(), "■");
		break;

	case 4:		//green
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetGreenColor(), "■");
		break;

	case 5:		//orange
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetOrangeColor(), "■");
		break;

	case 6:		//blue
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetBlueColor(), "■");
		break;

	case 7:		//cyan
		DrawFormatString(x*BLOCK_INTERVAL + BLOCK_HOLD_X, y*BLOCK_INTERVAL + BLOCK_HOLD_Y, g_cScene->m_cColor->GetCyanColor(), "■");
		break;
	}
}

//===============================================================
// ポーズ描画
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
// ポーズアイコン描画
//===============================================================
void CGame::DrawPauseIcon(const int array, int x, int y) 
{
	if (array != 0)
	{
		if (m_bReturnGame)
		{
			//black
			DrawFormatString(x*BLOCK_INTERVAL + 170, y*BLOCK_INTERVAL + 190, g_cScene->m_cColor->GetBlackColor(), "■");
		}
		else
			//black
			DrawFormatString(x*BLOCK_INTERVAL + 170, y*BLOCK_INTERVAL + 270, g_cScene->m_cColor->GetBlackColor(), "■");
	}
}