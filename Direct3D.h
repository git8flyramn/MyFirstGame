#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <assert.h>
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
//リンカ
enum SHADER_TYPE
{
	SHADER_3D,//3d用シェーダ
	SHADER_2D,//2d用シェーダ
	SHADER_MAX //シェーダの最大数
};

#pragma comment (lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
namespace Direct3D
{
	//externはどこかに実際の定義(宣言)文あるぞっていう宣言
	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader3D(); //3D用シェーダー初期化
	HRESULT InitShader2D();//2Dシェーダー初期化

	void SetShader(SHADER_TYPE type); //シェーダをセット
	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
};
