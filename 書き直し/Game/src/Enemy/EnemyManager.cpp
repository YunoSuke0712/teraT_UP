#include"EnemyManager.h"

// モデルデータのパス
static const char ENEMY_MODEL_PATH[] = "data/model/enemy/enemy.mv1";
static const char ENEMYB_MODEL_PATH[] = "data/model/enemy/enemyB.mv1";
static const char ENEMYB2_MODEL_PATH[] = "data/model/enemy/enemyB2.mv1";
static const char DANAGER_MODEL_PATH[] = "data/model/enemy/danger.mv1";

static const char CsvA[] = "data/csv/Map01/EnemyA.csv";
static const char CsvB[] = "data/csv/Map01/EnemyA.csv";



// 敵の再出現時間
static const int WAIT_TIME = 180.0f;

//コンストラクタ
EnemyManager::EnemyManager()
{
}


//初期化
void EnemyManager::Init()
{
	for (int i = 0; i < ENEMYA_MAX_NUM; i++)
	{
		m_EnemyA[i].SetEnemyID(i);
		m_EnemyA[i].Init();

	}


	m_SoundCage = 0;
}

//ロード
void EnemyManager::Load()
{
	int Ahndl = MV1LoadModel(ENEMY_MODEL_PATH);
	int Bhndl = MV1LoadModel(ENEMYB_MODEL_PATH);
	int Bhndll = MV1LoadModel(ENEMYB2_MODEL_PATH);
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

		EnemyA* tEmp;
		tEmp = new EnemyA();
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
void EnemyManager::Step(VECTOR P_pos, int level, VECTOR D_pos)
{
	for (auto A : m_EneA_List)
	{
		A->Step(P_pos, level, D_pos);
	}

	//slot.SetSoundCage(m_SoundCage);
	if (m_SoundCool > 0);
	m_SoundCool--;
}

//描画
void EnemyManager::Draw()
{
	for (auto A : m_EneA_List)
	{
		A->Draw();
	}
}

//終了
void EnemyManager::Exit()
{
	for (auto A : m_EneA_List)
	{
		A->Exit();
	}

}


//敵をリクエスト
void EnemyManager::Request(VECTOR P_pos)
{
	for (auto A : m_EneA_List)
	{
		A->Request(P_pos);
	}


}

//----------------------
//	更新
//----------------------
void EnemyManager::Update()
{
	for (auto A : m_EneA_List)
	{
		A->Update();
	}
	
}

