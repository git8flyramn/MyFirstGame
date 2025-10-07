#pragma once
#include "Quad.h"
class Dice :
    public Quad
{
   public:
       Dice();
       ~Dice();
	   HRESULT Initialize()override;
	   void Draw(DirectX::XMMATRIX& worldMatrix)override;
	   void Release();
	  
	
	 
//private:
//	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
//	ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
//	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
//	Texture* pTexture_;
//	float rotaionAngele = 0.0f;
//	XMVECTOR roationAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//	XMMATRIX rotationMatrix;
};

