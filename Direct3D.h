#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <assert.h>
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
//リンカ

#pragma comment (lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
namespace Direct3D
{
	//externはどこかに実際の定義(宣言)文あるぞっていう宣言
	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
	//シェーダー準備
	HRESULT InitShader();
	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
};
