//=============================================================================
//
// �J�������� [camera.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ANGLE_MOVE  (0.03f) //�J�����p�x�̈ړ���
#define CAMERA_MOVE (1.5f)  //�J�����̈ړ���

#define CAMERA_POS_INTERVAL (20.0f)			//�J�����̒����_�̈ʒu
#define CAMERA_POSV_COEFFICIENT (0.20f);	//�J�������_�̌W��
#define CAMERA_POSR_COEFFICIENT (0.18f);	//�J���������_�̌W��

#define CAMERA_ROTMOVE_INTERVAL (60)		//���_�ړ��̑ҋ@����
//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;	 //���_
	D3DXVECTOR3 posR;	 //�����_
	D3DXVECTOR3 posVDest;//�ړI�̎��_
	D3DXVECTOR3 posRDest;//�ړI�̒����_
	D3DXVECTOR3 vecU;	 //������x�N�g��
	D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;	 //�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;	 //�p�x
	D3DXVECTOR3 rotmove; //�p�ړ���
	int nRotmoveCount;	 //���_�ړ��̑ҋ@����
	float fLength;		 //����	
}Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif
