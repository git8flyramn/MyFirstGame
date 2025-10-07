#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
using namespace DirectX;
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWVP; //world*view*projection�̍s��
	DirectX::XMMATRIX matNomal; //�@���ϊ��p�̍s��
	DirectX::XMMATRIX matWorld; //���[���h�s��
};

//���_���
struct VERTEX
{
	XMFLOAT4 pos;
	XMFLOAT2 uv;
	XMFLOAT4 normal;
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
