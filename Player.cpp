#include "Player.h"
#include "Engine//Fbx.h"
#include "ChildOden.h"
#include "Engine/Model.h"
Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx_(nullptr)
{

}

Player::~Player()
{
}

void Player::Update()
{
	transform_.rotate_.y += 1.0f;
	if (transform_.rotate_.y > 720.0f)
	{
		//KillMe();
	}
}

void Player::Initialize()
{
	//pFbx_ = new Fbx;
	////pFbx_がNullptrじゃなかったら、のチェックをしておくと
	////良い。
	//pFbx_->Load("Oden.fbx");
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;
	//子のオブジェクトにChildOdenを追加する
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden = (ChildOden*)Instantiate<ChildOden>(this);
	pRChildOden_->SetPosition(2.0f, 1.0f, 0.0f);
	pLChildOden->SetPosition(-2.0f, 1.0f, 0.0f);
	hModel_ = Model::Load("Odenkushi.fbx");
}

void Player::Draw()
{
	///*if (pFbx_)
	//{
	//	pFbx_->Draw(transform_);
	//}*/
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

void Player::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
