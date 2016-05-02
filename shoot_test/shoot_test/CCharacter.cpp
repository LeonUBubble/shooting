#include "CCharacter.h"

#include <fstream>

using namespace std;
CCharacter::CCharacter(const char* filename, CGame* game, int suit, float x_i, float y_i)
{
	cGame = game;

	x = x_i;
	y = y_i;

	cModel = new MilkshapeModel();
	if(cModel->loadModelData(filename) == false)
	{
		MessageBox(NULL, "Couldn't load the model","Error",MB_OK | MB_ICONERROR);
		exit(0);

	}
	if(cGame->CharacterType == PIRATE)
	{
		cModel->setSuite(suit);
		cModel->addState(1,14,LOOP); 			//NINJIA_WALKING
		cModel->addState(45,59,LOOP);			//NINJIA_ATTACK
		cModel->addState(166, 173, NO_LOOP);	// NINJA_DEAD
		cModel->addState(184,205, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true); //nate n00b if visible is TRUE then collision detection is applied
								  //doesn't do anything about the actual visibility of the object

		cBehavior = AGGRESSIVE;
		cType 	  = NINJA:
	}
	else
	{
		cModel->setSuite(0);
		cModel->addState(2, 14, LOOP);			// NINJA_WALKING
		cModel->addState(112, 126,LOOP);		// NINJA_ATTACK
		cModel->addState(230, 251, NO_LOOP);	// NINJA_DEAD
		cModel->addState(292, 325, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true); //nate n00b if visible is TRUE then collision detection is applied
								  //doesn't do anything about the actual visibility of the object

		cBehavior	= AGGRESSIVE;
		cType		= PIRATE;
	}
	currentPosition[0] = x;
	currentPosition[2] = y;
	currentPosition[1] = cGame->getHMTrans(x,y)+10;//height
	setNewEndPosition();
	attackTime = (float)cGame->timer->getTicks_ms();
}
CCharacter::~CCharacter(void)
{
	delete cModel;
}
void CCharacter::Draw()
{
	switch(cBehavior)
	{
		case WANDDER:
			wander();
			break;
		case AGGRESSIVE:
			attack();
			break;
		case DEFENSIVE:
			defend();
			break;
		case DEAD:// do nothing
			break;
		default:
			break;
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(currentPosition[0],currentPosition[1],currentPosition[2]);
	glRotatef(rotation,0,1,0);
	
	//dwarf model is bigger than the ninja, so needs scaling
	if (cGame->CharacterType == NINJA)
		glScalef(0.18, 0.2, 0.18);

	//MUST call this function for updating collision detection matrices
	//this function must be called after ALL tranformations are applied
	cModel->updateTransfMatrix();

	//debugging purposes
	cModel->draw();

	glPopMatrix();
}
void CCharacter::die()
{
	cModel->setState(NINJA_DEAD);
	cModel->setVisible(false);
	cBehavior = DEAD;
	cGame->numEnemiesKilled++;
	//FSOUND_PlaySound (FSOUND_FREE,cGame->g_death);
}
void CCharacter::defend(){
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x,cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);

	//decide whether we've reached our destination point
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();// get the lengh between the enemy and player
	if(checkLength < ATTACK_RADIUS)
	{
		cModel->setState(NINJA_ATTACK);
		if (cGame->timer->getTicks_ms() - attackTime > ATTACK_TIME)
		{
			cGame->CharacterHealth -= 10;
			attackTime = (float)cGame->timer->getTicks_mS();
			//FSOUND_PlaySound (FSOUND_FREE,cGame->g_attack);
		}
	}
	else	
		cModel->setState(NINJA_IDLE);
	// make the enemy look at the camera;
	Vec3d newDirection = (currentPosition - cameraPosition);
	newDirection.normalize();
	if(newDirection[2]>=0)// to identify the direction of rotation
	{
		rotation = 90 - 180/PI * acosf((float)newDirection[0]);
	}
	else rotation = 90 + 180/PI * acosf((float)newDirection[0]);

}
void CCharacter::setNewEndPosition()
{
	if(cGame->CharacterType = PIRATE)
	{
		endPosition[0] = 200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[2] = 200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[1] = cGame->getHMTrans((float)endPosition[0],(float)endPosition[2]) + 10;
	}
	
	else
	{
		endPosition[0] = -200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[2] = -200+((float)rand() / RAND_MAX - 0.5) * MAP_SIZE / 4;
		endPosition[1] = cGame->getHMTrans((float)endPosition[0],(float)endPosition[2]) + 10;
	}
	
	startPosition = currentPosition;
	startTime = (float)cGame->timer->getTicks_ms();
}