//=============================================================================
//
// �����G�t�F�N�g����[explosion.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//�p�x
	D3DXCOLOR col;			//�F
	D3DXMATRIX g_mtxWorld;	//�|���S���̃}�g���b�N�X
	float fWidth;			//��
	float Haight;			//���s
	bool bUse;				//�g�p�̉�
	int nAnim;				//�e�̕\������ 
	int nCntAnimation;		//�A�j���[�V�����̃J�E���g
}EXPLOSION;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col,float fWidth ,float haight);
#endif
