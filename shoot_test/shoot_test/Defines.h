#pragma once 

#define		CAMERASPEED			0.025f			// ����ٶ�
#define		MAP_SIZE			1024
#define		STEP_SIZE			16				// ���Ƹ߳�ͼ�ķֱ��� 
#define		HM_DISPLACEMENT		10				// �������Ҫ�����ڸ��ڸ߳�ͼһ��ֵ���ܱȽϺõ���ʾ
#define		NUM_TREES			10
#define		TREE_DRAW_DIST		100000

#define		SHOT_STEP			0.4
#define		SHOOT_TIME			150
#define		CROSS_RADIUS		15

#define		TEXT_TIME			40

#define		MAX_ENEMIES			5				
#define		CH					3				// ��Χ����z�������ŵı���

#define		NO_ANIMATION		-1
#define		NO_LOOP				0
#define		LOOP				1

#define		STAR_DRAW_AFTER		2*SHOT_STEP

#define		DEST_RADIUS			20				// �����ж�NPC�Ƿ񵽴�������Ŀ��㣬Ȼ�����Ǿ�Ҫ��Ŀ����
#define		ATTACK_RADIUS		40				// �����ж�NPC�Ƿ񵽴��˹�������
#define		ATTACK_TIME			1000			// ����ʱ������������֮�����и�ʱ���

// ״̬�����ڶ�ȡ�����������ݣ�
enum {NINJA_WALKING, NINJA_ATTACK, NINJA_DEAD, NINJA_IDLE};

// For some reason this isn't defined anywhere else, needed to make texture borders disappear.
#ifndef		GL_CLAMP_TO_EDGE
#define		GL_CLAMP_TO_EDGE        0x812F
#endif

//��Ϸ״̬��
enum {GAMESTATE_LOADING, GAMESTATE_SPLASH_START, GAMESTATE_SPLASH_ABOUT, GAMESTATE_SPLASH_EXIT, GAMESTATE_ABOUT, GAMESTATE_SELECT_NINJA, 
	  GAMESTATE_SELECT_PIRATE, GAMESTATE_PLAY, GAMESTATE_DEBUG, GAMESTATE_END}; 
enum {YOU_LOSE, YOU_WIN};

// ����״̬��������Ϸ���ж�����ô�ߣ�
enum {PIRATE, NINJA};
enum {WANDER, DEFENSIVE, AGGRESSIVE, DEAD}; 
