#include "Bullet.h"
#include "Engine//SphereCollider.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
Bullet::Bullet(GameObject* parent) 
	:GameObject(parent, "Bullet"), pFbx(nullptr)
{

}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	pFbx = new Fbx;
	transform_.scale_.x = 0.5f;
	transform_.scale_.y = 0.5f;
	transform_.scale_.z = 0.5f;
	pFbx->Load("OdenKushiZasi.fbx");
	transform_.position_ = {  1.0f,-2.0f,0.0f };
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Bullet::Update()
{
	/*if (Input::IsKey(DIK_S))
	{
		transform_.position_.x += 0.2f;
	}*/
}

void Bullet::Draw()
{
	pFbx->Draw(transform_);
}

void Bullet::Release()
{
}
