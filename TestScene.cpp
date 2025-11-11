#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine//SceneManager.h"
TestScene::TestScene(GameObject* parent)
	: GameObject(parent,"TestScene")
{
	
}

TestScene::~TestScene()
{
	
}

void TestScene::Initialize()
{
	
	/*pRChildOden_->SetPosition(2.0f, 1.0f, 0.0f);
	pLChildOden->SetPosition(-2.0f, 1.0f, 0.0f);*/
	
	//transform_.scale_.x = 0.7f;
	//transform_.scale_.y = 0.7f;
	//transform_.scale_.z = 0.7f;
	//transform_.position_.x = 0.5f;
	//transform_.position_.y = 0.5f;
//	hModel_ = hModel_::Load("Oden.fbx");
}

void TestScene::Update()
{
	//スペースキーを押したら,SceneManager::ChangeScene(SCENE_ID_PLAY);を呼び出す
    
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
	 
}

void TestScene::Draw()
{
	/*Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);*/
}

void TestScene::Release()
{
}
