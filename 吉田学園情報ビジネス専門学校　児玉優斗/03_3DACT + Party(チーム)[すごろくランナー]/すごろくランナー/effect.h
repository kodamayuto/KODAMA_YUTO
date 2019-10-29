//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �G�t�F�N�g�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3   pos;              // �ʒu(���S)
	D3DXVECTOR3   rot;              // ����
	D3DXMATRIX    mtxWorld;         // ���[���h�}�g���b�N�X
	D3DXCOLOR     col;              // �F
	float         fRadius;          // ���a
	int           nLife;            // ����
	int           nIdxShadow;       // �g�p���Ă���e�̔ԍ�
	bool          bUse;             // �g�p���Ă��邩�ǂ���
}Effect;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define  MAX_EFFECT   (256)        // �G�t�F�N�g�̑���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float radius, int life);
#endif
