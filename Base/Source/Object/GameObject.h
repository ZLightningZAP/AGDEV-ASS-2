#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object.h"
#include "Collider.h"
#include "..\Base\Source\LevelOfDetail.h"

class CGameObject : public CObject, public CCollider
{
protected:
	CTransform m_transform;
	LevelOfDetail lod;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void Init(Mesh* mesh, CTransform* transform, bool active = true, bool render = true);
	void InitLod(Mesh* Resolution[LevelOfDetail::NUM_RESOLUTION]);
	void UpdateLod(Vector3 target);
	virtual void Update(const double dt);
	virtual void Reset();

	// Setters and Getters
	CTransform& GetTransform();
};

#endif