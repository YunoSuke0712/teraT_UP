#pragma once

#include "../Input/input.h"
#include "MessageText.h"

class MessageManager
{
private:

    CInput m_input;

    MessageText m_Text;

    int text[3];
    int text_ID;
    bool text_EV;

public:

    MessageManager();

    void Init();
    void Load();
    void Step();
    void Draw();
    void Exit();

    void SetText(int id);
};