#include "Mouse.h"

void Mouse::OnMouseMove(int x, int y)
{
    xPos = x;
    yPos = y;
}

void Mouse::OnLButtonPress()
{
    LButtonPressed = true;
}

void Mouse::OnRButtonPress()
{
    RButtonPressed = true;
}

void Mouse::OnLButtonRelease()
{
    LButtonPressed = false;
}

void Mouse::OnRButtonRelease()
{
    RButtonPressed = false;
}

bool Mouse::IsLButtonPressed()
{
    return LButtonPressed;
}

bool Mouse::IsRButtonPressed()
{
    return RButtonPressed;
}

int Mouse::GetXPos()
{
    return xPos;
}

int Mouse::GetYPos()
{
    return yPos;
}
