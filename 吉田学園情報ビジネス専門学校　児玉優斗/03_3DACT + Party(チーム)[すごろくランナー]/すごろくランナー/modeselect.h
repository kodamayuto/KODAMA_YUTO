//=============================================================================
//
// ポーズ処理 [modeSelect.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MODESELECT_H_	//二重インクルード防止のマクロ定義
#define _MODESELECT_H_

#include "main.h"

//=============================================================================
//								マクロ定義
//=============================================================================
#define MODESELECT_TEXTURE_001 "data/TEXTURE/rand.png"	  //背景に貼るテクスチャ
#define MODESELECT_TEXTURE_002 "data/TEXTURE/モード選択(ふきだし).png"	  
#define MODESELECT_TEXTURE_003 "data/TEXTURE/モード選択(ゲーム).png"	  
#define MODESELECT_TEXTURE_004 "data/TEXTURE/モード選択(チュートリアル).png"	  
#define MODESELECT_TEXTURE_005 "data/TEXTURE/モード選択(ランキング).png"	
#define MODESELECT_TEXTURE_006 "data/TEXTURE/モード選択画面(タイトル).png"

#define MODESELECT_POS_X (0)					  //X座標		
#define MODESELECT_POS_Y (0)					  //Y座標					
#define MODESELECT_WIDTH (SCREEN_WIDTH)		
#define MODESELECT_HEIGHT (SCREEN_HEIGHT)

#define MODESELECT_COL_A (0.3f)		//画面の色.a
//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitModeSelect(void);
void UninitModeSelect(void);
void UpdateModeSelect(void);
void DrawModeSelect(void);
void SerectReset(void);
void DispReset(void);

int GetNumber(void);
#endif // !_MODESELECT_H_

