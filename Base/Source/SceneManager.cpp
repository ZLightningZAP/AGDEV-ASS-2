#include "SceneManager.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

CSceneManager::CSceneManager(void)
	: m_cMinimap(NULL)
	, m_window_width(800)
	, m_window_height(600)
	, m_cAvatar(NULL)
	, m_cSceneGraph(NULL)
	, m_cSpatialPartition(NULL)
	, m_ProjectileManager(NULL)
	, m_treelist(NULL)
	, m_projlist(NULL)
	, m_enemylist(NULL)
{
}

CSceneManager::CSceneManager(const int m_window_width, const int m_window_height)
	: m_cMinimap(NULL)
	, m_cAvatar(NULL)
	, m_cSceneGraph(NULL)
	, m_cSpatialPartition(NULL)
	, m_ProjectileManager(NULL)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
	this->theGSM = Application::S_GSM;
}

CSceneManager::~CSceneManager(void)
{
	if (m_cSpatialPartition)
	{
		delete m_cSpatialPartition;
		m_cSpatialPartition = NULL;
	}
	if (m_cSceneGraph)
	{
		delete m_cSceneGraph;
		m_cSceneGraph = NULL;
	}
	/*if (m_cAvatar)
	{
	delete m_cAvatar;
	m_cAvatar = NULL;
	}*/
	if (m_cMinimap)
	{
		delete m_cMinimap;
		m_cMinimap = NULL;
	}
	if (m_ProjectileManager)
	{
		delete m_ProjectileManager;
		m_ProjectileManager = NULL;
	}
	while (m_treelist.size() > 0)
	{
		if (m_treelist.back())
		{
			delete m_treelist.back();
			m_treelist.pop_back();
		}
	}
	while (m_projlist.size() > 0)
	{
		if (m_projlist.back())
		{
			delete m_projlist.back();
			m_projlist.pop_back();
		}
	}

	while (m_enemylist.size() > 0)
	{
		if (m_enemylist.back())
		{
			delete m_enemylist.back();
			m_enemylist.pop_back();
		}
	}
}

