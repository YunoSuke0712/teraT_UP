#pragma once
#include "../lib/input/input.h"
#include "../lib/Fade/Fade.h"
#include "../Data/Data.h"

//定義関連---------------------------
#define TITLE_SIZE_X (1600.0f) //画面サイズ(横)
#define TITLE_SIZE_Y (900.0f) //画面サイズ(縦)
//-----------------------------------
static const int TITLE_MAX_HNDL = 20;
static const int CARD_MAX = 3;

class CTitle
{
private:
	CInput m_input;
	CFade m_fade;
	CData m_data;

	enum tagTitleScene {
		INIT,
		LOAD,
		STARTWAIT,
		MAIN,
		ENDWAIT,
		END,
	};
	enum tagTitleMainScene	{
		Fast,
		Select,
		Map,
	};

	tagTitleScene m_state;



	int m_hndl[TITLE_MAX_HNDL];
	int m_TitleSelect;
	int m_NowSelect;


	bool m_UI_active;

	int m_TitleCoolTime;

	float m_cardPosX[CARD_MAX];


public:
	//コンストラクタ・デストラクタ
	CTitle();
	~CTitle();

	//実行処理
	int Loop();
	//タイトル全体の描画管理
	void Draw();

private:
	//タイトルの初期化
	void Init();
	//タイトルの終了処理
	void Exit();
	//ロード
	void Load();
	// 毎フレーム
	void Step();


	//
	void UISwitch();



};

