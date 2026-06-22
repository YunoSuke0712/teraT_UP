#include"EnemyManager.h"

// モデルデータのパス
static const char ENEMY_MODEL_PATH[] = "data/model/enemy/trian.mv1";
static const char ENEMYB_MODEL_PATH[] = "data/model/enemy/enemyB.mv1";
static const char DANAGER_MODEL_PATH[] = "data/model/enemy/danger.mv1";

static const char ENEMYA_ROOT[][5][200] =
{
	{""},//map０は存在しない

	{	//map1
		"",
		"data/model/field/Map01/Map01_EnemyARoot_01.mv1"
	},

	{	//map2
		"",
		"data/model/field/Map02/Map02_EnemyARoot_01.mv1"
	},

	{
		//map3
		"",
		"data/model/field/Map03/Map03_EnemyARoot_01.mv1", 
		"data/model/field/Map03/Map03_EnemyARoot_02.mv1"
	},
};

static const char ENEMYA_POS[][200] =
{
	{""},
	{"data/csv/Map01/EnemyA.csv"},
	{"data/csv/Map02/EnemyA.csv"},
	{"data/csv/Map03/EnemyA.csv"},
};
static const char ENEMYB_POS[][200] =
{
	{""},
	{"data/csv/Map01/EnemyB.csv"},
	{"data/csv/Map02/EnemyB.csv"},
	{"data/csv/Map03/EnemyB.csv"},
};



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

}

//ロード
void EnemyManager::Load(int mapID)
{
	EnemyAData(mapID);

}

//ループ
void EnemyManager::Step(VECTOR P_pos, int level, VECTOR D_pos)
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

		delete A; // メモリ解放
	}

	m_EneA_List.clear(); // リストを空にする

	m_InfoList.clear();  // 座標情報も消す
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


void EnemyManager::EnemyAData(int mapID)
{
	int Ahndl = MV1LoadModel(ENEMY_MODEL_PATH);
	int Dangerhndl = MV1LoadModel(DANAGER_MODEL_PATH);

	int Open = FileRead_open(ENEMYA_POS[mapID]);


	FILE* FilePointer;
	if (fopen_s(&FilePointer, ENEMYA_POS[mapID], "r") != 0)return;
	ReadPosData tmp = { 0 };

	while (true)
	{
		int type = FileRead_scanf(Open, "%d,", &tmp.m_Type);
		int x = FileRead_scanf(Open, "%f,", &tmp.m_Pos_X);
		int y = FileRead_scanf(Open, "%f,", &tmp.m_Pos_Y);
		int z = FileRead_scanf(Open, "%f,", &tmp.m_Pos_Z);
		int root = FileRead_scanf(Open, "%d,", &tmp.m_RootNum);
		int rID = FileRead_scanf(Open, "%d,", &tmp.m_RootID);
		int rot = FileRead_scanf(Open, "%f", &tmp.m_RotationY);
		
		// どれか失敗したら終了
		if (type == -1 || x == -1 || y == -1 || z == -1 || root == -1 || rID == -1 || rot == -1)
		{
			break;
		}

		EnemyA* tEmp = new EnemyA();

		tEmp->SetPosition(VGet(tmp.m_Pos_X, tmp.m_Pos_Y, tmp.m_Pos_Z));
		tEmp->SetType(tmp.m_Type);
		tEmp->SetRootNum(tmp.m_RootNum);
		tEmp->SetRotationY(DegToRad(tmp.m_RotationY));//度をラジアンに変換しながら値を渡す


		m_EneA_List.push_back(tEmp);


		int Roothndl = MV1LoadModel(ENEMYA_ROOT[mapID][tmp.m_RootID]);

		tEmp->Load(Ahndl, Dangerhndl, Roothndl);

		m_InfoList.push_back(tmp);
	}
	fclose(FilePointer);

	MV1DeleteModel(Ahndl);
	MV1DeleteModel(Dangerhndl);
}

