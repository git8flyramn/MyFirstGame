#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "ChildOden.h"
#include "Engine/SphereCollider.h"
#include "Engine/Input.h"
Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel_(-1)
{

}

Player::~Player()
{
}



void Player::Initialize()
{
	 //pFbx_ = new Fbx;
	////pFbx_がNullptrじゃなかったら、のチェックをしておくと
	////良い。
	 hModel_ = Model::Load("OdenKushiZasi.fbx");
	//assert(hModel_ > 0);
	//pFbx_->Load("Oden.fbx");
	transform_.scale_.x = 0.5f;
	transform_.scale_.y = 0.5f;
	transform_.scale_.z = 0.5f;
	//子のオブジェクトにChildOdenを追加する
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden = (ChildOden*)Instantiate<ChildOden>(this);
	pRChildOden_->SetPosition(2.0f, 1.0f, 0.0f);
	pLChildOden->SetPosition(-2.0f, 1.0f, 0.0f);
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);

}

void Player::Update()
{

	static float x = 0.0;
	float tx = sin(x) * 5.0f;
	x += 0.02f;
	//transform_.position_.x = tx;
	transform_.rotate_.y += 1.0f;
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.z += 0.2f;
	}

	//if (transform_.rotate_.y > 720.0f)
	//{
	//	//KillMe();
	//}
}

void Player::Draw()
{
	/*if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}*/
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
	/*if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}*/
}
