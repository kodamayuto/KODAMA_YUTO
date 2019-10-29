//=============================================================================
//
// �|���S������ [meshCylinder.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

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
	D3DXCOLOR col;	//�F
}MESHCYLINDER;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
#endif
