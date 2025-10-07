#include "Input.h"
#include <DirectXMath.h>

using namespace DirectX;
namespace Input
{
    //�L�[�{�[�h�C���v�b�g
    LPDIRECTINPUT8 pDInput = nullptr;
    LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
    BYTE keyState[256] = { 0 };
    BYTE prevKeyState[256] = { 0 };

    //�}�E�X�C���v�b�g
    LPDIRECTINPUTDEVICE pMouseDevice = nullptr;
    DIMOUSESTATE mouseState; //�}�E�X�̏��
    DIMOUSESTATE prevMouseState;//�O��̃}�E�X�̏��
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
        //���͗����Ă��āA�O��͉����Ă���
        if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
        {
            return true;
        }
        return false;
    }

    bool Input::IsKeyDown(int keyCode)
    {
        //���͉����Ă���,�O��͉����Ă��Ȃ�
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