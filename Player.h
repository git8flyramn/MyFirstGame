#pragma once
#include "Engine//GameObject.h"
class Fbx;
class ChildOden;
class Player :
    public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    void Update()override;
    void Initialize() override;
    void Draw() override;
    void Release() override;
private:
   // Fbx* pFbx_;
    ChildOden* pRChildOden_;
    ChildOden* pLChildOden;
    int hModel_;
};

