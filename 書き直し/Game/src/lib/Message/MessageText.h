#pragma once

#include <DxLib.h>
#include <vector>

using namespace std;

class MessageText
{
private:

    struct MessageTextData
    {
        int m_size;
        int m_ColorR;
        int m_ColorG;
        int m_ColorB;

        char Message[256];
    };

    vector<MessageTextData> m_InfoList;

public:

    MessageText();

    void Load();
    void Draw(int id);
};