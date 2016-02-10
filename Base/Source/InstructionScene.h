#pragma once
#include "SceneBase.h"

class InstructionScene : public SceneBase
{
public:
	InstructionScene();
	~InstructionScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

