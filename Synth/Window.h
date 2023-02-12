#pragma once

#include <Windows.h>
#include "Keyboard.h"
#include "WindowText.h"
#include "NoteEventGenerator.h"
#include "Oscillator.h"
#include "olcNoiseMaker.h"
#include "AudioConstants.h"
#include "SynthModule.h"

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
	const wchar_t* CLASS_NAME = L"Synth Window Class";
	// application instance
	HINSTANCE m_hInstance;
	// window instance
	HWND m_hWnd;

	WindowText keyboardInputText;
	SynthModule synthModule;

	// soundwave output driver
	olcNoiseMaker<short>* WaveOut;
};

