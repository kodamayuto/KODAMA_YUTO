//=============================================================================
//
// �Ǐ���[wall.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	WALLTYPE_1,
	WALLTYPE_MAX
}WALLTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	WALLTYPE type;
	float fWidth;	//��
	float Haight;	//���s
	bool bUse;

	D3DXVECTOR3 aPos;
	D3DXVECTOR3 bPos;

}WALL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,WALLTYPE type, float fWidth ,float haight);
bool CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);

#endif
