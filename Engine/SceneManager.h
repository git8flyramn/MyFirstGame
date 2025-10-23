#pragma once
#include "GameObject.h"
//�V�[��ID�̗񋓌^
enum SCENE_ID
{
	SCENE_ID_TEST,
	SCENE_ID_PLAY,
	SCENE_ID_MAX
};
//�V�[���̊��N���X
class SceneManager
	: public GameObject
{
public:
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
	SceneManager(GameObject* parent);
	~SceneManager();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ChangeScene(SCENE_ID _nextScene);

private:

};

