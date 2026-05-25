#pragma once
#include<DxLib.h>
#include"../lib/Input/input.h"
#include"../lib/Input/PadInput.h"

class CData {
private:
	CInput m_input;

	int m_PlayMapID;
	float m_Score;

public:
	
	CData();
	~CData();

public:
	void SetPlayMapID(int id) { m_PlayMapID = id; }
	int	 GetPlayMapID() { return  m_PlayMapID; }

};