#include"GimmickManager.h"

// モデルデータのパス
static const char ENEMY_MODEL_PATH[] = "data/model/enemy/enemy.mv1";
static const char DANAGER_MODEL_PATH[] = "data/model/enemy/danger.mv1";

static const char CsvA[] = "data/csv/Map01/Gimmick.csv";



// 敵の再出現時間
static const int WAIT_TIME = 180.0f;

//コンストラクタ
GimmickManager::GimmickManager()
{
}


//初期化
void GimmickManager::Init()
{
	for (int i = 0; i < ENEMYA_MAX_NUM; i++)
	{
		m_Gimmick[i].SetGimmickID(i);
		m_Gimmick[i].Init();

	}


	m_SoundCage = 0;
}

//ロード
void GimmickManager::Load()
{
	int Ahndl = MV1LoadModel(ENEMY_MODEL_PATH);
	int Dangerhndl = MV1LoadModel(DANAGER_MODEL_PATH);


	int PosHndl = FileRead_open(CsvA);
	FILE* FilePointer;
	if (fopen_s(&FilePointer, CsvA, "r") != 0)return;
	ReadPosData tmp = { 0 };
	while (FileRead_eof(PosHndl) == 0)
	{
		FileRead_scanf(PosHndl, "%f,", &tmp.m_Pos_X);
		FileRead_scanf(PosHndl, "%f,", &tmp.m_Pos_Y);
		FileRead_scanf(PosHndl, "%f,", &tmp.m_Pos_Z);

		Gimmick* tEmp;
		tEmp = new Gimmick();
		tEmp->SetPosition(VGet(tmp.m_Pos_X, tmp.m_Pos_Y, tmp.m_Pos_Z));
		m_EneA_List.push_back(tEmp);

		tEmp->Load(Ahndl, Dangerhndl);

		m_InfoList.push_back(tmp);
	}
	fclose(FilePointer);

	MV1DeleteModel(Ahndl);
	MV1DeleteModel(Dangerhndl);
}

//ループ
void GimmickManager::Step(VECTOR P_pos, int level, VECTOR D_pos)
{
	for (auto A : m_EneA_List)
	{
		A->Step(P_pos, level, D_pos);
	}

	//slot.SetSoundCage(m_SoundCage);
	if (m_SoundCool > 0)
	m_SoundCool--;
}

//描画
void GimmickManager::Draw()
{
	for (auto A : m_EneA_List)
	{
		A->Draw();
	}
}

//終了
void GimmickManager::Exit()
{
	for (auto A : m_EneA_List)
	{
		A->Exit();

		delete A; // メモリ解放
	}

	m_EneA_List.clear(); // リストを空にする

	m_InfoList.clear();  // 座標情報も消す
}


//敵をリクエスト
void GimmickManager::Request(VECTOR P_pos)
{
	for (auto A : m_EneA_List)
	{
		A->Request(P_pos);
	}


}

//----------------------
//	更新
//----------------------
void GimmickManager::Update()
{
	for (auto A : m_EneA_List)
	{
		A->Update();
	}
	
}

