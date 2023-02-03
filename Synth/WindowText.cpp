#include "WindowText.h"

WindowText::WindowText()
{
    text = "";
}

WindowText::WindowText(std::string str)
{
    text = str;
}

void WindowText::SetText(std::string newText)
{
    text = newText;
}

void WindowText::SetText(std::string newText, char appendChar)
{
    text = newText;
    text.append(1, appendChar);
}

std::string WindowText::GetText()
{
    return text;
}
