#include "Fbx.h"
#include "Direct3D.h"
#include "Camera.h"
#include <filesystem>
namespace fs = std::filesystem;
Fbx::Fbx(): pVertexBuffer_(nullptr),
            pIndexBuffer_(nullptr),
            pConstantBuffer_(nullptr),
            vertexCount_(0),
            polygonCount_(0)
{

}

HRESULT Fbx::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();
	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//現在のカレントディレクトリを覚えておく
	wchar_t defaultCureentDir[MAX_PATH];
	//引数のfileNameからディレクトリ部分を取得
	GetCurrentDirectory(MAX_PATH, defaultCureentDir);
	//カレントディレクトリ変更
	

	//各情報の個数を取得

	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
    polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount(); //マテリアルの数

	InitVertex(mesh);
	InitIndex(mesh);
	IntConstantBuffer();
	InitMaterial(pNode);
	//カレントディレクトリを元に戻る
	SetCurrentDirectory(defaultCureentDir);
	
	//マネージャ解放
	pFbxManager->Destroy();
	
	return S_OK;
}

void Fbx::InitVertex(FbxMesh* mesh)
{
	VERTEX* vertices = new VERTEX[vertexCount_];
	int vertex = 0;
	//全ポリゴンの数だけ繰り返す
	for (long poly = 0; poly < polygonCount_; poly)
	{
		for (vertex; vertex < 3; vertex);
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);
			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)-pos[0], (float)pos[1], (float)pos[2], 0.0f);
		   
			//頂点のUV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);
		}
	}
	HRESULT hr;
	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
	}
}

void Fbx::InitIndex(FbxMesh* mesh)
{
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	int* index = new int[polygonCount_ * 3];

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;

		for (long poly = 0; poly < polygonCount_; poly)
		{
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);
			if (mtlId == i)
			{
				for (long vertex = 0; vertex < 3; vertex++)
				{
					index[count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}

		}
		// コンスタントバッファの作成
		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		//コンスタントバッファの作成
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr;
		hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
	}
}

void Fbx::IntConstantBuffer()
{
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	HRESULT hr;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL,L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
	}
  

	////コンスタントバッファ
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(VERTEX);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;
	//Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);


}
void Fbx::InitMaterial(FbxNode* pNode)
{

	
	//materialCountの数だけ配列を準備する
	materialList_.resize(materialCount_);
	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount > 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();
			//ファイル名+拡張だけにする
			//char name[_MAX_FNAME];	//ファイル名
			//char ext[_MAX_EXT];	//拡張子
		/*	_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);*/
			fs::path tPath(textureFilePath);
			if (fs::is_regular_file(tPath))
			{
				//int a = 0;
				//a++;
					//ここでテクスチャの読み込み
				materialList_[i].pTexture = new Texture();
				materialList_[i].pTexture->Load(textureFilePath);
			}
			else
			{
				//テクスチャファイルがない時の処理
				//materialList_[i].pTexture = nullptr;
			}
		}
		//テクスチャ無し
		else
		{
			//テクスチャ無しの時の処理
			materialList_[i].pTexture = nullptr;
		}
	}
}
void Fbx::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_3D);
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	transform.Calculation();
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixIdentity();


	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(polygonCount_ * 3, 0, 0);

}

void Fbx::Release()
{
	/*SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pConstantBuffer_);*/
}