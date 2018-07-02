/* DO NOT EDIT THIS FILE - it is machine generated */
#include "Test.h"

//-----------------------------WinSource-------------------------------

#ifdef _WIN64
#include <windows.h>

bool isActive = false;
DEVMODE* defaultMode = nullptr;


JNIEXPORT void JNICALL Java_Test_change
(JNIEnv *, jobject, jint w, jint h) {


	if (isActive) return;

	if (defaultMode == nullptr) {
		defaultMode = new DEVMODE();
		EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, defaultMode);
	}

	DEVMODE dm;
	EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm);
	dm.dmPelsWidth = w;
	dm.dmPelsHeight = h;
	isActive = ChangeDisplaySettings(&dm, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;

}

JNIEXPORT void JNICALL Java_Test_end
(JNIEnv *, jobject) {
	if (!isActive) return;
	isActive = ChangeDisplaySettings(defaultMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL;
}

#endif // !_WIN64

//-----------------------------MacSource-------------------------------

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>

bool isActive = false;
CGDisplayModeRef defaultMode = nullptr;

JNIEXPORT void JNICALL Java_Test_change
(JNIEnv *, jobject, jint w, jint h) {
    
    
    if (isActive) return;
    
    CGDirectDisplayID displayId = CGMainDisplayID();
    if ( defaultMode == nullptr ) defaultMode = CGDisplayCopyDisplayMode(displayId);
    CFArrayRef arr = CGDisplayCopyAllDisplayModes(displayId, NULL);
    CFIndex len = CFArrayGetCount(arr);
    int ref = INT_MAX;
    CGDisplayModeRef target = nullptr;
    for ( int i = 0;i < len;i++ ) {
        CGDisplayModeRef modePtr = (CGDisplayModeRef)(CFArrayGetValueAtIndex(arr, i));
        if ( CGDisplayModeGetWidth(modePtr) == w && CGDisplayModeGetHeight(modePtr) == h && abs(60 - CGDisplayModeGetRefreshRate(modePtr)) < ref ) {
            ref = abs(60 - CGDisplayModeGetRefreshRate(modePtr));
            target =modePtr;
        }
    }
    if ( target != nullptr ) {
        isActive = CGDisplaySetDisplayMode(displayId, target, nullptr) == kCGErrorSuccess;
    }
}

JNIEXPORT void JNICALL Java_Test_end
(JNIEnv *, jobject) {
    if (!isActive) return;
    CGDirectDisplayID displayId = CGMainDisplayID();
    CGDisplaySetDisplayMode(displayId, defaultMode, nullptr);
}
#endif // !__APPLE_

