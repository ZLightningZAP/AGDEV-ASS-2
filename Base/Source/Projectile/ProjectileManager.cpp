#include "ProjectileManager.h"

static const int theMaxNumberOfProjectiles = 50;

/********************************************************************************
 Constructor
 ********************************************************************************/
CProjectileManager::CProjectileManager(void)
	: theListOfProjectiles(NULL)
	, NumOfActiveProjectile(0)
	, CurrentEmptyProjectile(0)
{
	theListOfProjectiles = new CProjectile2*[theMaxNumberOfProjectiles];
	for (int i=0; i<theMaxNumberOfProjectiles; i++)
	{
		theListOfProjectiles[i] = new CProjectile2();
	}
	Boundary_TopLeft		= Vector3( 300.0f, 300.0f, 300.0f);
	Boundary_BottomRight	= Vector3( -300.0f, 0.0f, -300.0f);
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CProjectileManager::~CProjectileManager(void)
{
	if (theListOfProjectiles)
	{
		for (int i=0; i<theMaxNumberOfProjectiles; i++)
		{
			delete theListOfProjectiles[i];
		}
		delete [] theListOfProjectiles;
		theListOfProjectiles = NULL;
	}
}

/********************************************************************************
 Add Projectile
 ********************************************************************************/
bool CProjectileManager::AddProjectile(Vector3 position, Vector3 direction, const float speed)
{
	// Find the next empty projectile
	if (NumOfActiveProjectile < theMaxNumberOfProjectiles)
	{
		int StartIndex = CurrentEmptyProjectile;
		// Loop until we find an empty slot
		while (CurrentEmptyProjectile < theMaxNumberOfProjectiles && theListOfProjectiles[CurrentEmptyProjectile]->GetStatus() == true)
		{
			CurrentEmptyProjectile++;
			if (CurrentEmptyProjectile >= theMaxNumberOfProjectiles)
				CurrentEmptyProjectile = 0;
			// If we have checked 'theMaxNumberOfProjectiles' number of slots, and
			// still have not found a vacancy, then stop this loop. As the slot at 
			// CurrentEmptyProjectile is not empty, we will not be able to add it in.
			if (CurrentEmptyProjectile == StartIndex)
				break;
		}

		if (CurrentEmptyProjectile < theMaxNumberOfProjectiles && IsActive(CurrentEmptyProjectile)==false)
		{
			theListOfProjectiles[CurrentEmptyProjectile]->SetType(CProjectile2::PROJ_TYPE_DISCRETE);
			theListOfProjectiles[CurrentEmptyProjectile]->SetPosition( position );
			theListOfProjectiles[CurrentEmptyProjectile]->SetDirection( direction );
			theListOfProjectiles[CurrentEmptyProjectile]->SetSpeed( speed );
			theListOfProjectiles[CurrentEmptyProjectile]->SetActivate( true );
			CurrentEmptyProjectile++;
			NumOfActiveProjectile++;

			return true;
		}
	}
	return false;
}

bool CProjectileManager::AddRayProjectile(Vector3 pos, Vector3 dir, const float speed, const float length)
{
	if (NumOfActiveProjectile < theMaxNumberOfProjectiles)
	{
		int startIndex = CurrentEmptyProjectile;
		// Loop until we find an empty slot
		while (CurrentEmptyProjectile < theMaxNumberOfProjectiles && theListOfProjectiles[CurrentEmptyProjectile]->GetStatus() == true)
		{
			CurrentEmptyProjectile++;
			if (CurrentEmptyProjectile >= theMaxNumberOfProjectiles)
				CurrentEmptyProjectile = 0;
			// If we have checked 'theMaxNumberOfProjectiles' number of slots, and
			// still have not found a vacancy, then stop this loop. As the slot at 
			// CurrentEmptyProjectile is not empty, we will not be able to add it in.
			if (CurrentEmptyProjectile == startIndex)
				break;
		}

		if (IsActive(CurrentEmptyProjectile) == false)
		{
			pos += Vector3(0.f, 0.5f, 0.f);
			theListOfProjectiles[CurrentEmptyProjectile]->SetPosition(pos);
			theListOfProjectiles[CurrentEmptyProjectile]->SetDirection(dir);
			theListOfProjectiles[CurrentEmptyProjectile]->SetSpeed(speed);
			theListOfProjectiles[CurrentEmptyProjectile]->SetLength(length);
			theListOfProjectiles[CurrentEmptyProjectile]->SetActivate(true);
			++CurrentEmptyProjectile;
			if (CurrentEmptyProjectile >= theMaxNumberOfProjectiles)
			{
				CurrentEmptyProjectile = 0;
			}
			++NumOfActiveProjectile;

			return true;
		}
	}
	return false;
}

/********************************************************************************
 Set Projectile
 ********************************************************************************/
void CProjectileManager::SetProjectile(const int index, Vector3 position, Vector3 direction)
{
	theListOfProjectiles[index]->SetPosition( position );
	theListOfProjectiles[index]->SetDirection( direction );
	theListOfProjectiles[index]->SetActivate( true );
}

/********************************************************************************
 Remove Projectile
 ********************************************************************************/
void CProjectileManager::RemoveProjectile(const int index)
{
	if (IsValid( index ))
	{
		theListOfProjectiles[index]->SetActivate( false );
		NumOfActiveProjectile--;
		// Set current empty projectile
		if (index < CurrentEmptyProjectile)
		{
			CurrentEmptyProjectile = index;
		}
	}
}

/********************************************************************************
 Get Maximum Number of Projectiles
 ********************************************************************************/
int CProjectileManager::GetMaxNumberOfProjectiles(void)
{
	return theMaxNumberOfProjectiles;
}

/********************************************************************************
 Get Number of Active Projectile
 ********************************************************************************/
int CProjectileManager::GetNumberOfActiveProjectiles(void)
{
	return NumOfActiveProjectile;
}

/********************************************************************************
 Get Projectile
 ********************************************************************************/
CProjectile2* CProjectileManager::GetProjectile(const int index)
{
	if (IsValid( index ))
		return theListOfProjectiles[index];
	return NULL;
}

/********************************************************************************
 Check methods
 ********************************************************************************/
bool CProjectileManager::IsValid(const int index)
{
	if ((index<0) || (index>theMaxNumberOfProjectiles))
		return false;
	return true;
}

/********************************************************************************
 Check if a projectile is active
 ********************************************************************************/
bool CProjectileManager::IsActive(const int index)
{
	if (IsValid(index))
		return theListOfProjectiles[index]->GetStatus();
	else
		return true;	//	return true as we do not wish to use this index
}

/********************************************************************************
 Update
 ********************************************************************************/
void CProjectileManager::Update(const double dt)
{
	for (int i=0; i<theMaxNumberOfProjectiles; i++)
	{
		// Skip this projectile if it is not active
		if (theListOfProjectiles[i]->GetStatus() == false)
			continue;

		// Update the projectile
		theListOfProjectiles[i]->Update(dt);

		// Check if it is out of the boundaries
		Vector3 CheckThisPosition = theListOfProjectiles[i]->GetPosition();
		if (((CheckThisPosition.x > Boundary_TopLeft.x) || 
		     (CheckThisPosition.y > Boundary_TopLeft.y) ||
		     (CheckThisPosition.z > Boundary_TopLeft.z)) ||
			 ((CheckThisPosition.x < Boundary_BottomRight.x) ||
		     (CheckThisPosition.y < Boundary_BottomRight.y) ||
		     (CheckThisPosition.z < Boundary_BottomRight.z)) )
		{
			// Since it is out of the boundaries, then set it to inactive
			RemoveProjectile( i );
		}
	}
}