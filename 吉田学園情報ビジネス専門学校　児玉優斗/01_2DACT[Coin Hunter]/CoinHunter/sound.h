//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Kodama Yuto
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
	SOUND_LABEL_BGM000,			// BGM0(title&tutorial)
	SOUND_LABEL_BGM001,			// BGM1(game)
	SOUND_LABEL_BGM002,			// BGM2(result&ranking)
	SOUND_LABEL_SE_000,			// SE 0(���艹)
	SOUND_LABEL_SE_001,			// SE 1(�Z���N�g��)
	SOUND_LABEL_SE_002,			// SE 2(�|�[�Y��)
	SOUND_LABEL_SE_003,			// SE 3(�R�C���擾���P)
	SOUND_LABEL_SE_004,			// SE 4(�R�C���擾���Q)
	SOUND_LABEL_SE_005,			// SE 5(���[�v��)
	SOUND_LABEL_SE_006,			// SE 6(�W�����v��)
	SOUND_LABEL_SE_007,			// SE 7(�q�b�g��)
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);//PlaySound(SOUND_LABEL_BGM001);
void StopSound(SOUND_LABEL label);//StopSound(SOUND_LABEL_BGM001);
void StopSound(void);

#endif
