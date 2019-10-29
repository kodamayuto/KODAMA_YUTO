#pragma once
//=============================================================================
//
// ステージ処理 [stage_change.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _STAGE_CHANGE_H_	//二重インクルード防止のマクロ定義
#define _STAGE_CHANGE_H_

#include "main.h"
//=============================================================================
//								マクロ定義
//=============================================================================
#define CHANGE_TEXTURE_1 "data/TEXTURE/Action_Stage.png"	  //背景に貼るテクスチャの名前
#define CHANGE_TEXTURE_2 "data/TEXTURE/Action_Number.png"	  //背景に貼るテクスチャの名前
#define CHANGE_TEXTURE_3 "data/TEXTURE/Tutorial001.jpg"	  //背景に貼るテクスチャの名前

#define CHANGE_INTERVAL (80)
//-----------------------------------------------------------------------------
//							プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitChange(void);
void UninitChange(void);
void UpdateChange(void);
void DrawChange(void);

#endif // !_STAGE_CHANGE_H_
