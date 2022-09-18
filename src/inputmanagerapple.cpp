#include "inputmanagerapple.h"

namespace med {
#ifdef __APPLE__
//CGEventRef hook_event_proc(CGEventTapProxy tap_proxy, CGEventType type, CGEventRef event_ref, void *refcon) {
//    std::cout<<"hook_event_proc"<<type<<std::endl;
//    return event_ref;
//}
//
//static void hook_status_proc(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info) {
//    std::cout<<"hook_status_proc"<<activity<<std::endl;
//}
#endif

void InputManagerApple::start() {
#ifdef __APPLE__
//    typedef struct _hook_info {
//         CFMachPortRef port;
//         CFRunLoopSourceRef source;
//         CFRunLoopObserverRef observer;
//     } hook_info;
//    hook_info *hook = new hook_info;
//    CGEventMask event_mask = CGEventMaskBit(kCGEventKeyDown) |
//                CGEventMaskBit(kCGEventKeyUp) |
//                CGEventMaskBit(kCGEventFlagsChanged) |
//                CGEventMaskBit(kCGEventLeftMouseDown) |
//                CGEventMaskBit(kCGEventLeftMouseUp) |
//                CGEventMaskBit(kCGEventLeftMouseDragged) |
//                CGEventMaskBit(kCGEventRightMouseDown) |
//                CGEventMaskBit(kCGEventRightMouseUp) |
//                CGEventMaskBit(kCGEventRightMouseDragged) |
//                CGEventMaskBit(kCGEventOtherMouseDown) |
//                CGEventMaskBit(kCGEventOtherMouseUp) |
//                CGEventMaskBit(kCGEventOtherMouseDragged) |
//                CGEventMaskBit(kCGEventMouseMoved) |
//                CGEventMaskBit(kCGEventScrollWheel) |
//                CGEventMaskBit(NX_SYSDEFINED);
//
//    hook->port = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault, event_mask, hook_event_proc, NULL);
//    hook->source = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, hook->port, 0);
//    hook->observer = CFRunLoopObserverCreate(kCFAllocatorDefault, kCFRunLoopEntry | kCFRunLoopExit, true, 0, hook_status_proc, NULL);
//    CFRunLoopRef event_loop = CFRunLoopGetCurrent();
//    CFRunLoopAddSource(event_loop, hook->source, kCFRunLoopDefaultMode);
//    CFRunLoopAddObserver(event_loop, hook->observer, kCFRunLoopDefaultMode);
#endif
}


}
