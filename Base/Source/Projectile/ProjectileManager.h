#pragma once

#include "Projectile2.h"

class CProjectileManager
{
public:
	CProjectileManager(void);
	~CProjectileManager(void);

	// Projectile
	bool AddProjectile(Vector3 position, Vector3 direction, const float speed = 10.0f);
	bool AddRayProjectile(Vector3 pos, Vector3 dir, const float speed = 10.f, const float length = 10.f);
	void SetProjectile(const int index, Vector3 position, Vector3 direction);
	void RemoveProjectile(const int index);

	// Access modifiers
	int GetMaxNumberOfProjectiles(void);
	int GetNumberOfActiveProjectiles(void);
	CProjectile2* GetProjectile(const int index);

	// Check methods
	bool IsValid(const int index);
	bool IsActive(const int index);

	// Update
	void Update(const double dt);

	// Variables
	CProjectile2** theListOfProjectiles;
	int NumOfActiveProjectile;
	int CurrentEmptyProjectile;
	Vector3 Boundary_TopLeft, Boundary_BottomRight;
};

