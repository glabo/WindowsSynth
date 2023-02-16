#pragma once

#include <Windows.h>
#include "Keyboard.h"
#include "WindowText.h"
#include "NoteEventGenerator.h"
#include "Oscillator.h"
#include "olcNoiseMaker.h"
#include "AudioConstants.h"
#include "SynthModule.h"
#include "Mouse.h"


class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	unsigned long BGCOLOR = 0x001D2229;
	unsigned long HILITECOLOR = 0x00006EF3;

	const wchar_t* CLASS_NAME = L"Synth Window Class";
	// application instance
	HINSTANCE m_hInstance;
	// window instance
	HWND m_hWnd;
	Mouse mouse;

	WindowText keyboardInputText;
	SynthModule synthModule;

	// soundwave output driver
	olcNoiseMaker<short>* WaveOut;
};

