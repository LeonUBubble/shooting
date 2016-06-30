#include "CFigure.h"

#include <fstream>

using namespace std;

CFigure::CFigure(const char* filename, CGame* game, int suit, float x_i, float y_i)
{
	cGame = game;

	x = x_i;
	y = y_i;

	cModel = new Milkshape();
	if ( cModel->loadModelData( filename ) == false )
	{
		MessageBox( NULL, "Couldn't load the model", "Error", MB_OK | MB_ICONERROR );
		exit(0);
	}

	if (cGame->CharacterType == PIRATE) {

		cModel->setSuite(suit);
		cModel->addState(1, 14, LOOP);			// NINJA_WALKING
		cModel->addState(45,59,LOOP);			// NINJA_ATTACK
		cModel->addState(166, 173, NO_LOOP);	// NINJA_DEAD
		cModel->addState(184,205, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true); // ���visibleΪtrue����ô���ǽ��������ײ���

		cBehavior	= AGGRESSIVE;
		cType		= NINJA;

	}
	else {

		cModel->setSuite(0);
		cModel->addState(2, 14, LOOP);			// NINJA_WALKING
		cModel->addState(112, 126,LOOP);		// NINJA_ATTACK
		cModel->addState(230, 251, NO_LOOP);	// NINJA_DEAD
		cModel->addState(292, 325, LOOP);		// NINJA_IDLE
		cModel->setState(NINJA_WALKING);
		cModel->setVisible(true);  // ���visibleΪtrue����ô���ǽ��������ײ���

		cBehavior	= AGGRESSIVE;
		cType		= PIRATE;

	}

	currentPosition[0] = x;
	currentPosition[2] = y;
	currentPosition[1] = cGame->getHMTrans(x,y)+10;
	setNewEndPosition();

	attackTime = (float)cGame->timer->getTicks_mS();
}

CFigure::~CFigure(void)
{
	delete cModel;
}

void CFigure::Draw()
{
	// ���������ڸ�ʲô��ѡ����ȷ�Ļ��Ʒ�ʽ
	switch(cBehavior)
	{
		case WANDER:
			wander();
			break;
		case AGGRESSIVE:
			attack();
			break;
		case DEFENSIVE:
			defend();
			break;
		case DEAD:
			//do nothing
			break;
		default:
			break;
	}

	// ��ʽ����
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(currentPosition[0], currentPosition[1], currentPosition[2]);
	glRotatef(rotation, 0,1,0);

	//����ģ�ͱ�����ģ��Ҫ�������֣�����Ҫͨ�����ű�С
	if (cGame->CharacterType == NINJA)
		glScalef(0.18, 0.2, 0.18);

	//��ײ���֮ǰ����Ҫ���ⲿ�ֵĹ������Ѱ�Χ�о����ģ������ϵת������ͼ����ϵ
	//��Ȼ��Ҫ��֮ǰ����ת�������֮����ܹ��ó�������
	cModel->updateTransfMatrix();

	//debugging purposes
	/*cModel->drawBoundingBox();*/
	cModel->draw();

	glPopMatrix();
}

void CFigure::die()
{
	cModel->setState(NINJA_DEAD);
	cModel->setVisible(false);
	cBehavior = DEAD;
	cGame->numEnemiesKilled++;
}


void CFigure::wander()
{
	cModel->setState(NINJA_WALKING);

	lastPosition = currentPosition;		// ������Ҫ�����λ��
	
	// �ж��Ƿ��Ѿ�����Ŀ���
	Vec3d check = endPosition - currentPosition;
	if ( check.length() < DEST_RADIUS )
		setNewEndPosition();	// ����Ŀ���
	
	Vec3d delta = endPosition - startPosition;
	delta.normalize();
	float t = ((float)cGame->timer->getTicks_mS() - startTime)/80.0;
	
	currentPosition = startPosition + delta * t;
	currentPosition[1] = cGame->getHMTrans((float)currentPosition[0],(float)currentPosition[2])+9;
	
	Vec3d newDirection = (currentPosition - lastPosition);
	newDirection.normalize();

	if ( newDirection[2] >= 0 )
		rotation = -90 - 180 / PI * acosf( (float)newDirection[0] );
	else
		rotation = -90 + 180 / PI * acosf( (float)newDirection[0] );
}

void CFigure::attack()
{
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x, cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();
	if ( checkLength < ATTACK_RADIUS )
	{	
		defend();
	}
	else
		wander();
}

void CFigure::defend()
{
	Vec3d cameraPosition = Vec3d(cGame->camera->mPos.x, cGame->getHMTrans(cGame->camera->mPos.x,cGame->camera->mPos.z) + 10, cGame->camera->mPos.z);

	// �ж��Ƿ��Ѿ����﹥����Χ
	Vec3d check = currentPosition - cameraPosition;
	double checkLength = check.length();
	if ( checkLength < ATTACK_RADIUS )
	{	
		cModel->setState(NINJA_ATTACK);
		if ( cGame->timer->getTicks_mS() - attackTime > ATTACK_TIME )
		{			
			cGame->CharacterHealth -= 10;	//�����ɹ�������ֵ��10
			attackTime = (float)cGame->timer->getTicks_mS();
		}
	}
	else
		cModel->setState(NINJA_IDLE);
	
	// Ҫ��������������ӽ�
	Vec3d newDirection = (currentPosition - cameraPosition);
	newDirection.normalize();

	if ( newDirection[2] >= 0 )
		rotation = 90 - 180 / PI * acosf( (float)newDirection[0] );
	else
		rotation = 90 + 180 / PI * acosf( (float)newDirection[0] );

}

void CFigure::setNewEndPosition()
{
	if ( cGame->CharacterType == PIRATE )
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
	startTime = (float)cGame->timer->getTicks_mS();
}