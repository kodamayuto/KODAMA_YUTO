//=============================================================================
//
// �^�[�������� [turnNum.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _TURN_H_
#define _TURN_H_

#include "main.h"

//*****************************************************************************
// �^�[�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3  pos;          // �ʒu
	float        Width;        // ��
	float        Height;       // ����
	int          nScore;       // �X�R�A
	int          TexturePos;   // �e�N�X�`�����W
	int          NumScore;     // �X�R�A�̌���
}TurnNum;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTurnNum(void);
void UninitTurnNum(void);
void UpdateTurnNum(void);
void DrawTurnNum(void);
void AddTurnNum(int nValue);
int GetTurnNum(void);

#endif