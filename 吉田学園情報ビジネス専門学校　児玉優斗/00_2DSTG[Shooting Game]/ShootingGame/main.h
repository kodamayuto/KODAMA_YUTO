//*****************************************************************************
//
//DirectX 弾の発射処理  [main.h]
//Author : Kodama Yuto
//
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//インクルードファイル
#include <windows.h>
#include "d3dx9.h"		//描画処理に必要

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"	//サウンドの処理に必要

//
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "score.h"
#include "life.h"
#include "effect.h"
#include "sound.h"
#include "playermode.h"
#include "boss.h"
#include "boss_option.h"

//-----------------------------------------------------------------------------
//						ライブラリのリンク
//-----------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9.h]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント使用に必要
#pragma comment(lib,"winmm.lib")	//システム時刻の取得に必要
#pragma comment(lib,"dinput8.lib")

//-----------------------------------------------------------------------------
//						 マクロ定義
//-----------------------------------------------------------------------------
#define SCREEN_WIDTH	(1280)										   //ウインドウの幅
#define SCREEN_HEIGHT	(720)										   //ウインドウの高さ

#define FVF_VERTEX_2D   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //頂点フォーマット

#define TEX_PATTERN         (8)

//-----------------------------------------------------------------------------
//						 構造体の定義
//-----------------------------------------------------------------------------
typedef enum
{
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX,
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//1,0fで固定
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_2D;

//----------------------------------------------------------------------------
//						プロトタイプ宣言
//----------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif