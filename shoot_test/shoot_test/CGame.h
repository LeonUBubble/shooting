#pragma once

#include "Defines.h"
#include "CAltitude.h"
#include "CTimer.h"
#include "CCamera.h"


class CTimer;
class CCamera;	
class CAltitude;

class CGame
{
public:
	CGame(void);
	~CGame(void);
	
	// ��Ϸ��������
		void handleInput();
		void keyboardInput();

	// �߳�ͼ-�ƶ�ֵ
		int getHMTrans(float x, float y);

	// ��Ϸ״̬������
		void setState(int newState);	
		void setGameOver();

	// ��Ϸͼ
		void setText(int time, GLuint mask, GLuint text);
		bool displayText();

	// ��Ϸ����
		int				currentState;		// ��Ϸ״̬������
		bool			CharacterWinLose;	// �ж��Ƿ��Ѿ�Ӯ��
		int				CharacterHealth;	// ��ҵ�����ֵ
		bool			CharacterType;		// �������
		int				numEnemiesKilled;	// �Ѿ������˶��ٵ���
		bool			gameOver;			// ��Ϸ�Ƿ��Ѿ�����
		bool			rickroll_Mode;		// this should be self-explanatory.
		volatile int	shoot_time;			// how many Gldraws a shot lasts

	// Text showing
		volatile int	text_time; //same thing for test
		GLuint			t_mask;
		GLuint			t_text;
	
	// Global game classes
		CTimer*			timer;	// Timer class
		CCamera*		camera;	// Camera	
		CAltitude*		theMap;	// Height map
};
