#include "Projectile2.h"

/********************************************************************************
 Constructor
 ********************************************************************************/
CProjectile2::CProjectile2(void)
: m_bActive(false)
, thePosition(0, 0, 0)
, theDirection(0, 0, 0)
, speed(0.0f)
, length(0.f)
, type(PROJ_TYPE_DISCRETE)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CProjectile2::~CProjectile2(void)
{
}

/********************************************************************************
 Update the status of this projectile
 ********************************************************************************/
void CProjectile2::Update(const double dt)
{
	if (m_bActive == false)
		return;

	// Update Position
	thePosition.Set(	thePosition.x + theDirection.x * speed * dt, 
						thePosition.y + theDirection.y * speed * dt, 
						thePosition.z + theDirection.z * speed * dt);
}

/********************************************************************************
 Activate the projectile. true == active, false == inactive
 ********************************************************************************/
void CProjectile2::SetActivate(bool m_bActivate)
{
	if (m_bActivate == true)
		m_bActive = true;
	else
		m_bActive = false;
}

/********************************************************************************
 get status of the projectile. true == active, false == inactive
 ********************************************************************************/
bool CProjectile2::GetStatus(void)
{
	return m_bActive;
}

/********************************************************************************
 Get the position of the projectile
 ********************************************************************************/
Vector3 CProjectile2::GetPosition(void)
{
	return thePosition;
}

/********************************************************************************
 Get the direction of the projectile
 ********************************************************************************/
Vector3 CProjectile2::GetDirection(void)
{
	return theDirection;
}

/********************************************************************************
 Set the position of the projectile
 ********************************************************************************/
void CProjectile2::SetPosition(Vector3 theNewPosition)
{
	thePosition.Set( theNewPosition.x, theNewPosition.y, theNewPosition.z);
}

/********************************************************************************
 Set the direction of the projectile
 ********************************************************************************/
void CProjectile2::SetDirection(Vector3 theNewDirection)
{
	theDirection.Set( theNewDirection.x, theNewDirection.y, theNewDirection.z);
}

/********************************************************************************
 Set speed
 ********************************************************************************/
void CProjectile2::SetSpeed(const float speed)
{
	this->speed = speed;
}

void CProjectile2::SetLength(float length)
{
	this->length = length;
	type = PROJ_TYPE_RAY;
}

float CProjectile2::GetLength()
{
	return length;
}

void CProjectile2::SetType(PROJECTILE_TYPE type)
{
	this->type = type;
}

CProjectile2::PROJECTILE_TYPE CProjectile2::GetType()
{
	return type;;
}
