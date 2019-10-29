#pragma once
//=============================================================================
//
// 背景処理 [tutorial.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TUTORIAL_H_	//二重インクルード防止のマクロ定義
#define _TUTORIAL_H_

#include "main.h"
//=============================================================================
//								マクロ定義
//=============================================================================
#define TUTORIAL_TEXTURE "data/TEXTURE/tutorial0001.jpg"	  //背景に貼るテクスチャの名前
#define TUTORIAL_TEXTURE_2 "data/TEXTURE/tutorial0002.jpg"	  //背景に貼るテクスチャの名前
#define TUTORIAL_TEXTURE_3 "data/TEXTURE/Tutorial0003.jpg"	  //背景に貼るテクスチャの名前
#define TUTORIAL_TEXTURE_ENTER "data/TEXTURE/press_enter.png"
#define TUTORIAL_TEXTURE_START "data/TEXTURE/START.png"

#define TUTORIAL_POS_X (SCREEN_WIDTH-500)					  //X座標		
#define TUTORIAL_POS_Y (0)					  //Y座標					
#define TUTORIAL_WIDTH (SCREEN_WIDTH)		
#define TUTORIAL_HEIGHT (SCREEN_HEIGHT)

//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif // !_TUTORIAL_H_
