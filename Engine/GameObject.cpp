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
	//本体の機能を呼び出す
	transform_.Calculation();
	this->Update();
	for (auto child : childList_)
	{
		child->UpdateSub();
	}

}

void GameObject::ReleaseSub()
{
	this->Release();//自分を解放
	for (auto child : childList_)
	{
		child->ReleaseSub();
	}
	
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			//isDead_のtrueの場所のポインタを消す
			delete(*itr);
			//isDead_のtrueがあった場所の次の場所を指す。
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

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;//rootJobだよ
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const string& name)
{
	if (this->objectName_ == name)
	{
		return this;//自分が探されていたオブジェクト
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* result = child->FindChildObject(name);
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;//自分が探されていたオブジェクト
	}
}

GameObject* GameObject::FindObject(const string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* result = rootJob->FindChildObject(name);
	return result;
}

