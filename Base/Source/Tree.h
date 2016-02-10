#pragma once
#include "Object\GameObject.h"
#include <vector>

using std::vector;

class CTree : public CGameObject
{
public:
	CTree();
	virtual ~CTree();

	virtual void Init(Mesh* trunk, Mesh* leaf, Vector3 pos);

	vector<CGameObject*> m_treeparts;
};

