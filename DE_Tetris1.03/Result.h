#pragma once
#ifndef __RESULT_H_INCLUDED__
#define __RESULT_H_INCLUDED__

//===============================================================
// リザルトクラス
//===============================================================
class CResult
{
private:
	//フォントハンドル
	int m_iResultFontHandle;

	//テキスト点滅
	int m_iBlendCount = 0;
	//条件:255以上かどうか
	bool m_bBlendLimitMax = false;
	//タイマー
	int m_iBlendTimer = 0;

public:
	//コンストラクタ.デストラクタ
	CResult();
	~CResult();

private:
	//入力処理
	void CheckUserInput();

public:
	//動作処理
	void Move();

	//描画処理
	void Draw();
private:
	void ResultUI();
	void TextFlash();
};

#endif



