#pragma once
#ifndef __TITLE_H_INCLUDED__
#define __TITLE_H_INCLUDED__

//===============================================================
// タイトルクラス
//===============================================================
class CTitle
{
private:
	//フォント
	int m_iTitleFontHandle;
	int m_iMinTitleFontHandle;

	//プレイライン状態
	bool m_bPlayLineState = true;

	const int m_iIconBlock[4][4] =
	{
		0, 0, 0, 0,
		0, 9, 9, 0,
		0, 9, 9, 0,
		0, 0, 0, 0,
	};

public:
	//コンストラクタ.デストラクタ
	CTitle();
	~CTitle();

private:
	//入力処理
	void CheckUserInput();

public:
	//動作処理
	void Move();

	//描画処理
	void Draw();
private:
	void LineState();
	void DrawIcon(const int* p, int x, int y);
	void IconState();
};

#endif



