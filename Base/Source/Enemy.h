#pragma once
#include "Object\GameObject.h"
#include "PlayInfo3PV.h"
#include <vector>

using std::vector;

class CEnemy : public CGameObject
{
public:
	enum FSM
	{
		ESCAPE,
		ATTACK,
		NUM_FSM,
	};
	enum FLOCKING
	{
		SEPERATION,
		COHESION,
		IDLE,
		NUM_FLOCKING
	};

	int health;

	CEnemy();
	virtual ~CEnemy();

	CPlayInfo3PV* m_cAvatar;

	virtual void Init(Mesh* enemy, Vector3 pos);

	void Update(const float dt, Vector3 thePosition);

private:
	FSM currentFSM;
	FLOCKING currentFLOCKING;
};

