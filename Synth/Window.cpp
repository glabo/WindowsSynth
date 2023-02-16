#include "Window.h"
#include <string>
#include <iostream>


Window::Window()
	: m_hInstance(GetModuleHandle(nullptr))
{
	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = HandleMsgSetup;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Synth",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		this
	);

	ShowWindow(m_hWnd, SW_SHOW);

	// Get audio devices and set up audio
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();
	WaveOut = new olcNoiseMaker<short>(devices[0], &synthModule, SAMPLE_RATE, 1, 16, 128);
	// set noise generation callback
	WaveOut->SetUserFunction(synthModule.generateSoundCallback);

}

Window::~Window()
{
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg); // this calls the window procedure
	}

	return true;
}

// Fancy stuff so that we can have window proc as a member function of window
LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE) {
		// get window class ptr from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal handler
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, uMsg, wParam, lParam);
	}
	// use default handler if we get another msg first
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, uMsg, wParam, lParam);
}


LRESULT Window::HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool updateWindow = false;
	unsigned char keycode;
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		rect.left = 100;
		rect.top = 100;
		rect.right = rect.left + 500;
		rect.bottom = rect.top + 500;

		DrawTextA(hdc, keyboardInputText.GetText().c_str(), strlen(keyboardInputText.GetText().c_str()), &rect, DT_LEFT);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_ERASEBKGND:
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		// color it dark gray
		SetBkColor((HDC)wParam, BGCOLOR); // grey-brown ish
		ExtTextOut((HDC)wParam, 0, 0, ETO_OPAQUE, &rc, 0, 0, 0);
		return 1;
	}

		/*********** Keyboard Messages *************/
	case WM_KEYDOWN:
		synthModule.TriggerNote(wParam);
		keyboardInputText.SetText(synthModule.PrintCurrentNote());
		updateWindow = true;
		break;
	case WM_KEYUP:
		synthModule.ReleaseNote(wParam);
		keyboardInputText.SetText(synthModule.PrintCurrentNote());
		updateWindow = true;
		break;
	case WM_CHAR:
		//kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
	}
	if (updateWindow) {
		InvalidateRect(hWnd, NULL, false);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}