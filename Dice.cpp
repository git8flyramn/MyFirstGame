#include "Dice.h"
#include <DirectXMath.h>
#include "Quad.h"
#include <DirectXTex.h>
#include "Texture.h"
#pragma comment(lib, "DirectXTex.lib")
using namespace DirectX;

Dice::Dice()
{
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
	VERTEX vertices[] =
	{
		//{{position},{uv}}
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i����j
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�E��j
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�E���j
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�����j
		{ XMVectorSet(0.0f,0.0f,0.0f,)}
	};

}

void Dice::Draw(DirectX::XMMATRIX& worldMatrix)
{
}

void Dice::Release()
{
}
