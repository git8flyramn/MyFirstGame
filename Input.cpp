#include "Input.h"
#include <DirectXMath.h>

using namespace DirectX;
namespace Input
{
    //キーボードインプット
    LPDIRECTINPUT8 pDInput = nullptr;
    LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
    BYTE keyState[256] = { 0 };
    BYTE prevKeyState[256] = { 0 };

    //マウスインプット
    LPDIRECTINPUTDEVICE pMouseDevice = nullptr;
    DIMOUSESTATE mouseState; //マウスの状態
    DIMOUSESTATE prevMouseState;//前回のマウスの状態
    XMVECTOR mouseposition;
}
    void Input::Initialize(HWND hWnd)
    {
        DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
        pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
        pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
        pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
       
    }

    void Input::Update()
    {
        memcpy(prevKeyState, keyState, sizeof(keyState));
        for (auto i = 0; i < 256; i++)
        {
            prevKeyState[i] = keyState[i];
        }
        pKeyDevice->Acquire();
        pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
    }

    bool Input::IsKey(int keyCode)
    {
        if (keyState[keyCode] & 0x80)
        {
            return true;
        }
        return false;
    }

   

    bool Input::IsKeyUp(int keyCode)
    {
        //今は離していて、前回は押している
        if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
        {
            return true;
        }
        return false;
    }

    bool Input::IsKeyDown(int keyCode)
    {
        //今は押していて,前回は押していない
        if (IsKey(keyCode) &&  !(prevKeyState[keyCode] & 0x80) )
        {
            return true;
        }
        return false;
    }

    XMVECTOR Input::GetMousePosition()
    {
        return mouseposition;
    }

    void Input::SetMousePosition(int x, int y)
    {
        //mouseposition = XMVectorSet((float)x, (float)y, 0, 0);
        mouseposition = { (float)x,(float)y,0.0f,1.0f };
    }

    void Input::Release()
    {
        SAFE_RELESE(pDInput);
    }