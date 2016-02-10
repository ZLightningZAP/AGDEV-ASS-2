#pragma once
#include "SceneBase.h"
#include <sstream>

class HighscoreScene : public SceneBase
{
public:
	HighscoreScene();
	~HighscoreScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

