//=============================================================================
//
// �J�E���g�_�E������ [countDown.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNTDOWN_MOVE (0.0f)
#define COUNTDOWN_SIZE_MIN (300.0f)
#define COUNTDOWN_SIZE_MAX (1000.0f)
#define COUNTDOWN_TEXTURE_FIRENAME "data/TEXTURE/number000.png"
#define MAX_POLYGON_COUNTDOWN (2)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCountDown(void);
void UninitCountDown(void);
void UpdateCountDown(void);
void DrawCountDown(void);

void SetCountDown(void);
#endif
