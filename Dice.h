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
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
	Texture* pTexture_;
};

