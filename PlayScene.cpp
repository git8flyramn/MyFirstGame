#include "PlayScene.h"
#include "Player.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//player�̃C���X�^���X�̐���,�q�I�u�W�F�N�g�ɒǉ�����
	//Player* pPlayer = new Player(this);
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);

	Instantiate<Player>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
