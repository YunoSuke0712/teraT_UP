#include"GimmickManager.h"

// モデルデータのパス
static const char WAEP_MODEL_PATH[] = "data/model/gimmick/warp.mv1";
static const char ORI_MODEL_PATH[] = "data/model/gimmick/ori.mv1";
static const char BUTTON_MODEL_PATH[] = "data/model/gimmick/button.mv1";
static const char TREASURE_MODEL_PATH[] = "data/model/gimmick/treasure.mv1";
static const char GOAL_MODEL_PATH[] = "data/model/gimmick/goal.mv1";

//	マップごとのギミックの配置保存場所
static const char Csv_Warp[][255] =
{ 
	{""} ,//map0は存在しない
	{"data/csv/Map01/Warp.csv" } ,
	{"data/csv/Map02/Warp.csv" } ,
	{"data/csv/Map03/Warp.csv" } ,
};

static const char Csv_Ori[][255] =
{
	{""} ,//map0は存在しない
	{"data/csv/Map01/Ori.csv" } ,
	{"data/csv/Map02/Ori.csv" } ,
	{"data/csv/Map03/Ori.csv"} ,
};

static const char Csv_TreGoal[][255] =
{
	{""} ,//map0は存在しない
	{"data/csv/Map01/TreGoal.csv" } ,
	{"data/csv/Map02/TreGoal.csv" } ,
	{"data/csv/Map03/TreGoal.csv" } ,
};




//コンストラクタ
GimmickManager::GimmickManager()
{
}


//初期化
void GimmickManager::Init()
{
	for (int i = 0; i < GIMMICK_MAX_NUM; i++)
	{
		//
		m_Warp[i].SetID(i);
		m_Warp[i].Init();
		//
		m_Ori[i].SetID(i);
		m_Ori[i].Init();
		//
		m_Tre[i].SetID(i);
		m_Tre[i].Init();
		//
	}
}

//ロード
void GimmickManager::Load(int mapID)
{
	//ワープ
	LoadWarp(mapID);
	//檻
	LoadOri(mapID);
	//
	LoadTre_Goal(mapID);
}

//ループ
void GimmickManager::Step(Player& player)
{
	//
	for (auto A : m_Warp_List)
	{
		A->Step(player);
	}
	//
	for (auto A : m_Ori_List)
	{
		A->Step(player);
	}
	//
	for (auto A : m_Tre_Goal_List)
	{
		A->Step(player);
	}
}

//描画
void GimmickManager::Draw()
{
	//
	for (auto A : m_Warp_List)
	{
		A->Draw();
	}
	//
	for (auto A : m_Ori_List)
	{
		A->Draw();
	}
	//
	for (auto A : m_Tre_Goal_List)
	{
		A->Draw();
	}
}

//終了
void GimmickManager::Exit()
{
	//
	for (auto A : m_Warp_List)
	{
		A->Exit();

		delete A; // メモリ解放
	}
	//
	for (auto A : m_Ori_List)
	{
		A->Exit();

		delete A; // メモリ解放
	}
	//
	for (auto A : m_Tre_Goal_List)
	{
		A->Exit();

		delete A; // メモリ解放
	}


	m_Warp_List.clear(); // リストを空にする
	m_Ori_List.clear(); // リストを空にする
	m_Tre_Goal_List.clear();

	m_InfoList.clear();  // 座標情報も消す
}


//敵をリクエスト
void GimmickManager::Request(VECTOR P_pos)
{
	//
	for (auto A : m_Warp_List)
	{
		A->Request(P_pos);
	}
	//
	for (auto A : m_Ori_List)
	{
		A->Request(P_pos);
	}
	//
	for (auto A : m_Tre_Goal_List)
	{
		A->Request(P_pos);
	}
}

//----------------------
//	更新
//----------------------
void GimmickManager::Update()
{
	//
	for (auto A : m_Warp_List)
	{
		A->Update();
	}
	//
	for (auto A : m_Ori_List)
	{
		A->Update();
	}
	//
	for (auto A : m_Tre_Goal_List)
	{
		A->Update();
	}
}



