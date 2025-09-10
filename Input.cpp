#include "Input.h"
#include "MyFirstGame.h"
namespace Input
{
    LPDIRECTINPUT8 pDInput = nullptr;
    LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
    BYTE keyState[256] = { 0 };

    void Input::Initialize(HWND hWnd)
    {
        //DirectInput8Create(DrvGetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
        pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
        pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
        pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
    }

    void Input::Update()
    {
        pKeyDevice->Acquire();
        pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
    }

    bool Input::IsKey(int keyCode)
    {
        if (keyState[pKeyDevice->GetDeviceState(sizeof(keyState), &keyState)])
        {
            return true;
        }
        return false;
    }

    void Input::Release()
    {
        SAFE_RELESE(pDInput);
    }

}
