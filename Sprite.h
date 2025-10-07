#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
using namespace DirectX;
struct CONSTANT_BUFFER_
{
	DirectX::XMMATRIX matWorld; //�@���ϊ��p�̍s��
};

//���_���
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
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�萔�o�b�t�@
	Texture* pTexture_;

};