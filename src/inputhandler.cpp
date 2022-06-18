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

#ifdef __APPLE__
CGEventRef hook_event_proc(CGEventTapProxy tap_proxy, CGEventType type, CGEventRef event_ref, void *refcon) {
    std::cout<<"hook_event_proc"<<type<<std::endl;
    return event_ref;
}

static void hook_status_proc(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info) {
    std::cout<<"hook_status_proc"<<activity<<std::endl;
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
    
#ifdef __APPLE__
    typedef struct _hook_info {
         CFMachPortRef port;
         CFRunLoopSourceRef source;
         CFRunLoopObserverRef observer;
     } hook_info;
    hook_info *hook = new hook_info;
    CGEventMask event_mask = CGEventMaskBit(kCGEventKeyDown) |
                CGEventMaskBit(kCGEventKeyUp) |
                CGEventMaskBit(kCGEventFlagsChanged) |
                CGEventMaskBit(kCGEventLeftMouseDown) |
                CGEventMaskBit(kCGEventLeftMouseUp) |
                CGEventMaskBit(kCGEventLeftMouseDragged) |
                CGEventMaskBit(kCGEventRightMouseDown) |
                CGEventMaskBit(kCGEventRightMouseUp) |
                CGEventMaskBit(kCGEventRightMouseDragged) |
                CGEventMaskBit(kCGEventOtherMouseDown) |
                CGEventMaskBit(kCGEventOtherMouseUp) |
                CGEventMaskBit(kCGEventOtherMouseDragged) |
                CGEventMaskBit(kCGEventMouseMoved) |
                CGEventMaskBit(kCGEventScrollWheel) |
                CGEventMaskBit(NX_SYSDEFINED);
    
    hook->port = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault, event_mask, hook_event_proc, NULL);
    hook->source = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, hook->port, 0);
    hook->observer = CFRunLoopObserverCreate(kCFAllocatorDefault, kCFRunLoopEntry | kCFRunLoopExit, true, 0, hook_status_proc, NULL);
    CFRunLoopRef event_loop = CFRunLoopGetCurrent();
    CFRunLoopAddSource(event_loop, hook->source, kCFRunLoopDefaultMode);
    CFRunLoopAddObserver(event_loop, hook->observer, kCFRunLoopDefaultMode);
#endif
    
}
