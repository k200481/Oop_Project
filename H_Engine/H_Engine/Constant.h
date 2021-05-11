#ifndef CONSTANTS_H 
#define CONSTANTS_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include<d3d9.h>
const int KEYS_ARRAY_LEN = 256;
const UCHAR KEYS_DOWN = 1;
const UCHAR KEYS_PRESSED = 2;
const UCHAR MOUSE = 4;
const UCHAR TEXT_IN = 8;
const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = 1280;
const UINT GAME_HEIGHT = 960;
const double PI = 3.14159;
const float FRAME_RATE = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;
const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR ALT_KEY = VK_MENU;
const UCHAR ENTER_KEY = VK_RETURN;

#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define COLOR_ARGB DWORD
namespace graphicsNS {
    const COLOR_ARGB ORANGE = D3DCOLOR_ARGB(255, 255, 165, 0);
    const COLOR_ARGB BROWN = D3DCOLOR_ARGB(255, 139, 69, 19);
    const COLOR_ARGB LTGRAY = D3DCOLOR_ARGB(255, 192, 192, 192);
    const COLOR_ARGB GRAY = D3DCOLOR_ARGB(255, 128, 128, 128);
    const COLOR_ARGB OLIVE = D3DCOLOR_ARGB(255, 128, 128, 0);
    const COLOR_ARGB PURPLE = D3DCOLOR_ARGB(255, 128, 0, 128);
    const COLOR_ARGB MAROON = D3DCOLOR_ARGB(255, 128, 0, 0);
    const COLOR_ARGB TEAL = D3DCOLOR_ARGB(255, 0, 128, 128);
    const COLOR_ARGB GREEN = D3DCOLOR_ARGB(255, 0, 128, 0);
    const COLOR_ARGB NAVY = D3DCOLOR_ARGB(255, 0, 0, 128);
    const COLOR_ARGB WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
    const COLOR_ARGB YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0);
    const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255, 255, 0, 255);
    const COLOR_ARGB RED = D3DCOLOR_ARGB(255, 255, 0, 0);
    const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
    const COLOR_ARGB LIME = D3DCOLOR_ARGB(255, 0, 255, 0);
    const COLOR_ARGB BLUE = D3DCOLOR_ARGB(255, 0, 0, 255);
    const COLOR_ARGB BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);
    const COLOR_ARGB FILTER = D3DCOLOR_ARGB(0, 0, 0, 0);
    const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255);
    const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128, 255, 255, 255);
    const COLOR_ARGB BACK_COLOR = NAVY;

    enum DISPLAY_MODE { TOGGLE, FULLSCREEN, WINDOW };
}
namespace inputNS {
    const int KEYS_ARRAY_LEN = 256;
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
    const UCHAR MOUSE = 4;
    const UCHAR TEXT_IN = 8;
    const UCHAR KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
};
#endif

