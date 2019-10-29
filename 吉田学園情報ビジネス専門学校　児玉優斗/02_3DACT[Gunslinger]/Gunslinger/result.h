#pragma once
//=============================================================================
//
// ���U���g���� [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RESULT_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _RESULT_H_

#include "main.h"
//=============================================================================
//								�}�N����`
//=============================================================================
#define RESULT_TEXTURE_LOSE "data/TEXTURE/Gameover00.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define RESULT_TEXTURE_WIN "data/TEXTURE/sky.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define RESULT_TEXTURE_ENTER "data/TEXTURE/press_enter.png"
#define RESULT_POS_X (0)					  //X���W		
#define RESULT_POS_Y (0)					  //Y���W					
#define RESULT_WIDTH (SCREEN_WIDTH)		
#define RESULT_HEIGHT (SCREEN_HEIGHT)

//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif // !_RESULT_H_
