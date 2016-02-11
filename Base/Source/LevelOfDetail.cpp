#include "LevelOfDetail.h"


LevelOfDetail::LevelOfDetail()
{
}


LevelOfDetail::~LevelOfDetail()
{
	
}

void LevelOfDetail::Init(Mesh* Resolution[NUM_RESOLUTION])
{
	for (int i = 0; i < NUM_RESOLUTION; ++i)
	{
		m_Resolution[i] = Resolution[i];
	}
}

Mesh* LevelOfDetail::Update(double dt, Vector3 me, Vector3 object)
{
	float DistSq = (me - object).LengthSquared();

	if (DistSq < HIGH_RES_DIST)
	{
		return m_Resolution[RES_HIGH];
	}
	else if (DistSq < MID_RES_DIST)
	{
		return m_Resolution[RES_MID];
	}
	else
	{
		return m_Resolution[RES_LOW];
	}
}