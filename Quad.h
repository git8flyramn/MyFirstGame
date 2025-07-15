#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Texture.h"
using namespace DirectX;
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP; //world*view*projection�̍s��
	DirectX::XMMATRIX matW;
};

//���_���
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
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
	Texture* pTexture_;

};
