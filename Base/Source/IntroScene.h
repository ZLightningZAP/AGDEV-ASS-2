#pragma once
#include "SceneBase.h"

class IntroScene : public SceneBase
{
public:
	IntroScene();
	~IntroScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

