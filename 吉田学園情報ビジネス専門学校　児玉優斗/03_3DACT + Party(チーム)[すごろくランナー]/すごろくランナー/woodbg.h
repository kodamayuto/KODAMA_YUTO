//=============================================================================
//
// �w�i�̖؂̏��� [woodBG.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _WOODBG_H_
#define _WOODBG_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	WOODBG_TYPE_PALM,
	WOODBG_TYPE_LAKE,
	WOODBG_TYPE_MAX,
}WOODBG_TYPE;

typedef struct
{
	D3DXVECTOR3 pos;	              // �ʒu
	D3DXVECTOR3 rot;	              // ����
	D3DXVECTOR3 move;	              // �ړ���
	int			nInxShadow;           // �e
	WOODBG_TYPE	nType;            // ���
	D3DXMATRIX	mtxWorld;	          // ���[���h�}�g���b�N�X
	bool		bUse;                 // �g�p���Ă��邩�ǂ���
	D3DXVECTOR3	vtxMinWoodBG, vtxMaxWoodBG;	// ���f���̍ŏ��l�A�ő�l
}WOODBG;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;        // ����
	D3DXVECTOR3 move;		// �ړ���
	WOODBG_TYPE nType;	// ���
}WOODBG_INFO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWoodBG(void);
void UninitWoodBG(void);
void UpdateWoodBG(void);
void DrawWoodBG(void);
WOODBG *GetWoodBG(void);
void SetWoodBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, WOODBG_TYPE nType);
//bool CollisionWoodBG(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif
