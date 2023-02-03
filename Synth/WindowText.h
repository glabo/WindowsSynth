#pragma once
#include <string>

class WindowText
{
public:
	WindowText();
	WindowText(std::string str);
	~WindowText() = default;

	void SetText(std::string newText);
	void SetText(std::string newText, char appendChar);
	std::string GetText();
	
private:
	std::string text;
};

