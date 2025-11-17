#include "Enemy.h"
#include "Engine//SphereCollider.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),pFbx(nullptr)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("box.fbx");
	transform_.position_ = { 5.0f,0.0f,50.0f };
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Enemy::Draw()
{
	pFbx->Draw(transform_);
}

void Enemy::Release()
{
}
