#pragma once

#pragma once

#include <list>
#include <string>
#include "Transform.h"
using std::string;
using std::list;
class GameObject
{
	list<GameObject*> childList_;
	Transform transform_;
	GameObject*	pParent_;
	string	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	//継承したときに元のデストラクタが呼べなくなる
	virtual ~GameObject();

	//純粋仮想関数にする
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};
