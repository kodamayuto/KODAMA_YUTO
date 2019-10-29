//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000,			// BGM0(title&tutorial)
	SOUND_LABEL_BGM001,			// BGM1(game)
	SOUND_LABEL_BGM002,			// BGM2(result&ranking)
	SOUND_LABEL_SE_000,			// SE 0(決定音)
	SOUND_LABEL_SE_001,			// SE 1(セレクト音)
	SOUND_LABEL_SE_002,			// SE 2(ポーズ音)
	SOUND_LABEL_SE_003,			// SE 3(コイン取得音１)
	SOUND_LABEL_SE_004,			// SE 4(コイン取得音２)
	SOUND_LABEL_SE_005,			// SE 5(ワープ音)
	SOUND_LABEL_SE_006,			// SE 6(ジャンプ音)
	SOUND_LABEL_SE_007,			// SE 7(ヒット音)
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);//PlaySound(SOUND_LABEL_BGM001);
void StopSound(SOUND_LABEL label);//StopSound(SOUND_LABEL_BGM001);
void StopSound(void);

#endif
