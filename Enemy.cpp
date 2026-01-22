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
	//‚±‚±‚Åƒh[ƒiƒc‚ð•`‰æ‚·‚éêŠ‚Ì” ‚Ì•`‰æ
	pFbx = new Fbx;
	pFbx->Load("Room.fbx");
  //pFbx->Load("Room.fbx);
	transform_.scale_.x = 2.0f;
	transform_.scale_.y = 2.0f;
	transform_.scale_.z = 2.0f;
	transform_.position_ = { 0.0f,0.0f,-3.0f };
	/*SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);*/
}

void Enemy::Draw()
{
	pFbx->Draw(transform_);
}

void Enemy::Release()
{
}
