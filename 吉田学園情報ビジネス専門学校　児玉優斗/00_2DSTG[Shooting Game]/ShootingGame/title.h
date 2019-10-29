#pragma once
//=============================================================================
//
// 背景処理 [title.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TITLE_H_	//二重インクルード防止のマクロ定義
#define _TITLE_H_

#include "main.h"
//=============================================================================
//								マクロ定義
//=============================================================================
#define TITLE_TEXTURE "data/TEXTURE/Title1.png"			  //背景に貼るテクスチャの名前
#define TITLE_TEXTURE_100 "data/TEXTURE/bg100.png"	  //背景に貼るテクスチャの名前
#define TITLE_TEXTURE_101 "data/TEXTURE/bg101.png"	  //背景に貼るテクスチャの名前
#define TITLE_TEXTURE_102 "data/TEXTURE/bg102.png"	  //背景に貼るテクスチャの名前
#define TITLE_TEXTURE_ENTER "data/TEXTURE/press_enter.png"	  //背景に貼るテクスチャの名前
#define TITLE_POS_X (0)					  //X座標		
#define TITLE_POS_Y (0)					  //Y座標					
#define TITLE_WIDTH (SCREEN_WIDTH)		
#define TITLE_HEIGHT (SCREEN_HEIGHT)

//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif // !_BG_H_
