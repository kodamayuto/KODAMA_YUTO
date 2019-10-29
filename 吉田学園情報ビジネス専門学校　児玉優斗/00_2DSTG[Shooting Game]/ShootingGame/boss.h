//=============================================================================
//
// �{�X���� [boss.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include"game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define BOSS_TEXTURE "data/TEXTURE/Draw005Fryer1.png"
#define BOSS_DAMAGE_TEXTURE "data/TEXTURE/Draw005Fryer1_damage.png"

#define BOSS_POLYGON_SIZE (60)

#define BOSS_COLOR_RED (255)
#define BOSS_COLOR_GREEN (255)
#define BOSS_COLOR_BLUE (255)
#define BOSS_COLOR_ALPHA (255)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//��ԗ�
typedef enum
{
	BOSSSTATE_NORMAL = 0,	//�ʏ�
	BOSSSTATE_DAMAGE,		//�_���[�W
	BOSSSTATE_DEATH,		//��
	BOSSSTATE_MAX
}BOSSSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	bool bUse;				//�g�p�̉�
	int nLife;				//�̗�
	BOSSSTATE state;		//�G�̏��
	int nCounterState;		//��ԊǗ��p�J�E���^�[
	int nCounterBullet;		//�G�̒e�����p
}BOSS;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos,D3DXVECTOR3 move);
BOSS *GetBoss(void);
void HitBoss(int nDamage);

#endif
