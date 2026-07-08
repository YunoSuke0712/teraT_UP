#include "MessageManager.h"

MessageManager::MessageManager()
{
    Init();
}

void MessageManager::Init()
{
    text_ID = 0;
    text_EV = false;

    text[0] = 0;
    text[1] = 0;
    text[2] = 0;
}

void MessageManager::Load()
{
    m_Text.Load();
}

void MessageManager::Step()
{
    // 左クリックでテスト表示
    if (m_input.IsInputTrg(KEY_CLICK))
    {
        SetText(3);
    }

    if (text_EV)
    {
        text[2] = text[1];
        text[1] = text[0];
        text[0] = text_ID;

        text_EV = false;
    }
}

void MessageManager::Draw()
{
    m_Text.Draw(text_ID);
}

void MessageManager::Exit()
{

}

void MessageManager::SetText(int id)
{
    text_ID = id;
    text_EV = true;
}