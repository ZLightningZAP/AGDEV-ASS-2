#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "introstate.h"
#include "playstate.h"
#include "gamestate.h"
#include "menustate.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Init\n" << endl;
#endif
	scene = new MainMenuScene();
	scene->Init();
}

void CMenuState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Init\n" << endl;
#endif
	scene = new MainMenuScene();
	scene->Init();
}

void CMenuState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Cleanup\n" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CMenuState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Pause\n" << endl;
#endif
}

void CMenuState::Resume()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Resume\n" << endl;
#endif
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CMenuState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CIntroState::Instance() );
	//			break;

	//		case 1:
	//			theGSM->ChangeState( CPlayState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
#if GSM_DEBUG_MODE
	/*int m_iUserChoice = -1;

	do {
		cout << "CMenuState:";
		cout << "Choose one <1> Go to Play State:";
		cout << "Choose one <2> Go to Instruction State:";
		cout << "Choose one <3> Go to Option State:";
		cout << "Choose one <4> Go to Highscore State:";
		cin >> m_iUserChoice;
		cin.get();

		switch (m_iUserChoice) {
		case 1:
			theGSM->ChangeState(CPlayState::Instance());
			break;

		case 2:
			theGSM->ChangeState(InstructionState::Instance());
			break;

		case 3:
			theGSM->ChangeState(OptionState::Instance());
			break;

		case 4:
			theGSM->ChangeState(HighscoreState::Instance());
			break;

		default:
			cout << "Invalid choice!\n";
			m_iUserChoice = -1;
			break;
		}
	} while (m_iUserChoice == -1);*/
#endif
	if (key == 49)
	{
		theGSM->ChangeState(CPlayState::Instance());
	}
	if (key == 50)
	{
		theGSM->ChangeState(InstructionState::Instance());
	}
	if (key == 51)
	{
		theGSM->ChangeState(OptionState::Instance());
	}
	if (key == 52)
	{
		theGSM->ChangeState(HighscoreState::Instance());
	}
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
#if GSM_DEBUG_MODE
	int m_iUserChoice = -1;

	do {
		cout << "CMenuState: Choose one <0> Go to Intro State, <1> Go to Play State : ";
		cin >> m_iUserChoice;
		cin.get();

		switch (m_iUserChoice) {
		case 0:
			theGSM->ChangeState(CIntroState::Instance());
			break;

		case 1:
			theGSM->ChangeState(CPlayState::Instance());
			break;
		default:
			cout << "Invalid choice!\n";
			m_iUserChoice = -1;
			break;
		}
	} while (m_iUserChoice == -1);
#endif
}

void CMenuState::Update(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Update\n" << endl;
#endif
	scene->Update(0.16667);
}

void CMenuState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
}

void CMenuState::Draw(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Draw\n" << endl;
#endif
	scene->Render();
}
