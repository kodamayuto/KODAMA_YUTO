//=============================================================================
//
// �G���� [enemy.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include"game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(256)	// �G�̍ő吔

#define ENEMY_TEXTURE_00 "data/TEXTURE/Draw005Fryer1.png"
#define ENEMY_TEXTURE_01 "data/TEXTURE/Draw005Fryer2.png"
#define ENEMY_TEXTURE_02 "data/TEXTURE/Draw005Fryer3.png"
#define ENEMY_TEXTURE_03 "data/TEXTURE/Draw005Fryer4.png"
#define ENEMY_TEXTURE_04 "data/TEXTURE/Draw005Fryer1_damage.png"
#define ENEMY_TEXTURE_05 "data/TEXTURE/Draw005Fryer2_damage.png"
#define ENEMY_TEXTURE_06 "data/TEXTURE/Draw005Fryer3_damage.png"
#define ENEMY_TEXTURE_07 "data/TEXTURE/Draw005Fryer4_damage.png"

#define ENEMY_POLYGON_SIZE (22)

#define ENEMY_COLOR_RED (255)
#define ENEMY_COLOR_GREEN (255)
#define ENEMY_COLOR_BLUE (255)
#define ENEMY_COLOR_ALPHA (255)

#define	MAX_TYPE_ENEMY		(8)						// �G�̎��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//��ԗ�
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ�
	ENEMYSTATE_DAMAGE,		//�_���[�W
	ENEMYSTATE_MAX			
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nType;				//�G�̃^�C�v
	bool bUse;				//�g�p�̉�
	int nLife;				//�̗�
	ENEMYSTATE state;		//�G�̏��
	int nCounterState;		//��ԊǗ��p�J�E���^�[
	int nCounterBullet;		//�G�̒e�����p
}ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nType);
ENEMY *GetEnemy(void);
int GetNumEnemy(void);
void HitEnemy(int nCntEnemy,int nDamage);
void DebugEnemyLifeDown(void);

#endif
