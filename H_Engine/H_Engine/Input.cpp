#include "input.h"
Input::Input()
{
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
    newLine = true;
    textIn = ""; 
    charIn = 0;
    mouseX = 0;  
    mouseY = 0;   
    mouseRawX = 0; 
    mouseRawY = 0;  
    mouseLButton = false; 
    mouseRButton = false;  
}Input::~Input()
{
    if(mouseCaptured)
        ReleaseCapture();           
}
void Input::initialize(HWND hwnd, bool capture)
{
    try{
        mouseCaptured = capture;
        Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
        Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
        Rid[0].dwFlags = RIDEV_INPUTSINK;   
        Rid[0].hwndTarget = hwnd;
        RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

        if(mouseCaptured)
            SetCapture(hwnd); 
    }
    catch(...)
    {
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
    }
}void Input::keyDown(WPARAM wParam)
{
    if (wParam < inputNS::KEYS_ARRAY_LEN)
    {
        keysDown[wParam] = true; 
        keysPressed[wParam] = true;
    }
}

void Input::keyUp(WPARAM wParam)
{
    if (wParam < inputNS::KEYS_ARRAY_LEN)
        keysDown[wParam] = false;
}
void Input::keyIn(WPARAM wParam)
{
    if (newLine){
        textIn.clear();
        newLine = false;
    }

    if (wParam == '\b'){
        if(textIn.length() > 0) 
            textIn.erase(textIn.size()-1);
    }
    else{
        textIn += wParam;               
        charIn = wParam;                
    }

    if ((char)wParam == '\r')     
        newLine = true;   
}
bool Input::isKeyDown(UCHAR vkey) const
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysDown[vkey];
    else
        return false;
}
bool Input::wasKeyPressed(UCHAR vkey) const
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysPressed[vkey];
    else
        return false;
}
bool Input::anyKeyPressed() const
{
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        if(keysPressed[i] == true)
            return true;
    return false;
}
void Input::clearKeyPress(UCHAR vkey)
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        keysPressed[vkey] = false;
}
void Input::clear(UCHAR what)
{
    if(what & inputNS::KEYS_DOWN)  {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysDown[i] = false;
    }
    if(what & inputNS::KEYS_PRESSED){
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            keysPressed[i] = false;
    }
    if(what & inputNS::MOUSE){
        mouseX = 0;
        mouseY = 0;
        mouseRawX = 0;
        mouseRawY = 0;
    }
    if(what & inputNS::TEXT_IN)
        clearTextIn();
}
void Input::mouseIn(LPARAM lParam)
{
    mouseX = GET_X_LPARAM(lParam); 
    mouseY = GET_Y_LPARAM(lParam);
}
void Input::mouseRawIn(LPARAM lParam)
{
    UINT dwSize = 40;
    static BYTE lpb[40];
    
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
                    lpb, &dwSize, sizeof(RAWINPUTHEADER));
    
    RAWINPUT* raw = (RAWINPUT*)lpb;
    
    if (raw->header.dwType == RIM_TYPEMOUSE) 
    {
        mouseRawX = raw->data.mouse.lLastX;
        mouseRawY = raw->data.mouse.lLastY;
    } 
}
