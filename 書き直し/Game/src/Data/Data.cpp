#include"Data.h"
#include<math.h>
#include"../lib/Common/common.h"

//③
CData* CData::m_Instance = NULL;

//④
CData* CData::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CData();
	}
	return m_Instance;
}

//⑥
void CData::DeleteInstance()
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}





//コンス・デスト
CData::CData()
{
	m_PlayMapID = 0;
	m_Score = 0;
}

CData::~CData()
{

}


