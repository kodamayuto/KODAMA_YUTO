//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_FRAME		"data/TEXTURE/waku.png"
#define MAX_SCORE_DIGIT (8)									//����
#define SCORE_SIZE      (20.0f)								//�X�R�A�̑傫��

#define SCORE_POS_X (800)									//�X�R�A��X��
#define SCORE_POS_Y (50)									//�X�R�A��Y��

#define FRAME_INTERVAL (180)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

void OverStageScore(int nScore);
void ResetScore(void);
int GetScore(void);
#endif
