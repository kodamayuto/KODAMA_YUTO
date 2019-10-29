//=============================================================================
//
// �e���� [bullet.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET		(1024)						// �e�̍ő吔
#define BULLET_SIZE		(9)							//�e�̃T�C�Y

#define BULLET_TEXTURE "data/TEXTURE/bullet000.png"	//�e�̃e�N�X�`��

#define MAX_BULLET_LIFE (300)						//�e�̎���

#define BULLET_COEFFICIENT (0.4f)					//�e�p�x�̌W��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//��ԗ�
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//����
	BULLETTYPE_ENEMY,		//�G
	BULLETTYPE_ENEMY_HOMING,//�G�ǔ��e
	BULLETTYPE_BOSS,		//�{�X
	BULLETTYPE_BOSS_OPTION,	//�{�X�̃I�v�V����
	BULLETTYPE_MAX
}BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	BULLETTYPE type;
	D3DXCOLOR col;
	float fAngle;
	int nLife;
	bool bUse;
}Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type,D3DXCOLOR col ,float angle);
Bullet *GetBullet(void);
void BulletErese(void);
#endif
