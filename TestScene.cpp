#include "TestScene.h"
#include "Engine//Input.h"
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
}

void TestScene::Update()
{
	//�X�y�[�X�L�[����������,SceneManager::ChangeScene(SCENE_ID_PLAY);���Ăяo��
	if (Input::IsKey(DIK_SPACE))
	{
		SceneManager* Scene;
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
