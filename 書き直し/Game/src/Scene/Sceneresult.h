#pragma once

//定義関連---------------------------
//-----------------------------------



class Result
{
private:

	enum tagResultScene {
		INIT,
		LOAD,
		STARTWAIT,
		MAIN,
		ENDWAIT,
		END,
	};

	tagResultScene m_state;
	int m_hndl;
	int m_hndll;
	int m_score;

	int m_ResurtID;

public:
	//コンストラクタ・デストラクタ
	Result();
	~Result();

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


};




