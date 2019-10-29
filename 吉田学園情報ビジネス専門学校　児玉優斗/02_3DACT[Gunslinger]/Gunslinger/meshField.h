//=============================================================================
//
// �|���S������ [meshField.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;	  //�ʒu
	D3DXVECTOR3 rot;	  //����
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	float fWidth;	//��
	float fDepth;	//���s
	bool bUse;
	int nNumVertex;	//���_��
	int nNumIndex;	//�C���f�b�N�X��
	int nNumPolygon;//�|���S����
}MESHFIELD;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
#endif
