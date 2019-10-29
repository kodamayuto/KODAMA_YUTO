//=============================================================================
//
// �|���S������ [polygon.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	POLYGONTYPE_FIELD,
	POLYGONTYPE_MAX
}POLYGONTYPE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	POLYGONTYPE type;
	float fWidth;	//��
	float fDepth;	//���s
	bool bUse;
}POLYGON;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot,POLYGONTYPE type, float fWidth ,float fDepth);
#endif
