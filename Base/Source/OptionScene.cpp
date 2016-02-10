#include "OptionScene.h"


OptionScene::OptionScene()
{
}


OptionScene::~OptionScene()
{
}

void OptionScene::Init()
{
	SceneBase::Init();
}

void OptionScene::Render()
{
	SceneBase::Render();
	modelStack.PushMatrix();
	modelStack.Scale(m_window_width, m_window_height, 1);
	RenderMeshIn2D(meshList[GEO_OPTIONS], false);
	modelStack.PopMatrix();
}

void OptionScene::Update(double dt)
{
	SceneBase::Update(dt);
}

void OptionScene::Exit()
{
	SceneBase::Exit();
}
