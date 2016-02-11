#ifndef LEVEL_OF_DETAIL_H
#define LEVEL_OF_DETAIL_H

#include "Mesh.h"
#include "Vector3.h"

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
	Mesh* Update(double dt, Vector3 me, Vector3 object);

	static int HIGH_RES_DIST;
	static int MID_RES_DIST;

private:
	Mesh* m_Resolution[NUM_RESOLUTION];
};

#endif