void CSceneManager::Init()
{
	srand(time(NULL));
	// Blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(1, 1, 0);
	lights[1].color.Set(1, 1, 0.5f);
	lights[1].power = 0.4f;
	//lights[1].kC = 1.f;
	//lights[1].kL = 0.01f;
	//lights[1].kQ = 0.001f;
	//lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	//lights[1].cosInner = cos(Math::DegreeToRadian(30));
	//lights[1].exponent = 3.f;
	//lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//chair.obj");//MeshBuilder::GenerateCube("cube", 1);
	meshList[GEO_OBJECT]->textureID = LoadTGA("Image//chair.tga");
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 1.f);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	//meshList[GEO_TORUS] = MeshBuilder::GenerateCylinder("torus", 36, 36, 5, 1);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("LEFT", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("RIGHT", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Grass.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("FRONT", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	// Load the ground mesh and texture
	//meshList[GEO_GRASS_DARKGREEN] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	//meshList[GEO_GRASS_DARKGREEN]->textureID = LoadTGA("Image//grass_darkgreen.tga");
	//meshList[GEO_GRASS_LIGHTGREEN] = MeshBuilder::GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	//meshList[GEO_GRASS_LIGHTGREEN]->textureID = LoadTGA("Image//grass_lightgreen.tga");

	//Load all the objects into the scene
	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ("Player", "OBJ//Character.obj");
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Character.tga");
	meshList[GEO_GUN] = MeshBuilder::GenerateOBJ("Gun", "OBJ//Gun.obj");
	meshList[GEO_GUN]->textureID = LoadTGA("Image//Gun.tga");

	//Enemy High Mid Low Res Init
	meshList[GEO_ENEMY] = MeshBuilder::GenerateOBJ("Santa", "OBJ//Santa.obj");
	meshList[GEO_ENEMY]->textureID = LoadTGA("Image//Santa.tga");
	meshList[GEO_ENEMY_RES_MID] = MeshBuilder::GenerateOBJ("Santa", "OBJ//SantaMidRes.obj");
	meshList[GEO_ENEMY_RES_MID]->textureID = LoadTGA("Image//Santa.tga");
	meshList[GEO_ENEMY_RES_LOW] = MeshBuilder::GenerateOBJ("Santa", "OBJ//SantaLowRes.obj");
	meshList[GEO_ENEMY_RES_LOW]->textureID = LoadTGA("Image//Santa.tga");
	
	//TreeTrunk High Mid Low Res Init
	meshList[GEO_TREETRUNK] = MeshBuilder::GenerateOBJ("Treetrunk", "OBJ//Wood.obj");
	meshList[GEO_TREETRUNK]->textureID = LoadTGA("Image//TreeWood.tga");

	//TreeLeaf High Mid Low Res Init
	meshList[GEO_TREELEAF] = MeshBuilder::GenerateOBJ("Treeleaf", "OBJ//Leaf.obj");
	meshList[GEO_TREELEAF]->textureID = LoadTGA("Image//Treeleaf.tga");

	meshList[GEO_RAY] = MeshBuilder::GenerateRay("Bullet ray", 10.f);

	// Load the texture for minimap
	m_cMinimap = new CMinimap();
	m_cMinimap->SetBackground(MeshBuilder::GenerateMinimap("MINIMAP", Color(1, 1, 1), 1.f));
	m_cMinimap->GetBackground()->textureID = LoadTGA("Image//Grass.tga");
	m_cMinimap->SetBorder(MeshBuilder::GenerateMinimapBorder("MINIMAPBORDER", Color(0, 1, 0), 1.f));
	m_cMinimap->SetAvatar(MeshBuilder::GenerateMinimapAvatar("MINIMAPAVATAR", Color(0, 1, 0), 1.f));

	// Initialise and load a model into third person view's avatar
	m_cAvatar = new CPlayInfo3PV();
	m_cAvatar->SetModel(meshList[GEO_PLAYER]);

	// Create tree
	/*CTree* tree = new CTree();
	tree->Init(meshList[GEO_TREETRUNK], meshList[GEO_TREELEAF], Vector3(0, -10, 0));
	m_treelist.push_back(tree);*/

	for (int i = TreeMinValue; i != TreeMaxValue; i += TreeDistance)
	{
		for (int k = TreeMinValue; k != TreeMaxValue; k += TreeDistance)
		{
			CTree* tree = new CTree();
			tree->Init(meshList[GEO_TREETRUNK], meshList[GEO_TREELEAF], Vector3(i, -10, k));
			m_treelist.push_back(tree);
		}
	}

	Mesh* resList[LevelOfDetail::NUM_RESOLUTION] =
	{
		meshList[GEO_ENEMY_RES_LOW],
		meshList[GEO_ENEMY_RES_MID],
		meshList[GEO_ENEMY],
	};

	for (int g = 0; g < EnemyTopLeft; g++)
	{
		CEnemy* enemy = new CEnemy();
		int randomx = rand() % 300 + 20;
		int randomz = rand() % 300 + 20;
		enemy->Init(meshList[GEO_ENEMY], Vector3(randomx, -10, randomz));
		//enemy->SetRender(false);
		enemy->InitLod(resList);
		m_enemylist.push_back(enemy);
	}

	for (int g = 0; g < EnemyTopRight; g++)
	{
		CEnemy* enemy = new CEnemy();
		int randomx = rand() % 300 + 20;
		int randomz = rand() % 300 + 20;
		enemy->Init(meshList[GEO_ENEMY], Vector3(-randomx, -10, randomz));
		//enemy->SetRender(false);
		enemy->InitLod(resList);
		m_enemylist.push_back(enemy);
	}

	for (int g = 0; g < EnemyBottomLeft; g++)
	{
		CEnemy* enemy = new CEnemy();
		int randomx = rand() % 300 + 20;
		int randomz = rand() % 300 + 20;
		enemy->Init(meshList[GEO_ENEMY], Vector3(randomx, -10, -randomz));
		//enemy->SetRender(false);
		enemy->InitLod(resList);
		m_enemylist.push_back(enemy);
	}

	for (int g = 0; g < EnemyBottomRight; g++)
	{
		CEnemy* enemy = new CEnemy();
		int randomx = rand() % 300 + 20;
		int randomz = rand() % 300 + 20;
		enemy->Init(meshList[GEO_ENEMY], Vector3(-randomx, -10, -randomz));
		//enemy->SetRender(false);
		enemy->InitLod(resList);
		m_enemylist.push_back(enemy);
	}

	// Create projectiles
	for (int i = 0; i < 100; ++i)
	{
		CProjectile* p = new CProjectile();
		m_projlist.push_back(p);
	}

	// Create scenegraph
	InitSceneGraph();

	// Create Spatial Partition
	InitSpatialPartition();
	AddToSpatialPartition();

	m_ProjectileManager = new CProjectileManager();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	rotateAngle = 0;

	tempscore = 0;

	bLightEnabled = true;
}

