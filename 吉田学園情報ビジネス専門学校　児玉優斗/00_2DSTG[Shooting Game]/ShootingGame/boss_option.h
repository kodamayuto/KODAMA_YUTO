//=============================================================================
//
// �{�X���� [boss_option.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BOSS_OPTION_H_
#define _BOSS_OPTION_H_

#include "main.h"
#include"game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define BOSS_OPTION_TEXTURE "data/TEXTURE/Draw005Fryer1.png"

#define BOSS_OPTION_POLYGON_SIZE (20)

#define BOSS_OPTION_COLOR_RED (255)
#define BOSS_OPTION_COLOR_GREEN (255)
#define BOSS_OPTION_COLOR_BLUE (255)
#define BOSS_OPTION_COLOR_ALPHA (255)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	bool bUse;				//�g�p�̉�
	int nCounterBullet;		//�G�̒e�����p
}BOSS_OPTION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBossOption(void);
void UninitBossOption(void);
void UpdateBossOption(void);
void DrawBossOption(void);
void SetBossOption(D3DXVECTOR3 pos,D3DXVECTOR3 move);

#endif
