#pragma once
class Mouse
{
	friend class Window;
public:
	void OnMouseMove(int x, int y);
	void OnLButtonPress();
	void OnRButtonPress();
	void OnLButtonRelease();
	void OnRButtonRelease();

	bool IsLButtonPressed();
	bool IsRButtonPressed();

	int GetXPos();
	int GetYPos();

private:
	int xPos, yPos;
	bool LButtonPressed, RButtonPressed;
};