void CSceneManager::Update(double dt)
{
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('8'))
	{
		bLightEnabled = true;
	}
	else if (Application::IsKeyPressed('9'))
	{
		bLightEnabled = false;
	}

	if (Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(10.f * dt);
	if (Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(10.f * dt);
	if (Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(10.f * dt);
	if (Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(10.f * dt);
	if (Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(10.f * dt);
	if (Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(10.f * dt);

	rotateAngle -= Application::camera_yaw;// += (float)(10 * dt);
	//m_cSceneGraph->GetNode(P_BOTTOM)->ApplyRotate(180 * dt, 0, 1, 0);
	//m_cSceneGraph->GetNode(P_TOP)->ApplyTranslate(1 * dt, 0, 0);

	m_cAvatar->Update(dt);
	camera.UpdatePosition(m_cAvatar->GetPosition(), m_cAvatar->GetDirection());
	//camera.Update(dt);
	m_cSpatialPartition->Update(camera.position, (camera.target - camera.position).Normalized());

	m_ProjectileManager->Update(dt);

	for (int i = 0; i < m_projlist.size(); ++i)
	{
		CProjectile* p = m_projlist[i];
		if (p)
		{
			p->Update(dt);
			for (int j = 0; j < m_treelist.size(); ++j)
			{
				CTree* tree = m_treelist[j];
				if (p->CObject::GetActive())
				{
					for (int k = 0; k < tree->m_treeparts.size(); ++k)
					{
						CGameObject* part = tree->m_treeparts[k];
						if (p->CObject::GetActive())
						{
							if (p->CollideWith(*part, dt))
							{
								p->Reset();
								part->Reset();
								tempscore = tempscore + 10;
								break;
							}
						}
					}
				}
				else
				{
					break;
				}
			}

			//Enemy
			for (int j = 0; j < m_enemylist.size(); ++j)
			{
				CEnemy* enemy = m_enemylist[j];
				if (enemy->CObject::GetActive())
				{
					if (p->CollideWith(*enemy, dt))
					{
						p->Reset();
						int randomx = rand() % 300 + 20;
						int randomz = rand() % 300 + 20;
						enemy->GetTransform().m_translate.Set(randomx,-10,randomz);
						enemy->Init(meshList[GEO_ENEMY], enemy->GetTransform().m_translate);
						//part->Reset();
						tempscore = tempscore + 100;
						break;
					}

				}
			}
		}
	}

	for (int j = 0; j < m_enemylist.size(); ++j)
	{
		CEnemy* enemy = m_enemylist[j];
		if (enemy->CObject::GetActive())
		{
			enemy->Update(dt, m_cAvatar->GetPosition());
			enemy->UpdateLod(m_cAvatar->GetPosition());
		}
	}

	timer = timer - dt;

	if (timer <= 0)
	{
		CGameStateManager::highscore = tempscore;
		theGSM->ChangeState(CMenuState::Instance());
	}

	fps = (float)(1.f / dt);
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneManager::UpdateCameraStatus(const unsigned char key, const bool status)
{
	camera.UpdateStatus(key, status);
}

void CSceneManager::UpdateAvatarStatus(const unsigned char key, const bool status)
{
	m_cAvatar->UpdateMovement(key, status);
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneManager::UpdateWeaponStatus(const unsigned char key)
{
	if (key == WA_FIRE)
	{
		// Add a bullet object which starts at the camera position and moves in the camera's direction
		//m_ProjectileManager->AddProjectile(m_cAvatar->GetPosition(), m_cAvatar->GetDirection(), 500.f); // Shoot by avatar
		//m_ProjectileManager->AddProjectile(camera.position, (camera.target - camera.position).Normalized(), 50.f); // Shoot by camera

		CProjectile* p = fetchProj();
		if (p)
		{
			CTransform* transform = new CTransform();
			transform->Init(m_cAvatar->GetPosition(), Vector3::ZERO_VECTOR, Vector3(1, 1, 1));
			p->Init(m_cAvatar->GetDirection(), 500.f, meshList[GEO_SPHERE], transform);
			p->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_MIDDLE, true);
		}
	}
	else if (key == WA_FIRE_SECONDARY)
	{
		//m_ProjectileManager->AddRayProjectile(m_cAvatar->GetPosition(), m_cAvatar->GetDirection(), 500.f);
		CProjectile* p = fetchProj();
		if (p)
		{
			CTransform* transform = new CTransform();
			transform->Init(m_cAvatar->GetPosition(), Vector3::ZERO_VECTOR, Vector3(1, 1, 1));
			p->Init(m_cAvatar->GetDirection(), 500.f, meshList[GEO_RAY], transform);
			p->CCollider::Init(CCollider::CT_AABB, *transform, CCollider::X_MIDDLE, CCollider::Y_MIDDLE, true);
		}
	}
}

/********************************************************************************
 Render text onto the screen with reference position in the middle of the image
 ********************************************************************************/
void CSceneManager::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

/********************************************************************************
 Render text onto the screen
 ********************************************************************************/
void CSceneManager::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	//ortho.SetToOrtho(0, m_window_width, 0, m_window_height, -10, 10);
	ortho.SetToOrtho(0, m_window_width, 0, m_window_height, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation((i*0.5f) + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

/********************************************************************************
 Render a mesh in 2D
 ********************************************************************************/
void CSceneManager::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	if (rotate)
		modelStack.Rotate(rotateAngle, 0, 0, 1);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

/********************************************************************************
 Render a mesh
 ********************************************************************************/
void CSceneManager::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

/********************************************************************************
 Render mobile objects
 ********************************************************************************/
void CSceneManager::RenderGUI()
{
	// Render the crosshair
	RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);

	// Render the crosshair
	// Note that Ortho is set to this size -> 	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	RenderMeshIn2D(m_cMinimap->GetAvatar(), false, 20.0f, 68, -48, true);
	RenderMeshIn2D(m_cMinimap->GetBorder(), false, 20.0f, 68, -48);
	RenderMeshIn2D(m_cMinimap->GetBackground(), false, 20.0f, 68, -48);

	//On screen text
	std::ostringstream ss, projInfo, scoresetting;
	/*ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 30, 0, 6);*/

	projInfo << "Projectiles: " << m_ProjectileManager->NumOfActiveProjectile;
	RenderTextOnScreen(meshList[GEO_TEXT], projInfo.str(), Color(0, 1, 0), 30, 200, 6);

	ss.precision(3);
	ss << "Time Left: " << timer;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 40, 250, 550);

	scoresetting.precision(5);
	scoresetting << "Score: " << tempscore;
	RenderTextOnScreen(meshList[GEO_TEXT], scoresetting.str(), Color(1, 0, 0), 40, 300, 500);



	//RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);
}

/********************************************************************************
 Render mobile objects
 ********************************************************************************/
void CSceneManager::RenderMobileObjects()
{
	// Render LightBall
	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	// Render scene graph
	//m_cSceneGraph->Draw(this);

	// Render projectiles
	for (int i = 0; i < m_projlist.size(); ++i)
	{
		CProjectile* p = m_projlist[i];
		RenderGameObject(p, false, false);
	}

	/*for (int i = 0; i < m_ProjectileManager->GetMaxNumberOfProjectiles(); ++i)
	{
		if (m_ProjectileManager->IsActive(i))
		{
			CProjectile2* p = m_ProjectileManager->theListOfProjectiles[i];
			float theta = Math::RadianToDegree(atan2(m_ProjectileManager->theListOfProjectiles[i]->GetDirection().x, m_ProjectileManager->theListOfProjectiles[i]->GetDirection().z));
			switch (p->GetType())
			{
			case CProjectile2::PROJ_TYPE_DISCRETE:
			{
				Vector3 pos = p->GetPosition();
				modelStack.PushMatrix();
				modelStack.Translate(pos.x, pos.y, pos.z);
				RenderMesh(meshList[GEO_SPHERE], false);
				modelStack.PopMatrix();
			}
			break;
			case CProjectile2::PROJ_TYPE_RAY:
			{
				Vector3 pos = p->GetPosition();
				modelStack.PushMatrix();
				modelStack.Translate(pos.x, pos.y, pos.z);
				glLineWidth(5.f);
				modelStack.Rotate(theta, 0, 1, 0);
				RenderMesh(meshList[GEO_RAY], false);
				glLineWidth(1.f);
				modelStack.PopMatrix();
			}
			break;
			}
		}
	}*/

	// Render the Avatar
	modelStack.PushMatrix();
	modelStack.Translate(m_cAvatar->GetPos_x(), m_cAvatar->GetPos_y(), m_cAvatar->GetPos_z());
	//modelStack.Rotate(rotateAngle, 0, 1, 0);
	RenderMesh(m_cAvatar->theAvatarMesh, false);
	modelStack.PopMatrix();

	//Render the gun with the player
	modelStack.PushMatrix();
	modelStack.Translate(m_cAvatar->GetPos_x() - 1.7, m_cAvatar->GetPos_y() + 4, m_cAvatar->GetPos_z() + 0.8);
	RenderMesh(meshList[GEO_GUN], false);
	modelStack.PopMatrix();
}

/********************************************************************************
 Render the lights in this scene
 ********************************************************************************/
void CSceneManager::RenderFixedObjects()
{
	//RenderMesh(meshList[GEO_AXES], false);

	/*modelStack.PushMatrix();
	modelStack.Translate(-20, 0, -20);
	RenderMesh(meshList[GEO_OBJECT], false);
	modelStack.PopMatrix();*/
	//
	//modelStack.PushMatrix();
	//modelStack.Translate(20, 0, -20);
	//RenderMesh(meshList[GEO_OBJECT], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Scale(10, 10, 10);
	////RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	//RenderText(meshList[GEO_TEXT], "DM2240 AGDEV", Color(0, 1, 0));
	//modelStack.PopMatrix();

	for (int i = 0; i < m_treelist.size(); ++i)
	{
		CTree* tree = m_treelist[i];
		for (int j = 0; j < tree->m_treeparts.size(); ++j)
		{
			RenderGameObject(tree->m_treeparts[j], false, false);
		}
	}

	for (int i = 0; i < m_enemylist.size(); ++i)
	{
		CEnemy* enemy = m_enemylist[i];
		RenderGameObject(enemy, false, false);
		
	}

	/*for (int i = 0; i < ObjectList.size(); i++)
	{
		//First layer
		modelStack.PushMatrix();
		//modelStack.Translate(x, (y + i) * 10, z);
		RenderMesh(ObjectList[i]->theModel->GetMesh(), false);
		modelStack.PopMatrix();
	}*/
	//RenderTree(0, 0, 0);
}

/********************************************************************************
 Render the lights in this scene
 ********************************************************************************/
void CSceneManager::RenderLights()
{
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	if (lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}
}

/********************************************************************************
 Render the ground in this scene
 ********************************************************************************/
void CSceneManager::RenderGround()
{
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(100.0f, 100.0f, 100.0f);

	for (int x = 0; x < 10; x++)
	{
		for (int z = 0; z < 10; z++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(x - 5.0f, z - 5.0f, 0.0f);
			RenderMesh(meshList[GEO_BOTTOM], false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();

	//// Spatial Partition render
	//modelStack.PushMatrix();
	//modelStack.Rotate(-90, 1, 0, 0);
	//modelStack.Translate(0, 0, -9);
	//modelStack.Rotate(-90, 0, 0, 1);

	//for (int col = 0; col < m_cSpatialPartition->GetxNumOfGrid(); ++col)
	//{
	//	for (int row = 0; row < m_cSpatialPartition->GetyNumOfGrid(); ++row)
	//	{
	//		if (m_cSpatialPartition->GetGridMesh(col, row))
	//		{
	//			modelStack.PushMatrix();
	//			modelStack.Translate(m_cSpatialPartition->xGridSize * col, m_cSpatialPartition->yGridSize * row, 0.f);
	//			RenderMesh(m_cSpatialPartition->GetGridMesh(col, row), false);
	//			modelStack.PopMatrix();
	//		}
	//	}
	//}
	//modelStack.PopMatrix();
}

/********************************************************************************
 Render the skybox in this scene
 ********************************************************************************/
void CSceneManager::RenderSkybox()
{
	//left
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void CSceneManager::InitSceneGraph()
{
	const Vector3 SIZE(3, 3, 3);
	m_cSceneGraph = new CSceneNode(P_BOTTOM);
	CModel *newModel = new CModel();
	newModel->Init();
	CTransform2 *newTransform = new CTransform2();
	newTransform->SetTranslate2(10, 0, 0);
	newTransform->SetScale(SIZE.x, SIZE.y, SIZE.z);
	cout << m_cSceneGraph->SetNode(newTransform, newModel) << endl;

	/*newModel = new CModel();
	newModel->Init();
	newTransform = new CTransform2();
	newTransform->SetTranslate2(0, 5, 0);
	newTransform->AddToTranslate(-10, 0, 0);
	newTransform->SetScale(2,2,2);
	cout << m_cSceneGraph->AddChild(P_TOP, newTransform, newModel) << endl;*/
}

void CSceneManager::InitSpatialPartition()
{
	static const float S_GRID_SIZE = 100.f;
	m_cSpatialPartition = new CSpatialPartition();
	m_cSpatialPartition->Init(S_GRID_SIZE, S_GRID_SIZE, 3, 3);
	for (int col = 0; col < m_cSpatialPartition->GetxNumOfGrid(); ++col)
	{
		for (int row = 0; row < m_cSpatialPartition->GetyNumOfGrid(); ++row)
		{
			m_cSpatialPartition->SetGridMesh(col, row, MeshBuilder::GenerateQuad("Grid mesh", Color(1.f / col, 1.f / row, 1.f / (row * col)), S_GRID_SIZE));
		}
	}
	m_cSpatialPartition->PrintSelf();
}

void CSceneManager::AddToSpatialPartition()
{
	m_cSpatialPartition->AddObject(m_cSceneGraph);
}

void CSceneManager::UpdateCharDir(float yaw, float pitch)
{
	m_cAvatar->UpdateDir(-yaw, -pitch);
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Set up the view
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderLights();
	RenderGround();
	RenderSkybox();
	RenderFixedObjects();
	RenderMobileObjects();

	RenderGUI();
}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CSceneManager::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void CSceneManager::PreRendering(Vector3 translate, Vector3 rotate, Vector3 scale, bool enableLight)
{
	modelStack.PushMatrix();
	modelStack.Translate(translate.x, translate.y, translate.z);
	modelStack.Rotate(rotate.x, 1, 0, 0);
	modelStack.Rotate(rotate.y, 0, 1, 0);
	modelStack.Rotate(rotate.z, 0, 0, 1);
	modelStack.Scale(scale.x, scale.y, scale.z);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
}

void CSceneManager::PostRendering()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	modelStack.PopMatrix();
}

bool CSceneManager::CheckCollision(Vector3 first, CSceneNode* second)
{
	if ((first.x < second->GetTopLeft().x + second->size.x * 0.5 && first.x > second->GetBottomRight().x - second->size.x * 0.5) &&
		(first.y < second->GetTopLeft().y + second->size.y * 0.5 && first.y > second->GetBottomRight().y - second->size.y * 0.5) &&
		(first.z < second->GetTopLeft().z + second->size.z * 0.5 && first.z > second->GetBottomRight().z - second->size.z * 0.5))
		return true;
	return false;
}

void CSceneManager::RenderGameObject(CGameObject * go, bool enableLight, bool in2D)
{
	if (go && go->GetMesh() && go->GetRender())
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->GetTransform().GetTranslate().x, go->GetTransform().GetTranslate().y, go->GetTransform().GetTranslate().z);
		modelStack.Rotate(go->GetTransform().GetRotate().x, 1, 0, 0);
		modelStack.Rotate(go->GetTransform().GetRotate().y, 0, 1, 0);
		modelStack.Rotate(go->GetTransform().GetRotate().z, 0, 0, 1);
		modelStack.Scale(go->GetTransform().GetScale().x, go->GetTransform().GetScale().y, go->GetTransform().GetScale().z);
		if (in2D)
		{
			RenderMeshIn2D(go->GetMesh(), bLightEnabled);
		}
		else
		{
			RenderMesh(go->GetMesh(), bLightEnabled);
		}
		modelStack.PopMatrix();
	}
}

CProjectile * CSceneManager::fetchProj()
{
	for (vector<CProjectile*>::iterator it = m_projlist.begin(); it != m_projlist.end(); ++it)
	{
		CProjectile* proj = *it;
		if (!proj->GetRender())
		{
			return proj;
		}
	}
	return NULL;
}