void GimmickManager::LoadWarp(int mapID)
{
	int Ahndl = MV1LoadModel(WAEP_MODEL_PATH);
	int Bhndl = MV1LoadModel(WAEP_MODEL_PATH);

	int PosHndl = FileRead_open(Csv_Warp[mapID]);


	FILE* FilePointer;
	if (fopen_s(&FilePointer, Csv_Warp[mapID], "r") != 0)return;
	ReadPosData tmp = { 0 };

	while (true)
	{
		int axp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_X);
		int ayp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_Y);
		int azp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_Z);

		int bxp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_X);
		int byp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_Y);
		int bzp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_Z);

		// どれか失敗したら終了
		if (axp == -1 || ayp == -1 || azp == -1 ||
			bxp == -1 || byp == -1 || bzp == -1)
		{
			break;
		}

		Warp* tEmp = new Warp();

		tEmp->SetPositionA(
			VGet(tmp.m_PosA_X, tmp.m_PosA_Y, tmp.m_PosA_Z)
		);

		tEmp->SetPositionB(
			VGet(tmp.m_PosB_X, tmp.m_PosB_Y, tmp.m_PosB_Z)
		);

		m_Warp_List.push_back(tEmp);

		tEmp->Load(Ahndl, Bhndl);

		m_InfoList.push_back(tmp);
	}
	fclose(FilePointer);

	MV1DeleteModel(Ahndl);
	MV1DeleteModel(Bhndl);
}



void GimmickManager::LoadOri(int mapID)
{
	int Ahndl = MV1LoadModel(ORI_MODEL_PATH);
	int Bhndl = MV1LoadModel(BUTTON_MODEL_PATH);

	int PosHndl = FileRead_open(Csv_Ori[mapID]);

	FILE* FilePointer;
	if (fopen_s(&FilePointer, Csv_Ori[mapID], "r") != 0)return;
	ReadPosData tmp = { 0 };

	while (true)
	{
		int axp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_X);
		int ayp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_Y);
		int azp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_Z);

		int bxp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_X);
		int byp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_Y);
		int bzp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_Z);

		int axr = FileRead_scanf(PosHndl, "%f,", &tmp.m_RotA_Y);

		// どれか失敗したら終了
		if (axp == -1 || ayp == -1 || azp == -1 ||
			bxp == -1 || byp == -1 || bzp == -1 ||
			axr == -1)
		{
			break;
		}

		Ori* tEmp = new Ori();

		tEmp->SetPositionA(
			VGet(tmp.m_PosA_X, tmp.m_PosA_Y, tmp.m_PosA_Z)
		);

		tEmp->SetPositionB(
			VGet(tmp.m_PosB_X, tmp.m_PosB_Y, tmp.m_PosB_Z)
		);

		tEmp->SetRotationA(
			tmp.m_RotA_Y
		);

		tEmp->GetInitPosA(
			VGet(tmp.m_PosA_X, tmp.m_PosA_Y, tmp.m_PosA_Z)
		);

		m_Ori_List.push_back(tEmp);

		tEmp->Load(Ahndl, Bhndl);

		m_InfoList.push_back(tmp);
	}
	fclose(FilePointer);

	MV1DeleteModel(Ahndl);
	MV1DeleteModel(Bhndl);
}




void GimmickManager::LoadTre_Goal(int mapID)
{
	int Ahndl = MV1LoadModel(TREASURE_MODEL_PATH);
	int Bhndl = MV1LoadModel(GOAL_MODEL_PATH);

	int PosHndl = FileRead_open(Csv_TreGoal[mapID]);

	FILE* FilePointer;
	if (fopen_s(&FilePointer, Csv_TreGoal[mapID], "r") != 0)return;
	ReadPosData tmp = { 0 };

	while (true)
	{
		int axp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_X);
		int ayp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_Y);
		int azp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosA_Z);

		int bxp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_X);
		int byp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_Y);
		int bzp = FileRead_scanf(PosHndl, "%f,", &tmp.m_PosB_Z);

		int axr = FileRead_scanf(PosHndl, "%f,", &tmp.m_RotA_Y);

		// どれか失敗したら終了
		if (axp == -1 || ayp == -1 || azp == -1 ||
			bxp == -1 || byp == -1 || bzp == -1 ||
			axr == -1)
		{
			break;
		}

		TreasureGoal* tEmp = new TreasureGoal();

		tEmp->SetPositionA(
			VGet(tmp.m_PosA_X, tmp.m_PosA_Y, tmp.m_PosA_Z)
		);

		tEmp->SetPositionB(
			VGet(tmp.m_PosB_X, tmp.m_PosB_Y, tmp.m_PosB_Z)
		);

		tEmp->SetRotationA(
			tmp.m_RotA_Y
		);


		m_Tre_Goal_List.push_back(tEmp);

		tEmp->Load(Ahndl, Bhndl);

		m_InfoList.push_back(tmp);
	}
	fclose(FilePointer);

	MV1DeleteModel(Ahndl);
	MV1DeleteModel(Bhndl);
}