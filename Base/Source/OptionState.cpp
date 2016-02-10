#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "gamestate.h"
#include "menustate.h"
#include "OptionState.h"

OptionState OptionState::theOptionState;

void OptionState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Init\n" << endl;
#endif
	scene = new OptionScene();
	scene->Init();
}

void OptionState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Init\n" << endl;
#endif
	scene = new OptionScene();
	scene->Init();
}

void OptionState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Cleanup\n" << endl;
#endif

	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void OptionState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Pause\n" << endl;
#endif
}

void OptionState::Resume()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Resume\n" << endl;
#endif
}

void OptionState::HandleEvents(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CIntroState: Choose one <0> Go to Menu State, <1> Go to Play State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
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

void OptionState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CIntroState: Choose one <0> Go to Menu State, <1> Go to Play State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
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

	if (key == '0')
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
}

void OptionState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							   const int button_Left, const int button_Middle, const int button_Right)
{
#if GSM_DEBUG_MODE
	//int m_iUserChoice = -1;

	//do {
	//	cout << "CIntroState: Choose one <0> Go to Menu State, <1> Go to Play State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CMenuState::Instance() );
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

void OptionState::Update(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Update\n" << endl;
#endif
	scene->Update(0.16667);
}

void OptionState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
}

void OptionState::Draw(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Draw\n" << endl;
#endif
	scene->Render();
}
