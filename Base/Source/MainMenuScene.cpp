#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
}


MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Init()
{
	SceneBase::Init();
}

void MainMenuScene::Render()
{
	SceneBase::Render();
	modelStack.PushMatrix();
	modelStack.Scale(m_window_width, m_window_height, 1);
	RenderMeshIn2D(meshList[GEO_MAINMENU], false);
	modelStack.PopMatrix();
}

void MainMenuScene::Update(double dt)
{
	SceneBase::Update(dt);
}

void MainMenuScene::Exit()
{
	SceneBase::Exit();
}
