#include "Tree.h"



CTree::CTree() : m_treeparts(NULL)
{
}


CTree::~CTree()
{
	for (int i = 0; i < m_treeparts.size(); ++i)
	{
		if (m_treeparts[i])
		{
			delete m_treeparts[i];
			m_treeparts[i] = NULL;
		}
	}
}

void CTree::Init(Mesh* trunk, Mesh* leaf, Vector3 pos)
{
	float x = pos.x, y = pos.y, z = pos.z;
	Vector3 SIZE(10, 10, 10);
	CGameObject* go;
	CTransform* transform;
	Vector3 offset;
	//GetTransform().Init(pos, Vector3::ZERO_VECTOR, Vector3(1, 1, 1));

	//First layer
	offset.Set(0, 0, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(trunk, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	//Second layer
	offset.Set(0, 10, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(trunk, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	//Third layer
	offset.Set(0, 20, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(trunk, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	//Fourth layer
	offset.Set(0, 30, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(-10, 30, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(10, 30, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(0, 30, -10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(0, 30, 10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(-10, 30, -10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(-10, 30, 10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(10, 30, -10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(10, 30, 10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	//Fifth layer
	offset.Set(0, 40, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(10, 40, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(-10, 40, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(0, 40, 10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	offset.Set(0, 40, -10);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);

	//Sixth layer
	offset.Set(0, 50, 0);
	go = new CGameObject();
	transform = new CTransform();
	transform->Init(pos + offset, Vector3::ZERO_VECTOR, SIZE);
	go->Init(leaf, transform);
	go->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_BOTTOM, true);
	m_treeparts.push_back(go);
}
