//=============================================================================
//
// タイマー処理 [meter.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _METER_H_
#define _METER_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define METER_MOVE (0.5f)
#define METER_SIZE_MIN (300.0f)
#define METER_SIZE_MAX (1000.0f)
#define METER_TEXTURE_FIRENAME0 "data/TEXTURE/gradation000.jpg"
#define METER_TEXTURE_FIRENAME "data/TEXTURE/Meter002.png"
#define MAX_POLYGON_METER (2)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeter(void);
void UninitMeter(void);
void UpdateMeter(void);
void DrawMeter(void);

float GetMeterSize(void);
#endif
