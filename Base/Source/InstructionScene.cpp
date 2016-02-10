#include "InstructionScene.h"


InstructionScene::InstructionScene()
{
}


InstructionScene::~InstructionScene()
{
}

void InstructionScene::Init()
{
	SceneBase::Init();
}

void InstructionScene::Render()
{
	SceneBase::Render();
	modelStack.PushMatrix();
	modelStack.Scale(m_window_width, m_window_height, 1);
	RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false);
	modelStack.PopMatrix();
}

void InstructionScene::Update(double dt)
{
	SceneBase::Update(dt);
}

void InstructionScene::Exit()
{
	SceneBase::Exit();
}
