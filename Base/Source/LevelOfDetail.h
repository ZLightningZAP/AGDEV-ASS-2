#ifndef LEVEL_OF_DETAIL_H
#define LEVEL_OF_DETAIL_H

#include "Mesh.h"
#include "..\Base\Source\Object\GameObject.h"

class LevelOfDetail
{
public:
	enum RESOLUTION_TYPE
	{
		RES_LOW,
		RES_MID,
		RES_HIGH,
		NUM_RESOLUTION,
	};

	LevelOfDetail();
	~LevelOfDetail();

	void Init(Mesh* Resolution[NUM_RESOLUTION]);
	Mesh* Update(double dt, CTransform* me, CTransform* object);

	static int HIGH_RES_DIST;
	static int MID_RES_DIST;

private:
	Mesh* m_Resolution[NUM_RESOLUTION];
};

#endif