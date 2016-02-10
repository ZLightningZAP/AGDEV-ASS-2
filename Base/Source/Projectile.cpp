#include "Projectile.h"



CProjectile::CProjectile()
	: m_dir(0,0,1)
	, m_speed(0.f)
	, m_length(0.f)
{
}


CProjectile::~CProjectile()
{
}

void CProjectile::Init(Vector3 dir, float speed, Mesh * mesh, CTransform * transform, bool active, bool render)
{
	CGameObject::Init(mesh, transform, active, render);
	m_dir = dir;
	m_speed = speed;
}

void CProjectile::Update(const double dt)
{
	CGameObject::Update(dt);

	if (!m_dir.IsZero())
	{
		m_transform.m_translate += m_dir * (m_speed * dt);
		CCollider::Update(m_transform);
	}

	Vector3 Boundary_TopLeft = Vector3(400.0f, 50.0f, 400.0f);
	Vector3 Boundary_BottomRight = Vector3(-400.0f, -50.0f, -400.0f);

	Vector3 CheckThisPosition = m_transform.m_translate;
	if (((CheckThisPosition.x > Boundary_TopLeft.x) ||
		(CheckThisPosition.y > Boundary_TopLeft.y) ||
		(CheckThisPosition.z > Boundary_TopLeft.z)) ||
		((CheckThisPosition.x < Boundary_BottomRight.x) ||
			(CheckThisPosition.y < Boundary_BottomRight.y) ||
			(CheckThisPosition.z < Boundary_BottomRight.z)))
	{
		CProjectile::Reset();
	}
}

void CProjectile::Reset()
{
	CGameObject::Reset();
	m_dir.Set(0, 0, 1);
	m_speed = 0.f;
	m_length = 0.f;
}

void CProjectile::SetDir(Vector3 dir)
{
	m_dir = dir;
}

Vector3 & CProjectile::GetDir()
{
	return m_dir;
}

void CProjectile::SetLength(float length)
{
	m_length = length;
}

float CProjectile::GetLength()
{
	return m_length;
}
