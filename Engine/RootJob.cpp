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
	//PlayScenceを生成して、子オブジェクトに追加
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
