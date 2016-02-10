#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"
#include "PlayInfo3PV.h"
#include "SceneGraph\SceneNode.h"
#include "SpatialPartition\SpatialPartition.h"
#include "Projectile\ProjectileManager.h"
#include "Tree.h"
#include "Projectile.h"
#include "Enemy.h"
#include "GameStateManager.h"


class CSceneManager : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE5,
		GEO_SPHERE6,
		GEO_SPHERE7,
		GEO_SPHERE8,
		GEO_SPHERE9,
		GEO_QUAD,
		GEO_CUBE,
		GEO_RING,
		GEO_CONE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_RAY,
		GEO_GRASS_DARKGREEN,
		GEO_GRASS_LIGHTGREEN,
		GEO_OBJECT,
		GEO_TEXT,
		GEO_MAINMENU,
		GEO_SPLASH,
		GEO_INSTRUCTIONS,
		GEO_PLAYER,
		GEO_TREETRUNK,
		GEO_TREELEAF,
		GEO_ENEMY,
		GEO_GUN,
		NUM_GEOMETRY,
	};

	enum SCENEGRAPH_PARTS
	{
		P_BOTTOM,
		P_TOP,
		NUM_PARTS,
	};

public:
	static double timer;
	static float SKYBOXSIZE;
	static int EnemyTopLeft;
	static int EnemyTopRight;
	static int EnemyBottomLeft;
	static int EnemyBottomRight;
	static int TreeMinValue;
	static int TreeMaxValue;
	static int TreeDistance;

	CSceneManager(void);
	CSceneManager(const int m_window_width, const int m_window_height);
	~CSceneManager(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Avatar status
	virtual void UpdateAvatarStatus(const unsigned char key, const bool status = true);
	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	// Update character direction
	void UpdateCharDir(float yaw, float pitch);
	virtual void Render();
	virtual void Exit();
	bool CheckCollision(Vector3 first, CSceneNode* second);

	// Low level render tools
	void PreRendering(Vector3 translate, Vector3 rotate, Vector3 scale, bool enableLight);
	void PostRendering();

	// Low level render tools
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size = 1.0f, float x = 0.0f, float y = 0.0f, bool rotate = false);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void CSceneManager::RenderGameObject(CGameObject * go, bool enableLight, bool in2D);

	// Render the main components of this scene
	void RenderGUI();
	void RenderMobileObjects();
	void RenderFixedObjects();
	void RenderLights();
	void RenderGround();
	void RenderSkybox();
	//void RenderTree(int x, int y, int z);

	// Init features
	void InitSceneGraph();
	void InitSpatialPartition();
	void AddToSpatialPartition();

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_FIRE,
		WA_FIRE_SECONDARY,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	//Vector Game Object
	vector<CSceneNode*> ObjectList;
	vector<CSceneNode*> LeafList;

	// Handler to the camera
	Camera3 camera;

	// Rotation angle for use with the model stack
	float rotateAngle;

	// Matrices for Model, View and Projection stack
	MS modelStack;
	MS viewStack;
	MS projectionStack;

	int tempscore;
	

	// Window size
	int m_window_width;
	int m_window_height;

	Light lights[2];
	bool bLightEnabled;

	float fps;

	// Handle to the minimap
	CMinimap* m_cMinimap;

	// Handle to 3rd Person View's avatar
	CPlayInfo3PV* m_cAvatar;

	// Scene graph
	CSceneNode* m_cSceneGraph;
	
	// Spatial Partition
	CSpatialPartition* m_cSpatialPartition;

	// Projectile
	CProjectileManager* m_ProjectileManager;

	// Tree
	vector<CTree*> m_treelist;

	// Projectile
	vector<CProjectile*> m_projlist;
	CProjectile* fetchProj();

	//Enemy
	vector<CEnemy*> m_enemylist;

	CGameStateManager* theGSM;
};
#endif