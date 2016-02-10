#pragma once
#include "SceneBase.h"

class MainMenuScene : public SceneBase
{
public:
	MainMenuScene();
	~MainMenuScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

