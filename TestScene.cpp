#include "TestScene.h"
#include "Engine//Fbx.h"
#include "Engine//Model.h"
TestScene::TestScene(GameObject* parent)
	: GameObject(parent,"TestScene")
{
	
}

TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
{
	/*
	pRChildOden_->SetPosition(2.0f, 1.0f, 0.0f);
	pLChildOden->SetPosition(-2.0f, 1.0f, 0.0f);
	*/
	transform_.scale_.x = 0.3f;
	transform_.scale_.y = 0.3f;
	transform_.scale_.z = 0.3f;
	transform_.position_.x = 1.0f;
	transform_.position_.y = 1.0f;
	hModel_ = Model::Load("Odenkushi.fbx");
}

void TestScene::Update()
{
	//�X�y�[�X�L�[����������,SceneManager::ChangeScene(SCENE_ID_PLAY);���Ăяo��
	SceneManager* pScene = nullptr;
	pScene = new SceneManager(nullptr);
	pScene->ChangeScene(SCENE_ID_PLAY);
	 
}

void TestScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestScene::Release()
{
}
