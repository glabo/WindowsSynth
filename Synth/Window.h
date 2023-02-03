#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();
	
private:
	const wchar_t* CLASS_NAME = L"Synth Window Class";
	// application instance
	HINSTANCE m_hInstance;
	// window instance
	HWND m_hWnd;
};

