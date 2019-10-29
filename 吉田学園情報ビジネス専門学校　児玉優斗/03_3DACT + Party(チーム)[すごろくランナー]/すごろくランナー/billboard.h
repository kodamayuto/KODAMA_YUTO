//=============================================================================
//
// �r���{�[�h�̏��� [billboard.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _BILLBORAD_H_
#define _BILLBORAD_H_

#include "main.h"

//*****************************************************************************
// �r���{�[�h�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3   pos;              // �ʒu(���S)
	D3DXVECTOR3   move;             // �ړ���
	D3DXVECTOR3   rot;              // ����
	D3DXMATRIX    mtxWorld;         // ���[���h�}�g���b�N�X
	float         fWidth;           // ��
	float         fHeight;          // ����
	int           nIdxShadow;       // �g�p���Ă���e�̔ԍ�
	bool          bUse;             // �g�p���Ă��邩�ǂ���
}Billboard;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;        // ����
	float       fWidth;     // ��
	float       fHeight;    // ����
} BILLBOARD_INFO;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define  MAX_BILLBOARD   (256)         // �r���{�[�h�̑���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, float width, float height);
bool CollisionBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 radius);
Billboard *GetBillboard(void);

#endif
