#include "GameObject.h"

GameObject::GameObject(): pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name)
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
}