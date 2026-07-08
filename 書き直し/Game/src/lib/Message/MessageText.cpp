#include "MessageText.h"

#include <DxLib.h>
#include <string.h>

static const char TextCsvAddress[][200] =
{
    {""},
    {"data/csv/TextCsv/Text_01.csv"},
};

static const int TEXT_ALL_X = 320;
static const int TEXT_T_Y = 768;

MessageText::MessageText()
{

}

void MessageText::Load()
{
    m_InfoList.clear();

    int Open = FileRead_open(TextCsvAddress[1]);

    if (Open == 0)
    {
        printfDx("Open Error\n");
        return;
    }

    FILE* FilePointer;

    if (fopen_s(&FilePointer, TextCsvAddress[1], "r") != 0)
        return;

    while (true)
    {
        MessageTextData tmp = {};

        int size = FileRead_scanf(Open, "%d,", &tmp.m_size);
        int colR = FileRead_scanf(Open, "%d,", &tmp.m_ColorR);
        int colG = FileRead_scanf(Open, "%d,", &tmp.m_ColorG);
        int colB = FileRead_scanf(Open, "%d,", &tmp.m_ColorB);
        int text = FileRead_gets(tmp.Message, sizeof(tmp.Message), Open);

        if (size == -1 || colR == -1 || colG == -1 || colB == -1 || text == -1)
        {
            break;
        }

        m_InfoList.push_back(tmp);
    }

    fclose(FilePointer);
    FileRead_close(Open);
}

void MessageText::Draw(int id)
{
    if (id < 0)
        return;

    if (id >= m_InfoList.size())
        return;

    SetFontSize(m_InfoList[id].m_size);

    DrawString(
        TEXT_ALL_X,
        TEXT_T_Y,
        m_InfoList[id].Message,
        GetColor(
            m_InfoList[id].m_ColorR,
            m_InfoList[id].m_ColorG,
            m_InfoList[id].m_ColorB));
}