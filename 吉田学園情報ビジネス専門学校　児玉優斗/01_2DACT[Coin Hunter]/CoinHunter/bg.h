//*****************************************************************************
//
//					DirectX �t�@�C���Ǘ�(�w�i����) [bg.h]
//						Author Kodama Yuto
//
//*****************************************************************************
#ifndef _BG_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _BG_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "Player.h"

//=============================================================================
//								�}�N����`
//=============================================================================
#define BG_TEXTURE "data/TEXTURE/sky000.jpg"	  //�w�i�ɓ\��e�N�X�`���̖��O
#define BG_MOUNTEN_TEXTURE "data/TEXTURE/mountain000.png"
#define BG_TEXTURE_001 "data/TEXTURE/machi.jpg"	  //�w�i�ɓ\��e�N�X�`���̖��O

#define BG_POS_X (0)					  //X���W		
#define BG_POS_Y (0)					  //Y���W					
#define BG_WIDTH (SCREEN_WIDTH)		
#define BG_HEIGHT (700)

//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

#endif // !_BG_H_

