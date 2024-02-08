//À¿¡¿–¿“Œ–Õ¿ﬂ

#include "windows.h"
#include "tchar.h"

using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WCHAR className[] = L"WINDOW";
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.cbClsExtra = 0;

	wndClass.cbWndExtra = 0;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;

	wndClass.lpfnWndProc = WindowProc;

	if (!RegisterClassEx(&wndClass))
		return 0;

	HWND hWnd = CreateWindowEx(
		0,
		className,
		L"WINDOW",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);
	return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int WIDTH = 400;
	const int HEIGHT = 500;
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			MoveWindow(hwnd, 0, 0, WIDTH, HEIGHT, true);
			SetTimer(hwnd, 1, 10, NULL);
		}
		else if (wParam == VK_ESCAPE)
			KillTimer(hwnd, 1);
		break;
	case WM_TIMER:
		RECT rectangle;
		GetWindowRect(hwnd, &rectangle);
		MoveWindow(hwnd, rectangle.left + 3, rectangle.top + 5, WIDTH, HEIGHT, true);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
    return 0;
}