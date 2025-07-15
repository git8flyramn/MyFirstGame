#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Texture.h"
using namespace DirectX;
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP; //world*view*projectionの行列
	DirectX::XMMATRIX matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR pos;
	XMVECTOR uv;
	XMVECTOR nomal;
};

class Texture;
class Quad
{
public:
	Quad();
	virtual ~Quad();
	virtual HRESULT Initialize();
	void Draw(DirectX::XMMATRIX& worldMatrix);
	void Release();
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//定数バッファ
	Texture* pTexture_;

};
