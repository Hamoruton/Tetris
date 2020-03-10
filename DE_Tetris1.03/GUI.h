#pragma once
#ifndef __GUI_H_INCLUDED__
#define __GUI_H_INCLUDED__

#define PI		3.1415926

//画像
#define BACK_CHIP "Assets/Sprites/BG01.png"

#define KEY_ARROW_CHIP "Assets/Sprites/KeyArrow.png"
#define KEY_SHIFT_CHIP "Assets/Sprites/KeyShift.png"
#define KEY_CTRL_CHIP  "Assets/Sprites/KeyCtrl.png"
#define KEY_P_CHIP	   "Assets/Sprites/KeyP.png"

//フォント
#define FONT_CHIP "GAU_font_PRIVAtE"

//座標
#define SCORE_TEXT_Y  10

#define NEXT_TEXT_X  430
#define NEXT_TEXT_Y   50

#define HOLD_TEXT_X	 130
#define HOLD_TEXT_Y	  85

#define HELP_TEXT_Y  200

#define KEY_CHIP_X  160
#define KEY_CHIP_Y  200

//テキスト点滅スピード
#define TEXT_FLASH_SPEED  5

//===============================================================
// GUIクラス
//===============================================================
class CGUI
{
private:
	//背景画像ハンドル
	int m_iGHBackGround;

	//キーボタン画像ハンドル
	int m_iGHKeyArrow;
	int m_iGHKeyShift;
	int m_iGHKeyCtrl;
	int m_iGHKeyP;

public:
	//フォントハンドル
	int m_iFontHandle;
	int m_iMinFontHandle;
	int m_iMaxFontHandle;
	int m_iPauseFontHandle;
	int m_iMinPauseFontHandle;

private:
	//テキスト点滅
	int m_iBlendCount = 0;
	//条件:255以上かどうか
	bool m_bBlendLimitMax = false;
	//タイマー
	int m_iBlendTimer = 0;

public:
	//コンストラクタ.デストラクタ
	CGUI();
	~CGUI();

	//描画処理
	void Draw();
	void BackGround();		//背景画像
	void KeyGraphic();		//キーボタン画像
	void UIText();			//テキスト
	void ScoreText();		//スコアテキスト
	void TextFlash();		//点滅テキスト（4列同時クリアでテトリステキスト表示）
};

#endif



