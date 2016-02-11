#include "GameObject.h"
#include "..\SpatialPartition\Grid.h"

CGameObject::CGameObject() : CObject(), CCollider(), m_transform()
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Init(Mesh* mesh, CTransform* transform, bool active, bool render)
{
	CObject::Init(mesh, active, render);
	m_transform = *transform;
	//CCollider::Init(CT_AABB, m_transform, X_MIDDLE, Y_BOTTOM, true);
}

void CGameObject::UpdateLod(Vector3 target)
{
	m_mesh = lod.Update(0, m_transform.m_translate, target);
}

void CGameObject::InitLod(Mesh* Resolution[LevelOfDetail::NUM_RESOLUTION])
{
	lod.Init(Resolution);
}

void CGameObject::Update(const double dt)
{
}

void CGameObject::Reset()
{
	CObject::Reset();
	CCollider::Reset();
	m_transform.Reset();
}

CTransform & CGameObject::GetTransform()
{
	return m_transform;
}
