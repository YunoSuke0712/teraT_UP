#include"GimmickManager.h"

// モデルデータのパス
static const char WAEP_MODEL_PATH[] = "data/model/enemy/enemy.mv1";

static const char CsvA[] = "data/csv/Map01/Warp.csv";


//コンストラクタ
GimmickManager::GimmickManager()
{
}


//初期化
void GimmickManager::Init()
{
	for (int i = 0; i < GIMMICK_MAX_NUM; i++)
	{
		m_Warp[i].SetWarpID(i);
		m_Warp[i].Init();

	}
}

//ロード
void GimmickManager::Load()
{
	int Ahndl = MV1LoadModel(WAEP_MODEL_PATH);
	int Bhndl = MV1LoadModel(WAEP_MODEL_PATH);

	int APosHndl = FileRead_open(CsvA);
	int BPosHndl = FileRead_open(CsvA);

	FILE* FilePointer;
	if (fopen_s(&FilePointer, CsvA, "r") != 0)return;
	ReadPosData tmp = { 0 };
	while (FileRead_eof(APosHndl) == 0 && FileRead_eof(BPosHndl) == 0 )
	{
		FileRead_scanf(APosHndl, "%f,", &tmp.m_PosA_X);
		FileRead_scanf(APosHndl, "%f,", &tmp.m_PosA_Y);
		FileRead_scanf(APosHndl, "%f,", &tmp.m_PosA_Z);
		FileRead_scanf(BPosHndl, "%f,", &tmp.m_PosB_X);
		FileRead_scanf(BPosHndl, "%f,", &tmp.m_PosB_Y);
		FileRead_scanf(BPosHndl, "%f,", &tmp.m_PosB_Z);

		Warp* tEmp;
		tEmp = new Warp();
		tEmp->SetPositionA(VGet(tmp.m_PosA_X, tmp.m_PosA_Y, tmp.m_PosA_Z));
		tEmp->SetPositionB(VGet(tmp.m_PosB_X, tmp.m_PosB_Y, tmp.m_PosB_Z));


		m_Warp_List.push_back(tEmp);

		tEmp->Load(Ahndl, Bhndl);

		m_InfoList.push_back(tmp);
	}
	fclose(FilePointer);

	MV1DeleteModel(Ahndl);
	MV1DeleteModel(Bhndl);
}

//ループ
void GimmickManager::Step(VECTOR P_pos)
{
	for (auto A : m_Warp_List)
	{
		A->Step(P_pos);
	}

	//slot.SetSoundCage(m_SoundCage);
	if (m_SoundCool > 0)
	m_SoundCool--;
}

//描画
void GimmickManager::Draw()
{
	for (auto A : m_Warp_List)
	{
		A->Draw();
	}
}

//終了
void GimmickManager::Exit()
{
	for (auto A : m_Warp_List)
	{
		A->Exit();

		delete A; // メモリ解放
	}

	m_Warp_List.clear(); // リストを空にする

	m_InfoList.clear();  // 座標情報も消す
}


//敵をリクエスト
void GimmickManager::Request(VECTOR P_pos)
{
	for (auto A : m_Warp_List)
	{
		A->Request(P_pos);
	}
}

//----------------------
//	更新
//----------------------
void GimmickManager::Update()
{
	for (auto A : m_Warp_List)
	{
		A->Update();
	}
	
}

