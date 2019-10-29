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
	SOUND_LABEL_BGM000,			// BGM0(title)
	SOUND_LABEL_BGM001,			// BGM1(tutorial)
	SOUND_LABEL_BGM002,			// BGM2(game)
	SOUND_LABEL_BGM003,			// BGM3(result)
	SOUND_LABEL_SE000,			// SE 0(プレイヤーの弾打ち)
	SOUND_LABEL_SE001,			// SE 1(決定音)
	SOUND_LABEL_SE002,			// SE 2(ポーズ音)
	SOUND_LABEL_SE003,			// SE 3(ポーズ選択音)
	SOUND_LABEL_SE004,			// SE 4(ヒット音)
	SOUND_LABEL_SE005,			// SE 5(爆発音)
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
