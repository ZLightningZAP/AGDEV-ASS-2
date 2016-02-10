#pragma once
#include "SceneBase.h"

class OptionScene : public SceneBase
{
public:
	OptionScene();
	~OptionScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

