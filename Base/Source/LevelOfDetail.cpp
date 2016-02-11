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

Mesh* LevelOfDetail::Update(double dt, CTransform* me, CTransform* object)
{
	float DistSq = (me->m_translate - object->m_translate).LengthSquared();

	if (DistSq >= HIGH_RES_DIST * HIGH_RES_DIST)
	{
		return m_Resolution[RES_HIGH];
	}
	else if ((DistSq < HIGH_RES_DIST * HIGH_RES_DIST) && (DistSq >= MID_RES_DIST * MID_RES_DIST))
	{
		return m_Resolution[RES_MID];
	}
	else
	{
		return m_Resolution[RES_LOW];
	}
}