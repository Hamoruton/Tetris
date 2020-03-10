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
// ゲームクラス
//===============================================================
class CGame
{
private:
	//ステージ配列（ブロックの情報を代入していき最終的な描画の情報を示す）
	int m_iStage[STAGE_HEIGHT][STAGE_WIDTH] = { 0 };

	//ブロック配列
	int m_iBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };

	//回転後のブロック配列（回転後のブロック情報を一時的に保管し当たり判定の有無をみるための変数）
	int m_iRotateBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = { 0 };

	//ネクストブロック配列
	int m_iNextBlockID[BLOCK_NEXT_NUM] = { 0 };

	//ブロック座標
	int m_iBlockX = 5;
	int m_iBlockY = 0;
	int m_iGhostBlockY = 0;

	//1列ブロッククリア時のY座標
	int m_iClearLineY = 0;
public:
	//1列ブロックをクリアした合計数
	int m_iFullLines = 0;

private:
	//ブロックID（7個にm_iTetrimino配列を区切るための変数）
	int m_iBlockID = 0;
	//ターン変数 (4パターンにm_iTetrimino配列を区切るための変数)
	int m_iTurn = 0;

	//ブロックの自由落下を調整する変数
	int m_iDropCount = 0;
	int m_iLimitCount = 60;

public:
	//レベル（10列ブロックをクリアするごとにレベルアップ）
	int m_iLevel = 0;
private:
	//条件:0以外の10の倍数
	bool m_bLevelUpStart = false;
	//条件:10の倍数になった時1度だけ
	bool m_bLevelUp = false;

public:
	//ポーズ
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
	//スコア
	int m_iScore = 0;

	//条件:テトリス（4列同時消し）でテキスト表示
	bool m_bTextFlash = false;
private:
	int m_iLineCount = 0;
	
	//ホールド
	int m_iHoldBlockID = 0;
	int m_iHoldCount = 0;
	bool m_bFirstHold = false;

	//テトリミノ配列
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
	//コンストラクタ.デストラクタ
	CGame();
	~CGame();

private:
	//初期化
	void InitWall();
	void InitBlock();

	//入力処理
	void CheckUserInput();		    //プレイヤー入力処理
	bool Pause();					//ポーズ

public:
	//動作処理
	void Move();
private:
	void FreeDrop();				//ブロック自由落下
	void Generate();				//ブロック生成
	void ExchangeNextBlocks();		//ネクストブロック
	void HoldBlock();				//ホールドブロック
	bool IsValid();					//ブロック有効範囲
	bool IsGhostValid();			//ゴーストブロック有効範囲
	void Rotate();					//ブロック回転
	bool IsClear();					//ブロッククリア
	void AffterClear();				//ブロッククリア後の落下
	void LevelUp();					//レベルアップ
	void AddScore();				//スコアの加算
	bool IsGameOver();				//ゲームオーバー

public:
	//描画処理
	void Draw();
private:
	void DrawBlock(int array, int x, int y);					//ブロック描画
	void DrawGhostBlock(int array, int x, int y);				//ゴーストブロック描画
	void DrawStage(int array, int x, int y);					//ステージ描画
	void DrawNextBlocks(const int array, int x, int y, int h);	//ネクストブロック描画
	void DrawHoldBlock(const int array, int x, int y);			//ホールドブロック描画
	void DrawPause();											//ポーズ描画
	void DrawPauseIcon(const int array, int x, int y);			//ポーズアイコン描画
};
extern CGame* g_cGame;

#endif

