#pragma once
#pragma once
//#include <d3d11.h>
//#include <fbxsdk.h>
//#include <string>
//#include "Transform.h"
//#include "Texture.h"
//#include <vector>
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

//class Fbx
//{
//public:
//
//	Fbx();
//	HRESULT Load(std::string fileName);
//	void    Draw(Transform& transform);
//	void    Release();
//
//	void InitVertex(FbxMesh* mesh);
//	void InitIndex(FbxMesh* mesh);
//	void IntConstantBuffer();
//	void InitMaterial(FbxNode* pNode);
//private:
//
//	struct MATERIAL
//	{
//		Texture* pTexture;
//		XMFLOAT4 diffuse;
//	};
//	struct CONSTANT_BUFFER
//	{
//		XMMATRIX   matWVP;
//		XMMATRIX   matNormal;
//		XMFLOAT4   diffuse;
//		BOOL     materialFlag; //�}�e���A�������邩�Ȃ���
//	
//
//	};
//
//	//�{����XMFLOAT�`�ł���
//	struct VERTEX
//	{
//		XMVECTOR position;
//		XMVECTOR uv;
//		XMVECTOR normal;
//	};
//
//	ID3D11Buffer *pVertexBuffer_; //���_�o�b�t�@
//	ID3D11Buffer **pIndexBuffer_;  //�C���f�b�N�X�o�b�t�@
//	ID3D11Buffer *pConstantBuffer_;//�R���X�^���g�o�b�t�@
//	std::vector<int> indexCount_;
//	std::vector<MATERIAL> materialList_;
//
//	int vertexCount_;	//���_��
//	int polygonCount_;	//�|���S����
//	int materialCount_; //�}�e���A���̐�
//
//
//};
//
class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;
	};
	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

public:
	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	//���_�o�b�t�@����
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer(fbxsdk::FbxMesh* mesh);
};