#pragma once

#include "Grid.h"
#include "Vector3.h"
#include "..\SceneGraph\SceneNode.h"
#include "..\Occlusion\Occlusion.h"

class CSpatialPartition
{
public:
	// Constructor
	CSpatialPartition(void);
	// Destructor
	~CSpatialPartition(void);

	// Initialise the spatial partition
	bool Init(const int xSize, const int ySize, const int xNumOfGrid, const int yNumOfGrid);
	// Get xNumOfGrid
	int GetxNumOfGrid(void);
	// Get yNumOfGrid
	int GetyNumOfGrid(void);
	// Get a particular grid
	CGrid GetGrid(const int xIndex, const int yIndex);
	// Get a particular grid's Mesh
	Mesh* GetGridMesh(const int xIndex, const int yIndex);

	// Set a particular grid's Mesh
	void SetGridMesh(const int xIndex, const int yIndex, Mesh* theGridMesh);
	// Add a new object
	void AddObject(CSceneNode* theObject);

	// Calculate the squared distance from camera to a grid's centrepoint
	float CalculateDistanceSquare(Vector3* theCameraPosition, const int xIndex, const int yIndex);
	float CalculateDistanceSquare(Vector3 pos, Vector3 dir, const int xIndex, const int yIndex);

	// Check a position for collision with objects in any of the grids
	bool CheckForCollision(Vector3 pos);
	bool CheckForCollision(Vector3 pos_start, Vector3 pos_End);

	// Update the spatial partition
	void Update(Vector3 cameraPos, Vector3 cameraNormal);
	// Render the spatial partition
	void Render(Vector3* theCameraPosition = NULL);

	//PrintSelf
	void PrintSelf();

	// Variables
	CGrid* theGrid;
	int xSize;
	int ySize;
	int xGridSize;
	int yGridSize;
	int xNumOfGrid;
	int yNumOfGrid;

private:
	// Find the index of a grid which is nearest to a position
	void findNearestGrid(Vector3 pos, Vector3 dir);
	// Occlusion
	COcclusion occulusionChecker;
};
