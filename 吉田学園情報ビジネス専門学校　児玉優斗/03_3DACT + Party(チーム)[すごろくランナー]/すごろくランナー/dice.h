//=============================================================================
//
// ���f������ [model.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _DICE_H_
#define _DICE_H_

#include "main.h"
//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	DICEMOTION_NONE = 0,
	DICEMOTION_MOVE,
	DICEMOTION_THROW,
	DICEMOTION_STOP,
	DICEMOTION_MAX
}DICEMOTION;
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 oldPos;		//�����ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//��]�p�x
	D3DXVECTOR3 rotMove;	//��]��
	D3DXMATRIX  mtxWorld;	//���f���̃}�g���b�N�X
	bool bUse;				//�g�p�t���O
	D3DXVECTOR3 VtxMin;		//���f���̓����蔻��̍ŏ�
	D3DXVECTOR3 VtxMax;		//���f���̓����蔻��̍ő�
	DWORD NumMatDice;		//�}�e���A�����̐�
	int nCntDiceMove;		//���f���̉�]���x
	int nNumDice;			//�T�C�R���̏o��
	DICEMOTION DiceMotion;	//�T�C�R���̏��
}DICE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitDice(void);
void UninitDice(void);
void UpdateDice(void);
void DrawDice(void);

int  GetNumDice(void);	//�_�C�X�̐������擾
void SetDice(int nNumDice);
void DeleteDice(int nNumDice);

#endif
