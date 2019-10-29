//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT (3)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];		//ライトの情報
D3DXVECTOR3 vecDir[MAX_LIGHT];
D3DXCOLOR DifCol[MAX_LIGHT];

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	//DifCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//DifCol[1] = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	//DifCol[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	DifCol[0] = D3DXCOLOR(0.60f, 0.60f, 0.60f, 1.0f);
	DifCol[1] = D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f);
	DifCol[2] = D3DXCOLOR(0.05f, 0.05f, 0.05f, 1.0f);

	// ライトをクリアする
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの初期化
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		g_light[nCntLight].Diffuse = DifCol[nCntLight];

		// ライトの方向の設定
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		// ライトを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
}

