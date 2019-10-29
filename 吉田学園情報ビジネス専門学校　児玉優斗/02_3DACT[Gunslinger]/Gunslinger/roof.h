//=============================================================================
//
// �Ǐ���[roof.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ROOF_H_
#define _ROOF_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	ROOFTYPE_1,
	ROOFTYPE_MAX
}ROOFTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	ROOFTYPE type;
	float fWidth;	//��
	float Haight;	//���s
	bool bUse;
}ROOF;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRoof(void);
void UninitRoof(void);
void UpdateRoof(void);
void DrawRoof(void);
void SetRoof(D3DXVECTOR3 pos, D3DXVECTOR3 rot,ROOFTYPE type, float fWidth ,float haight);
#endif
