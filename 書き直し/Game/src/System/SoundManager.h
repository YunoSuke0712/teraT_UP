#pragma once
#include <DxLib.h>
#include<vector>
using namespace std;

// BGM/SE全体を管理する
class SoundManager {
public:
	enum tagID
	{
		BGM_GAME,		//ゲーム音
		SE_PSHOT,		//プレイヤーの弾
		SE_EXPROSION,	//爆発音

		SOUND_NUM,
	};
private:
	static vector<int> m_hndl; //音楽ハンドル

public:
	// 初期化
	static void Init();
	// モデルデータのロード
	static void Load();
	// 終了時のデータ破棄など
	static void Exit();

	//音楽再生
	static bool Play(tagID id, int type = DX_PLAYTYPE_BACK, bool isStart = true);
	//音楽停止
	static void Stop(tagID id);
	//音楽全停止
	static void AllStop();
		
		
	//音楽を再生中
	static bool IsPlay(tagID id);



};