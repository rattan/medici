#include "inputhandler.h"

#ifdef _WIN32
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg == WM_INPUT)
    {
        HRAWINPUT hRawInput = (HRAWINPUT)lParam;
        RAWINPUT input = { 0 };
        UINT size = sizeof(input);
        GetRawInputData(hRawInput, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER));
        switch (input.header.dwType) {
        case RIM_TYPEKEYBOARD:
            std::cout << input.data.keyboard.VKey << " " << input.data.keyboard.Flags << std::endl;
            break;
        case RIM_TYPEMOUSE:
            std::cout << input.data.mouse.lLastX << " " << input.data.mouse.lLastY << " " << input.data.mouse.ulButtons << std::endl;
            break;
        }
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
#endif

InputHandler::InputHandler() {
#ifdef _WIN32
    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = &MyWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = TEXT("Sample");
    if (!RegisterClassEx(&wc)) {
        std::cerr << "RegisterClassEx fail" << std::endl;
    }
    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);
    if (!hwnd) {
        std::cerr << "CreateWindowEx fail" << std::endl;
    }

    RAWINPUTDEVICE inputDevice[2] = {};
    inputDevice[0].usUsagePage = 0x01;
    inputDevice[0].usUsage = 0x02;
    inputDevice[0].dwFlags = RIDEV_INPUTSINK;
    inputDevice[0].hwndTarget = hwnd;
    inputDevice[1].usUsagePage = 0x01;
    inputDevice[1].usUsage = 0x06;
    inputDevice[1].dwFlags = RIDEV_INPUTSINK;
    inputDevice[1].hwndTarget = hwnd;
    if (RegisterRawInputDevices(inputDevice, 2, sizeof(RAWINPUTDEVICE)) == FALSE) {
        std::cerr << "RegisterRawInputDevices fail" << std::endl;
    }

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif
}