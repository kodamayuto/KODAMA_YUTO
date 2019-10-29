//=============================================================================
//
// �����G�t�F�N�g����[particle.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//�p�x
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	D3DXMATRIX g_mtxWorld;//�|���S���̃}�g���b�N�X
	float fWidth;	//��
	float Haight;	//���s
	bool bUse;		//�g�p�̉�
	int nLife;		//�e�̕\������
}PARTICLE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col,float fWidth ,float haight);
#endif
