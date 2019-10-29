//=============================================================================
//
// �e����[arrow.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _ARROW_H_
#define _ARROW_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorldArrow;
	bool bUse;
}Arrow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitArrow(void);
void UninitArrow(void);
void UpdateArrow(void);
void DrawArrow(void);
void SetArrow(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
void SetPositionArrow(D3DXVECTOR3 pos);
#endif
