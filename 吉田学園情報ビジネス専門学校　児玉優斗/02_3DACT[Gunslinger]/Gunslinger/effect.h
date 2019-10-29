//=============================================================================
//
// �����G�t�F�N�g����[effect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//�p�x
	D3DXCOLOR col;		//�F
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	float fWidth;	//��
	float Haight;	//���s
	bool bUse;		//�g�p�̉�
	int nLife;		//�e�̕\������
}EFFECT;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col,float fWidth ,float haight);
#endif
