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
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�C���|�[�^�[�𐶐�
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();
	//���b�V�������擾
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//���݂̃J�����g�f�B���N�g�����o���Ă���
	wchar_t defaultCureentDir[MAX_PATH];
	//������fileName����f�B���N�g���������擾
	GetCurrentDirectory(MAX_PATH, defaultCureentDir);
	//�J�����g�f�B���N�g���ύX
	

	//�e���̌����擾

	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
    polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount(); //�}�e���A���̐�

	InitVertex(mesh);
	InitIndex(mesh);
	IntConstantBuffer();
	InitMaterial(pNode);
	//�J�����g�f�B���N�g�������ɖ߂�
	SetCurrentDirectory(defaultCureentDir);
	
	//�}�l�[�W�����
	pFbxManager->Destroy();
	
	return S_OK;
}

void Fbx::InitVertex(FbxMesh* mesh)
{
	VERTEX* vertices = new VERTEX[vertexCount_];
	int vertex = 0;
	//�S�|���S���̐������J��Ԃ�
	for (long poly = 0; poly < polygonCount_; poly)
	{
		for (vertex; vertex < 3; vertex);
		{
			//���ׂ钸�_�̔ԍ�
			int index = mesh->GetPolygonVertex(poly, vertex);
			//���_�̈ʒu
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)-pos[0], (float)pos[1], (float)pos[2], 0.0f);
		   
			//���_��UV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);
		}
	}
	HRESULT hr;
	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
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
		MessageBox(NULL, L"���_�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
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
		// �R���X�^���g�o�b�t�@�̍쐬
		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		//�R���X�^���g�o�b�t�@�̍쐬
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
		MessageBox(NULL,L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
	}
  

	////�R���X�^���g�o�b�t�@
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

	
	//materialCount�̐������z�����������
	materialList_.resize(materialCount_);
	for (int i = 0; i < materialCount_; i++)
	{
		//i�Ԗڂ̃}�e���A�������擾
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//�e�N�X�`�����
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//�e�N�X�`���̐���
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//�e�N�X�`������
		if (fileTextureCount > 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();
			//�t�@�C����+�g�������ɂ���
			//char name[_MAX_FNAME];	//�t�@�C����
			//char ext[_MAX_EXT];	//�g���q
		/*	_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);*/
			fs::path tPath(textureFilePath);
			if (fs::is_regular_file(tPath))
			{
				//int a = 0;
				//a++;
					//�����Ńe�N�X�`���̓ǂݍ���
				materialList_[i].pTexture = new Texture();
				materialList_[i].pTexture->Load(textureFilePath);
			}
			else
			{
				//�e�N�X�`���t�@�C�����Ȃ����̏���
				//materialList_[i].pTexture = nullptr;
			}
		}
		//�e�N�X�`������
		else
		{
			//�e�N�X�`�������̎��̏���
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
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ

	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	Direct3D::pContext->DrawIndexed(polygonCount_ * 3, 0, 0);

}

void Fbx::Release()
{
	/*SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pConstantBuffer_);*/
}