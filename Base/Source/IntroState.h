#pragma once

#include "gamestate.h"
#include "IntroScene.h"
#include "timer.h"
#include "MenuState.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class CIntroState : public CGameState
{
public:
	float timer;

	void Init();
	void Init(const int width, const int height);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* theGSM);
	void HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status = true);
	void HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right);
	void Update(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM, const double m_dElapsedTime);
	void Draw(CGameStateManager* theGSM);

	static CIntroState* Instance() {
		return &theIntroState;
	}

protected:
	CIntroState() { }

private:
	static CIntroState theIntroState;
	IntroScene *scene;
};
