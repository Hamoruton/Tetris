#pragma once
#ifndef __TRANSITION_H_INCLUDED__
#define __TRANSITION_H_INCLUDED__

#define COUNT_DOWN_TEXT_X  300
#define COUNT_DOWN_TEXT_Y  200

//===============================================================
// トランジションクラス
//===============================================================
class CTransition
{
private:
	//フェイドアウト.フェイドインタイマー
	int m_iFadeOutTimer;
	int m_iFadeInTimer;

	//カウントダウンタイマー
	int m_iCountDownTimer;
	int m_iCount;

public:
	//コンストラクタ.デストラクタ
	CTransition();
	~CTransition();

	//描画
	bool FadeOut();		//フェイドアウト
	bool FadeIn();		//フェイドイン

	void CountDown();	//ゲーム開始カウントダウン
};

#endif


