#include "PlayInfo3PV.h"
#include "MeshBuilder.h"

CPlayInfo3PV::CPlayInfo3PV(void)
	: theAvatarMesh(NULL)
	, jumpspeed(0)
{
	Init();
}


CPlayInfo3PV::~CPlayInfo3PV(void)
{
	if (theAvatarMesh)
	{
		delete theAvatarMesh;
		theAvatarMesh = NULL;
	}
}

// Initialise this class instance
void CPlayInfo3PV::Init(void)
{
	curPosition.Set( 0, -10, 0);
	curDirection.Set( 0, 0, 1 );
	curUp.Set(0, 1, 0);


	// Initialise the Avatar's movement flags
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}
}

// Set Model
bool CPlayInfo3PV::SetModel( Mesh* theAvatarMesh )
{
	this->theAvatarMesh = theAvatarMesh;
	if (this->theAvatarMesh == NULL)
		return false;

	return true;
}

// Returns true if the player is on ground
bool CPlayInfo3PV::isOnGround(void)
{
	return true;
}

// Returns true if the player is jumping upwards
bool CPlayInfo3PV::isJumpUpwards(void)
{
	return true;
}

// Returns true if the player is on freefall
bool CPlayInfo3PV::isFreeFall(void)
{
	return true;
}

// Set the player's status to free fall mode
void CPlayInfo3PV::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void CPlayInfo3PV::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true)
	{
		jumpspeed = 15;
	}
}

