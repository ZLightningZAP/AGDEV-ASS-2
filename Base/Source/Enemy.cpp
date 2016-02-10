#include "Enemy.h"


CEnemy::CEnemy()
: health(100)
, currentFSM(ESCAPE)
{
}


CEnemy::~CEnemy()
{
}

void CEnemy::Init(Mesh* enemy, Vector3 pos)
{
	//float x = pos.x, y = pos.y, z = pos.z;
	Vector3 SIZE(20, 20, 20);
	CTransform* transform = new CTransform();
	transform->Init(pos, Vector3::ZERO_VECTOR, SIZE);

	//Enemy
	CGameObject::Init(enemy, transform);
	CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
}

void CEnemy::Update(const float dt, Vector3 thePosition)
{
	if (health == 0)
	{
		currentFSM = ESCAPE;
	}
	else if (health == 100)
	{
		currentFSM = ATTACK;

		Vector3 position = m_transform.m_translate;

		Vector3 distanceVector = thePosition - position;
		float theDistance = distanceVector.Length();

		//if the player is within this node's cohesion ring, then move towards it.
		if ((theDistance > 10.0f) && (theDistance < 50.0f))
		{
			currentFLOCKING = COHESION;
		}

		//if the player is within this node's seperation ring, then move away from it.
		else if (theDistance < 10.0f)
		{
			currentFLOCKING = SEPERATION;
		}
		else
		{
			currentFLOCKING = IDLE;
		}
	}

	if (currentFSM == ESCAPE)
	{
		Vector3 position = m_transform.m_translate;

		Vector3 newDirection = thePosition - position;
		if (newDirection.Length() > 0.0f)
		{
			// Moving Away Direction
			newDirection.Normalize();

			m_transform.m_translate += newDirection * dt * 200;
		}
		if (health < 100)
			health++;
	}
	else if (currentFSM == ATTACK)
	{
		Vector3 position = m_transform.m_translate;

		Vector3 newDirection = position - thePosition;

		switch (currentFLOCKING)
		{
		case SEPERATION:
			if (newDirection.Length() > 0.0f)
			{
				newDirection.Normalize();
				m_transform.m_translate = Vector3::Move(position, thePosition, dt * 200, true);
			}
			break;

		case COHESION:
			if (newDirection.Length() > 0.0f)
			{
				newDirection.Normalize();
				m_transform.m_translate = Vector3::Move(position, thePosition, dt * 200);
			}
			health--;
			break;

		case IDLE:

			break;

		default:
			break;
		}
	}
}