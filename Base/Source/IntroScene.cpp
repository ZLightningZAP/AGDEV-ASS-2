#include "IntroScene.h"


IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::Init()
{
	SceneBase::Init();
}

void IntroScene::Render()
{
	SceneBase::Render();
	modelStack.PushMatrix();
	modelStack.Scale(m_window_width, m_window_height, 1);
	RenderMeshIn2D(meshList[GEO_INTRO], false);
	modelStack.PopMatrix();
}

void IntroScene::Update(double dt)
{
	SceneBase::Update(dt);
}

void IntroScene::Exit()
{
	SceneBase::Exit();
}