// Set position x of the player
void CPlayInfo3PV::SetPos_x(float pos_x)
{
	curPosition.x = pos_x;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_y(float pos_y)
{
	curPosition.y = pos_y;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_z(float pos_z)
{
	curPosition.z = pos_z;
}

// Set Jumpspeed of the player
void CPlayInfo3PV::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

// Stop the player's movement
void CPlayInfo3PV::SetToStop(void)
{
	jumpspeed = 0;
}

/********************************************************************************
 Hero Move Up Down
 ********************************************************************************/
void CPlayInfo3PV::MoveFrontBack(const bool mode, const float timeDiff)
{
	Vector3 tempTarget = curPosition + curDirection;
	tempTarget.y = curPosition.y;
	Vector3 tempDir = (tempTarget - curPosition).Normalized();
	if (mode) // Move backwards
	{
		curPosition -= tempDir * (CAMERA_SPEED * timeDiff);
		//curPosition.z = curPosition.z - (int) (200.0f * timeDiff);
	}
	else // Move forward
	{
		curPosition += tempDir * (CAMERA_SPEED * timeDiff);
		//curPosition.z = curPosition.z + (int) (200.0f * timeDiff);
	}
}

/********************************************************************************
 Hero Move Left Right
 ********************************************************************************/
void CPlayInfo3PV::MoveLeftRight(const bool mode, const float timeDiff)
{
	Mtx44 rotation;
	rotation.SetToRotation(90, 0, 1, 0);
	// Dir without moving y axis
	Vector3 tempTarget = curPosition + curDirection;
	tempTarget.y = curPosition.y;
	Vector3 tempDir = (tempTarget - curPosition).Normalized();

	Vector3 right = rotation * tempDir;
	if (mode)
	{
		curPosition += right * (CAMERA_SPEED * timeDiff);
		//curPosition.x = curPosition.x + (int) (200.0f * timeDiff);
	}
	else
	{
		curPosition -= right * (CAMERA_SPEED * timeDiff);
		//curPosition.x = curPosition.x - (int) (200.0f * timeDiff);
	}
}

void CPlayInfo3PV::MoveUpDown(const bool mode, const float timeDiff)
{
	if (mode) // Move up
	{
		curPosition.y += CAMERA_SPEED * timeDiff;
	}
	else
	{
		curPosition.y -= CAMERA_SPEED * timeDiff;
	}
}


// Get position x of the player
float CPlayInfo3PV::GetPos_x(void)
{
	return curPosition.x;
}

// Get position y of the player
float CPlayInfo3PV::GetPos_y(void)
{
	return curPosition.y;
}

// Get position y of the player
float CPlayInfo3PV::GetPos_z(void)
{
	return curPosition.z;
}

// Get position of the player
Vector3 CPlayInfo3PV::GetPosition()
{
	return curPosition;
}

// Get direction of the player
Vector3 CPlayInfo3PV::GetDirection()
{
	return curDirection;
}

// Get Jumpspeed of the player
int CPlayInfo3PV::GetJumpspeed(void)
{
	return jumpspeed;
}

// Update Jump Upwards
void CPlayInfo3PV::UpdateJumpUpwards()
{
	curPosition.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
	}
}

// Update FreeFall
void CPlayInfo3PV::UpdateFreeFall()
{
	curPosition.y += jumpspeed;
	jumpspeed += 1;
}

// Constrain the position of the Hero to within the border
void CPlayInfo3PV::ConstrainHero(const int leftBorder, const int rightBorder, 
								  const int topBorder, const int bottomBorder, 
								  float timeDiff)
{
	if (curPosition.x < leftBorder)
	{
		curPosition.x = leftBorder;
	}
	else if (curPosition.x > rightBorder)
	{
		curPosition.x = rightBorder;
	}

	if (curPosition.y < topBorder)
		curPosition.y = topBorder;
	else if (curPosition.y > bottomBorder)
		curPosition.y = bottomBorder;
}


/********************************************************************************
 Update Movement
 ********************************************************************************/
void CPlayInfo3PV::UpdateMovement(const unsigned char key, const bool status)
{
	myKeys[key] = status;
}

/********************************************************************************
 Update
 ********************************************************************************/
void CPlayInfo3PV::Update(double dt)
{
	// WASD movement
	if ( myKeys['w'] == true)
	{
		MoveFrontBack( false, dt );
	}
	else
	{
//		MoveVel_W = 0.0f;
	}
	if (myKeys['s'] == true)
	{
		MoveFrontBack( true, dt );
	}
	else
	{
//		MoveVel_S = 0.0f;
	}
	if (myKeys['a'] == true)
	{
		MoveLeftRight( true, dt );
	}
	else
	{
//		MoveVel_A = 0.0f;
	}
	if (myKeys['d'] == true)
	{
		MoveLeftRight( false, dt );
	}
	else
	{
//		MoveVel_D = 0.0f;
	}

	if (myKeys['q'])
	{
		MoveUpDown(true, dt);
	}
	if (myKeys['e'])
	{
		MoveUpDown(false, dt);
	}

	// Rotation
	/*
	if ( myKeys[VK_UP] == true)
	{
		LookUp( dt );
	}
	if (myKeys[VK_DOWN] == true)
	{
		LookUp( -dt );
	}
	if (myKeys[VK_LEFT] == true)
	{
		TurnLeft( -dt );
	}
	if (myKeys[VK_RIGHT] == true)
	{
		TurnRight( dt );
	}

	// Jump
	if (myKeys[32] == true)
	{
		Jump( dt );
		myKeys[32]	= false;
	}
	UpdateJump(dt);

	//Update the camera direction based on mouse move
	// left-right rotate
	if ( Application::camera_yaw != 0 )
		Yaw( dt );
	if ( Application::camera_pitch != 0 )
		Pitch( dt );

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	*/
}

void CPlayInfo3PV::UpdateDir(float yaw, float pitch)
{
	// Yaw
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	curDirection = rotation * curDirection;
	Vector3 right = curDirection.Cross(curUp);
	right.y = 0;
	right.Normalize();
	curUp = right.Cross(curDirection).Normalized();

	// Pitch
	//rotation.SetToRotation(pitch, 1, 0, 0);

	right = curDirection.Cross(curUp);
	right.y = 0;
	right.Normalize();
	curUp = right.Cross(curDirection).Normalized();
	rotation.SetToRotation(pitch, right.x, right.y, right.z);

	curDirection = rotation * curDirection;
}
