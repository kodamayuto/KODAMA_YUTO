//*****************************************************************************
//
//					DirectX ファイル管理(背景処理) [bg.h]
//						Author Kodama Yuto
//
//*****************************************************************************
#ifndef _BG_H_	//二重インクルード防止のマクロ定義
#define _BG_H_

//インクルードファイル
#include "main.h"
#include "Player.h"

//=============================================================================
//								マクロ定義
//=============================================================================
#define BG_TEXTURE "data/TEXTURE/sky000.jpg"	  //背景に貼るテクスチャの名前
#define BG_MOUNTEN_TEXTURE "data/TEXTURE/mountain000.png"
#define BG_TEXTURE_001 "data/TEXTURE/machi.jpg"	  //背景に貼るテクスチャの名前

#define BG_POS_X (0)					  //X座標		
#define BG_POS_Y (0)					  //Y座標					
#define BG_WIDTH (SCREEN_WIDTH)		
#define BG_HEIGHT (700)

//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

#endif // !_BG_H_

