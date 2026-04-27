#include<DxLib.h>

//これも追加しておくと、フレームレート自体の変更が可能になる
//このフレームで固定
#define FRAME_RATE (60)
//上のフレームレートだと一フレームに何ミリ秒かかるか
#define FRAME_RATE_MILI_SECOND (1000/FRAME_RATE)


//FPSを表示するのに使用するデータがまとまった構造体

typedef struct {
	float m_frameRate;	//今のフレームレートを保存
	int m_nowTime;		// 現在時間
	int m_prevTime;		//ひとつ前の時間
	int m_count;		//カウント用


	int m_prebDrawTime; //1つ前にFPSを表示した時間
	int m_score;
}FpsData;

FpsData g_fps;  //実際にfps表示に使用する変数

//初期化関数
void InitFps()
{
	//基本的に０で初期化
	g_fps.m_frameRate = 0.0f;
	g_fps.m_nowTime = GetNowCount();
	g_fps.m_prevTime = 0;
	g_fps.m_count = 0;
	g_fps.m_prebDrawTime = 0;

	g_fps.m_score = 0;
}

bool IsNextFame()
{
	//現在の時間を習得
	g_fps.m_nowTime = GetNowCount();
	//前回の時間と今回の時間を取得
	int difTime = g_fps.m_nowTime - g_fps.m_prevTime;

	//想定している1フレにかかる時間を超えたら
	if (difTime > FRAME_RATE_MILI_SECOND)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StepFps()
{
	//ひとつ前の時間を更新
	g_fps.m_prevTime = g_fps.m_nowTime;
}





//FPS表示関数
void PrintFps()
{
	//まずはカウントを増やす
	g_fps.m_count++;
	//前回の時間と今回の時間を取得
	int difTime = g_fps.m_nowTime - g_fps.m_prebDrawTime;

	//差異が1秒事情あれば計三開始（１秒毎に１回フレームレートの表示を更新
	if (difTime >= 1000)
	{
		//ある程度正常に動いていたら、m_countは60になっているはず
		float frameCount = (float)(g_fps.m_count * 1000);
		//表示するFPSを変更
		g_fps.m_frameRate = frameCount / difTime;
		//カウントは0に初期化
		g_fps.m_count = 0;
		//ひとつ前の時間を更新
		g_fps.m_prebDrawTime = g_fps.m_nowTime;
	}
	DrawFormatString(16, 16, GetColor(255, 0, 0), "FPS  :%.2f", g_fps.m_frameRate);


	
}
//FPSは常に表示を続ける

