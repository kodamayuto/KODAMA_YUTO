//=============================================================================
//
// �e����[bullet.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	BULLETTYPE_NONE = 0,
	BULLETTYPE_PLAYER,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 Oldpos;	//���ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//�p�x
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	float fWidth;	//��
	float Haight;	//���s
	bool bUse;		//�g�p�̉�
	int nIdxShadow;	//�e�̃C���f�b�N�X
	int nLife;		//�e�̕\������
	int nDeleteIdxNpc; //����npc�̃C���f�b�N�X
	BULLETTYPE type;	//�e�̑���
}BULLET;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move,float fWidth ,float haight, BULLETTYPE type);
void BulletErese(void);
#endif
