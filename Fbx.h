#pragma once
#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"
#include <vector>
#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(FbxNode* pNode);
private:

	struct MATERIAL
	{
		Texture* pTexture;
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	//�{����XMFLOAT�`�ł���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};

	ID3D11Buffer *pVertexBuffer_; //���_�o�b�t�@
	ID3D11Buffer **pIndexBuffer_;  //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer *pConstantBuffer_;//�R���X�^���g�o�b�t�@
	std::vector<MATERIAL> materialList_;

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;


};

