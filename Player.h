#pragma once
#include "Engine/GameObject.h"

class Fbx;
class Player :
    public GameObject
{
private:
    Fbx* pFbx_;
public:
    Player(GameObject* parent);
    ~Player();
    void Update()override;
    void Initialize() override;
    void Draw() override;
    void Release() override;
};

