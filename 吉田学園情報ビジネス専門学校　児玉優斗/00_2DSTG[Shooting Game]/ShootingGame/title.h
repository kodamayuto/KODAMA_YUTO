#pragma once
//=============================================================================
//
// �w�i���� [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLE_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _TITLE_H_

#include "main.h"
//=============================================================================
//								�}�N����`
//=============================================================================
#define TITLE_TEXTURE "data/TEXTURE/Title1.png"			  //�w�i�ɓ\��e�N�X�`���̖��O
#define TITLE_TEXTURE_100 "data/TEXTURE/bg100.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TITLE_TEXTURE_101 "data/TEXTURE/bg101.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TITLE_TEXTURE_102 "data/TEXTURE/bg102.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TITLE_TEXTURE_ENTER "data/TEXTURE/press_enter.png"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TITLE_POS_X (0)					  //X���W		
#define TITLE_POS_Y (0)					  //Y���W					
#define TITLE_WIDTH (SCREEN_WIDTH)		
#define TITLE_HEIGHT (SCREEN_HEIGHT)

//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif // !_BG_H_
