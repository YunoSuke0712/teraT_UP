#pragma once


class Debug {
private:

	typedef struct {
		float m_frameRate;	//今のフレームレートを保存
		int m_nowTime;		// 現在時間
		int m_prevTime;		//ひとつ前の時間
		int m_count;		//カウント用


		int m_prebDrawTime; //1つ前にFPSを表示した時間
		int m_score;
	}FpsData;

	FpsData g_fps;  //実際にfps表示に使用する変数

public:

	//FPS表示
	void PrintFps();
	void InitFps();

	//次の処理へ進んでよいか判断
	bool IsNextFame();
	//FPS更新関数
	void StepFps();
};




