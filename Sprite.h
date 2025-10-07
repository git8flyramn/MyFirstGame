#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
using namespace DirectX;
struct CONSTANT_BUFFER_
{
	DirectX::XMMATRIX matWorld; //法線変換用の行列
};

//頂点情報
struct VERTEX_
{
	XMFLOAT4 pos;
	XMFLOAT2 uv;
};

class Texture;
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();
	virtual HRESULT Initialize();
	virtual void Draw(DirectX::XMMATRIX& worldMatrix);
	void Release();
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//定数バッファ
	Texture* pTexture_;

};