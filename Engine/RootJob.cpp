#include "RootJob.h"
#include "../PlayScene.h"
RootJob::RootJob(GameObject* parent)
	:GameObject(parent,"RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	//PlayScence�𐶐����āA�q�I�u�W�F�N�g�ɒǉ�
	/*PlayScene* playscence;
	playscence = new PlayScene(this);
	playscence->Initialize();
	childList_.push_back(playscence);*/
	Instantiate<PlayScene>(this);

}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
