//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PAUSE_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _PAUSE_H_

#include "main.h"

//=============================================================================
//								�}�N����`
//=============================================================================
#define PAUSE_TEXTURE_001 "data/TEXTURE/pause100.png"	  //�w�i�ɓ\��e�N�X�`��
#define PAUSE_TEXTURE_002 "data/TEXTURE/Tutorial004.jpg"	  
#define PAUSE_TEXTURE_003 "data/TEXTURE/pause000.png"	  
#define PAUSE_TEXTURE_004 "data/TEXTURE/pause002.png"	

#define PAUSE_POS_X (0)					  //X���W		
#define PAUSE_POS_Y (0)					  //Y���W					
#define PAUSE_WIDTH (SCREEN_WIDTH)		
#define PAUSE_HEIGHT (SCREEN_HEIGHT)

#define PAUSE_COL_A (0.3f)		//��ʂ̐F.a
//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SerectReset(void);
void DispReset(void);
#endif // !_PAUSE_H_

