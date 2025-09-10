#pragma once
#include "Quad.h"
using namespace DirectX;
class Texture;
class Dice :
    public Quad
{
   public:
       Dice();
       ~Dice();
	   HRESULT Initialize() override;
	   void Draw(DirectX::XMMATRIX& worldMatrix);
	   void Release();
	 
private:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//定数バッファ
	Texture* pTexture_;
};

