#pragma once




class CFade
{

private:



public:
	//フェードを初期化
	void InitFade();
	//フェード処理更新
	void StepFade();
	//フェード用の画像描画
	void DrawFade();

	//フェードインリクエスト
	void RequestFadeIn();
	//フェードアウトリクエスト
	void RequestFadeOut();
	//フェードインが終了したか
	bool IsEndFadeIn();
	//フェードアウトが終了したか
	bool IsEndFadeOut();


};

