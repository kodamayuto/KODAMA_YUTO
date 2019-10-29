#pragma once
//=============================================================================
//
// �w�i���� [tutorial.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TUTORIAL_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _TUTORIAL_H_

#include "main.h"
//=============================================================================
//								�}�N����`
//=============================================================================
#define TUTORIAL_TEXTURE "data/TEXTURE/tutorial0001.jpg"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TUTORIAL_TEXTURE_2 "data/TEXTURE/tutorial0002.jpg"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TUTORIAL_TEXTURE_3 "data/TEXTURE/Tutorial0003.jpg"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define TUTORIAL_TEXTURE_ENTER "data/TEXTURE/press_enter.png"
#define TUTORIAL_TEXTURE_START "data/TEXTURE/START.png"

#define TUTORIAL_POS_X (SCREEN_WIDTH-500)					  //X���W		
#define TUTORIAL_POS_Y (0)					  //Y���W					
#define TUTORIAL_WIDTH (SCREEN_WIDTH)		
#define TUTORIAL_HEIGHT (SCREEN_HEIGHT)

//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif // !_TUTORIAL_H_
