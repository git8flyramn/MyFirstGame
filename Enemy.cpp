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
	static float y = 0.0f;
	float ty = sin(y) * 5.0f;
	//y += 0.02f;
	//transform_.position_.y = ty;
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("box.fbx");
	transform_.scale_.x = 1.0f;
	transform_.scale_.y = 1.0f;
	transform_.scale_.z = 1.0f;
	transform_.position_ = { 5.0f,0.0f,0.0f };
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
