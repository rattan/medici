#include "inputmanagerwindows.h"

namespace med {

const std::string InputManagerWindows::TAG = "InputManagerW";

void InputManagerWindows::start() {
#ifdef _WIN32
    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = TEXT("Sample");
    if (!RegisterClassEx(&wc)) {
        Log::e(TAG, "RegisterClassEx fail");
    }
    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);
    if (!hwnd) {
        Log::e(TAG, "CreateWindowEx fail");
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
        Log::e(TAG, "RegisterRawInputDevices fail");
    }

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_INPUT)
        {
            HRAWINPUT hRawInput = (HRAWINPUT)msg.lParam;
            RAWINPUT input = { 0 };
            UINT size = sizeof(input);
            GetRawInputData(hRawInput, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER));
            switch (input.header.dwType) {
            case RIM_TYPEKEYBOARD:
                sendKeyEvent(KeyboardEvent(input.data.keyboard.VKey, input.data.keyboard.Flags));
                //std::cout << input.data.keyboard.VKey << " " << input.data.keyboard.Flags << std::endl;
                break;
            case RIM_TYPEMOUSE:
                sendMouseEvent(MouseEvent(Point(input.data.mouse.lLastY, input.data.mouse.lLastX), input.data.mouse.ulButtons));
                //std::cout << input.data.mouse.lLastX << " " << input.data.mouse.lLastY << " " << input.data.mouse.ulButtons << std::endl;
                break;
            }
        }
    }
#endif
}

void InputManagerWindows::stop() {

}

}
