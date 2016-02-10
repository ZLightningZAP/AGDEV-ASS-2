#include "HighscoreScene.h"
#include "GameStateManager.h"


HighscoreScene::HighscoreScene()
{
}


HighscoreScene::~HighscoreScene()
{
}

void HighscoreScene::Init()
{
	SceneBase::Init();
}

void HighscoreScene::Render()
{
	SceneBase::Render();
	modelStack.PushMatrix();
	modelStack.Scale(m_window_width, m_window_height, 1);
	RenderMeshIn2D(meshList[GEO_HIGHSCORE], false);
	modelStack.PopMatrix();

	std::ostringstream ss;
	ss << CGameStateManager::highscore;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 10, 35, 8);
	
}

void HighscoreScene::Update(double dt)
{
	SceneBase::Update(dt);
}

void HighscoreScene::Exit()
{
	SceneBase::Exit();
}
