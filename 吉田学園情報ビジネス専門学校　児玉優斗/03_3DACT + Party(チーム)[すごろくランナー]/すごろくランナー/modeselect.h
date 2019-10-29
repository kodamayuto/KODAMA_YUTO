//=============================================================================
//
// �|�[�Y���� [modeSelect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MODESELECT_H_	//��d�C���N���[�h�h�~�̃}�N����`
#define _MODESELECT_H_

#include "main.h"

//=============================================================================
//								�}�N����`
//=============================================================================
#define MODESELECT_TEXTURE_001 "data/TEXTURE/rand.png"	  //�w�i�ɓ\��e�N�X�`��
#define MODESELECT_TEXTURE_002 "data/TEXTURE/���[�h�I��(�ӂ�����).png"	  
#define MODESELECT_TEXTURE_003 "data/TEXTURE/���[�h�I��(�Q�[��).png"	  
#define MODESELECT_TEXTURE_004 "data/TEXTURE/���[�h�I��(�`���[�g���A��).png"	  
#define MODESELECT_TEXTURE_005 "data/TEXTURE/���[�h�I��(�����L���O).png"	
#define MODESELECT_TEXTURE_006 "data/TEXTURE/���[�h�I�����(�^�C�g��).png"

#define MODESELECT_POS_X (0)					  //X���W		
#define MODESELECT_POS_Y (0)					  //Y���W					
#define MODESELECT_WIDTH (SCREEN_WIDTH)		
#define MODESELECT_HEIGHT (SCREEN_HEIGHT)

#define MODESELECT_COL_A (0.3f)		//��ʂ̐F.a
//-----------------------------------------------------------------------------
//							�v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitModeSelect(void);
void UninitModeSelect(void);
void UpdateModeSelect(void);
void DrawModeSelect(void);
void SerectReset(void);
void DispReset(void);

int GetNumber(void);
#endif // !_MODESELECT_H_

