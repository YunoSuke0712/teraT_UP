#pragma once



class CInput
{
public:

	#define KEY_UP			(0b1)			//上ボタン
	#define KEY_DOWN		(0b10)			//下ボタン
	#define KEY_RIGHT		(0b100)			//右ボタン
	#define KEY_LEFT		(0b1000)		//左ボタン
	#define KEY_JUMP		(0b10000)		//ジャンプ
	#define KEY_DASH		(0b100000)		//ダッシュ
	#define KEY_CLICK		(0b1000000)		//←click
	#define KEY_RCLICK		(0b10000000)	//→click
	#define KEY_WHEEL_UP	(0b100000000)	//ホイール上
	#define KEY_WHEEL_DOWN	(0b1000000000)	//ホイール下
	#define KEY_PAUSE		(0b10000000000)	//キャンセルボタン

	//キー入力情報の初期化
	void InitInput();
	//キー入力情報を更新
	void UpdateInput();
	//キーを押したか（通常判定）
	bool IsInputRep(unsigned int key);
	//キーを押したか（通常判定）
	bool IsInputTrg(unsigned int key);
	//キーを離したか（通常判定）
	bool IsInputRel(unsigned int key);


	
private:

};


