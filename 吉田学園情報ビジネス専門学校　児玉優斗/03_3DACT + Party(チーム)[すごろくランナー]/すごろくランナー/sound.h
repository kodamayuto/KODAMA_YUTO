//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,	//�^�C�g��
	SOUND_LABEL_BGM001,		//���[�h�Z���N�g
	SOUND_LABEL_BGM002,		//�Q�[�����
	SOUND_LABEL_BGM003,		//�`���[�g���A�����
	SOUND_LABEL_BGM004,		//���U���g���
	SOUND_LABEL_BGM005,		//���U���g���
	SOUND_LABEL_BGM006,		//�����L���O���
	SOUND_LABEL_SE000,		//����
	SOUND_LABEL_SE001,		//�L�����Z��
	SOUND_LABEL_SE002,		//�I����
	SOUND_LABEL_SE003,		//�I����
	SOUND_LABEL_SE004,		//�T�C�R��
	SOUND_LABEL_SE005,		//�A�N�V����
	SOUND_LABEL_SE006,		//�q�b�g
	SOUND_LABEL_SE007,		//����
	SOUND_LABEL_SE008,		//�W�����v
	SOUND_LABEL_SE009,		//�X�e�[�^�XUP
	SOUND_LABEL_SE010,		//�X�e�[�^�XDOWN
	SOUND_LABEL_SE011,		//�c�^
	SOUND_LABEL_SE012,		//�N����
	SOUND_LABEL_SE013,		//�L�b�N
	SOUND_LABEL_MAX
} SOUND_LABEL;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
