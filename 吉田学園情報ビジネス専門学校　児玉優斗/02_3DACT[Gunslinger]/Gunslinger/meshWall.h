//=============================================================================
//
// �|���S������ [meshWall.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;	  //�ʒu
	D3DXVECTOR3 rot;	  //����
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	bool bUse;
	int nNumVertex;	//���_��
	int nNumIndex;	//�C���f�b�N�X��
	int nNumPolygon;//�|���S����
	D3DXVECTOR3 aPos;//����p���W//��
	D3DXVECTOR3 bPos;//����p���W//��
	int nMeshBlockWidth;//���b�V���̉�����
	int nMeshBlockHaight;//���b�V���̏c����
	float fMeshSizeW;//�ǂ̕�
	float fMeshSizeH;//�ǂ̍���
}MESHWALL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);

bool CollisionMeshWall(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pPosOld);
void SetMeshWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
#endif
