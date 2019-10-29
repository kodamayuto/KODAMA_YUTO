#pragma once
//=============================================================================
//
// �X�e�[�W���� [stage_change.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _STAGE_CHANGE_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _STAGE_CHANGE_H_

#include "main.h"
//=============================================================================
//								�}�N����`
//=============================================================================
#define CHANGE_TEXTURE_1 "data/TEXTURE/Action_Stage.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define CHANGE_TEXTURE_2 "data/TEXTURE/Action_Number.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define CHANGE_TEXTURE_3 "data/TEXTURE/Tutorial001.jpg"	  //�w�i�ɓ\��e�N�X�`���̖��O

#define CHANGE_INTERVAL (80)
//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitChange(void);
void UninitChange(void);
void UpdateChange(void);
void DrawChange(void);

#endif // !_STAGE_CHANGE_H_
