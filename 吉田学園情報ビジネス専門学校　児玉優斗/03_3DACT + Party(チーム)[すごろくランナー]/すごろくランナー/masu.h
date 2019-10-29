//=============================================================================
//
// �}�X�̏��� [nasu.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _MASU_H_
#define _MASU_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
//*****************************************************************************
// �u���b�N�̎��
//*****************************************************************************
typedef enum
{// �u���b�N�̎��
	MASUTYPE_JUMP_UP = 0,   // �W�����v�͏㏸�}�X
	MASUTYPE_JUMP_DOWN,     // �W�����v�͌����}�X
	MASUTYPE_SPEED_UP,      // �ړ��͏㏸�}�X
	MASUTYPE_SPEED_DOWN,    // �ړ��͌����}�X
	MASUTYPE_DICE_TWICE,    // 2�{�}�X
	MASUTYPE_JUMP_RAMP,     // �W�����v��}�X
	MASUTYPE_NORMAL,		// �ʏ�}�X
	MASUTYPE_GOAL,			// �S�[��
	MASUTYPE_START,			// �X�^�[�g
	MASUTYPE_MAX
} MASUTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	                // �ʒu
	D3DXVECTOR3 rot;	                // ����
	D3DXVECTOR3 move;	                // �ړ���
	int			nInxShadow;             // �e�̔ԍ�
	MASUTYPE	masuType;               // �}�X�̎��
	D3DXVECTOR3	vtxMinMasu, vtxMaxMasu;	// ���f���̍ŏ��l�A�ő�l
	D3DXMATRIX	mtxWorld;			    // ���[���h�}�g���b�N�X
	bool		bUse;                   // �g�p���Ă��邩�ǂ���
} MASU;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMasu(void);
void UninitMasu(void);
void UpdateMasu(void);
void DrawMasu(void);
MASU *GetMasu(void);
void SetMasu(D3DXVECTOR3 pos, MASUTYPE Type);
bool CollisionMasu(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius, MASU **pMasu);

D3DXVECTOR3 PlayerDistance(void);
#endif