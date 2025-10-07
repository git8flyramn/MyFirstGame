#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

//namespace �O���[�o���̕ϐ��ۂ��g��
using namespace DirectX;
struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWorld; //���[���h�s��
};

//���_���
struct VERTEX
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
	void Draw(DirectX::XMMATRIX& worldMatrix);
	void Release();
protected:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
	Texture* pTexture_;

};