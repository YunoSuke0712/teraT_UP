#include"SoundManager.h"

//staticメンバ変数はここで書く作業が必要
vector<int>SoundManager::m_hndl;

//----------------------
// 初期化
//----------------------
void SoundManager::Init()
{
	//中身の空にする
	m_hndl.clear();

}


//--------------------------
// モデルデータのロード
//--------------------------
void SoundManager::Load()
{
	const char* filePath[SOUND_NUM] = { "Data/Sound/bgm00.mp3","Data/Sound/se_plshot.mp3","Data/Sound/se_explore.mp3" };
	for (int i = 0; i < SOUND_NUM; i++) {
		int hndl = LoadSoundMem(filePath[i]);
		m_hndl.push_back(hndl);
	}

}

//----------------------------
//  終了時のデータ破棄など
//----------------------------
void SoundManager::Exit()
{
	for (int i = 0; i < m_hndl.size(); i++) {
		if (m_hndl[i] != -1)
		{
			DeleteSoundMem(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}



//----------------------------
//  音楽再生
//----------------------------
bool SoundManager::Play(tagID id, int type, bool isStart)
{
	//if (IsPlay(id)) return false;

	int ret = PlaySoundMem(m_hndl[id], type, isStart);
	if (ret == -1) return false;
	else return true;
}


//----------------------------
//  音楽ストップ
//----------------------------
void SoundManager::Stop(tagID id)
{
	StopSoundMem(m_hndl[id]);
}

//----------------------------
//  全音楽ストップ
//----------------------------
void SoundManager::AllStop()
{
	for (int i = 0; i < m_hndl.size(); i++)
	{
		StopSoundMem(m_hndl[i]);
	}
}


//----------------------------
//  音楽を再生中か
//----------------------------
bool SoundManager::IsPlay(tagID id)
{


	//int result = CheckSoundMem(m_hndl[id]);
	//if (result == 1) return true;
	//else return false;
	//↓
	return CheckSoundMem(m_hndl[id]) == 1 ? true : false;
}


