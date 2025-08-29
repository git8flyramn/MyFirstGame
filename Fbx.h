#pragma once
#pragma once
#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
	};

	//本来はXMFLOAT～である
	struct VERTEX
	{
		XMVECTOR position;
	};

	ID3D11Buffer* pVertexBuffer_; //頂点バッファ
	ID3D11Buffer* pIndexBuffer_;  //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void IntConstantBuffer();
};

