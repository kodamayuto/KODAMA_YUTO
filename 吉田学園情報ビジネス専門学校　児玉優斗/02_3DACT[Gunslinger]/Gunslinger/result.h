#pragma once
//=============================================================================
//
// リザルト処理 [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RESULT_H_	//二重インクルード防止のマクロ定義
#define _RESULT_H_

#include "main.h"
//=============================================================================
//								マクロ定義
//=============================================================================
#define RESULT_TEXTURE_LOSE "data/TEXTURE/Gameover00.png"	  //背景に貼るテクスチャの名前
#define RESULT_TEXTURE_WIN "data/TEXTURE/sky.png"	  //背景に貼るテクスチャの名前
#define RESULT_TEXTURE_ENTER "data/TEXTURE/press_enter.png"
#define RESULT_POS_X (0)					  //X座標		
#define RESULT_POS_Y (0)					  //Y座標					
#define RESULT_WIDTH (SCREEN_WIDTH)		
#define RESULT_HEIGHT (SCREEN_HEIGHT)

//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif // !_RESULT_H_
