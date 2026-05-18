#pragma once
#include"PlayScene.h"
#include"Scenetitle.h"
#include"Sceneresult.h"
#include"../lib/input/input.h"
#include"../lib/Fade/Fade.h"




// 複数のカメラを管理する
class SceneManager {
private:
	// ゲームの処理の流れ
	enum tagScene {
		INIT,   // データ初期化
		TITLE,
		GAME,
		RESULT,
	};

	CInput m_input;
	CFade m_fade;

	PlayScene m_play;
	tagScene m_sceneID;         // 現在の状態遷移
	CTitle m_title;
	Result m_result;

public:
	// コンストラクタ・デストラクタ
	SceneManager();
	~SceneManager();

	// 実行処理
	int Loop();
	// 描画処理
	void Draw();

};