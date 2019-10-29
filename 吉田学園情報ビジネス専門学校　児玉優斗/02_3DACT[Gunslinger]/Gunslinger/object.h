//=============================================================================
//
// ���f������ [object.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
	D3DXVECTOR3 VtxMin;	//���f���̓����蔻��̍ŏ�
	D3DXVECTOR3 VtxMax;	//���f���̓����蔻��̍ő�
	DWORD NumMatModel;	//�}�e���A�����̐�
	LPCSTR FireName;
}OBJECT;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);

bool CollisionObject(D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pOldPos,
	D3DXVECTOR3 *pMove,
	D3DXVECTOR3 *pVtxMin,
	D3DXVECTOR3 *pVtxMax);


void SetObjectVertex(int nCntModel);

OBJECT *Getobject(void);
#endif
