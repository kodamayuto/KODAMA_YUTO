//=============================================================================
//
// カウントダウン処理 [countDown.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COUNTDOWN_MOVE (0.0f)
#define COUNTDOWN_SIZE_MIN (300.0f)
#define COUNTDOWN_SIZE_MAX (1000.0f)
#define COUNTDOWN_TEXTURE_FIRENAME "data/TEXTURE/number000.png"
#define MAX_POLYGON_COUNTDOWN (2)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCountDown(void);
void UninitCountDown(void);
void UpdateCountDown(void);
void DrawCountDown(void);

void SetCountDown(void);
#endif
