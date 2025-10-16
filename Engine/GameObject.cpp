#include "GameObject.h"

GameObject::GameObject(): pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),isDead_(false)
{
	if (parent != nullptr)
	{
		transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	
	this->Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
	
	/*for(auto child : childList_)
	* {
	*    child->DrawSub();
	* }
	*/
}

void GameObject::UpdateSub()
{
	//�{�̂̋@�\���Ăяo��
	this->Update();
	for (auto child : childList_)
	{
		child->UpdateSub();
	}

}

void GameObject::ReleaseSub()
{
	this->Release();//���������
	for (auto child : childList_)
	{
		child->ReleaseSub();
	}
	
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			//isDead_��true�̏ꏊ�̃|�C���^������
			delete(*itr);
			//isDead_��true���������ꏊ�̎��̏ꏊ���w���B
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	transform_.position_.z = z;
}

void GameObject::KillMe()
{
	isDead_ = true;
}

