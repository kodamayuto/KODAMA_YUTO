//*****************************************************************************
//
//					DirectX ステージ処理 [stage_change.cpp]
//					Author Kodama Yuto
//	(:3 )三
//****************************************************************************
//インクルードファイル
#include "stage_change.h"
#include "fade.h"

//=============================================================================
//							グローバル変数宣言
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChange = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureChange[3] = {};	                //テクスチャへのポインタ

int g_CounterChange = 0;

//-----------------------------------------------------------------------------
//						   背景の初期化処理
//-----------------------------------------------------------------------------
void InitChange(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得

	pDevice = GetDevice();
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	int nNumStage;

	nNumStage = GetNumStage() + 1;

	g_CounterChange = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, CHANGE_TEXTURE_1, &g_pTextureChange[0]);
	D3DXCreateTextureFromFile(pDevice, CHANGE_TEXTURE_2, &g_pTextureChange[1]);
	D3DXCreateTextureFromFile(pDevice, CHANGE_TEXTURE_3, &g_pTextureChange[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChange,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffChange->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(200, 160, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(800, 160, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200, 360, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(800, 360, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(850, 180, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(940, 180, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(850, 360, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(940, 360, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((0.1f * nNumStage) + 0.1f, 1.0f);

	pVtx += 4;
	pVtx[0].pos = D3DXVECTOR3(200, 460, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1000, 460, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200, 660, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1000, 660, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffChange->Unlock();

}

//-----------------------------------------------------------------------------
//						   背景の終了処理
//-----------------------------------------------------------------------------

void UninitChange(void)
{

	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (g_pTextureChange[nCntTex] != NULL)
		{
			g_pTextureChange[nCntTex]->Release();
			g_pTextureChange[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffChange != NULL)
	{
		g_pVtxBuffChange->Release();
		g_pVtxBuffChange = NULL;
	}
}

//-----------------------------------------------------------------------------
//							背景の更新処理
//-----------------------------------------------------------------------------
void UpdateChange(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_CounterChange++;

		if (*pFade != FADE_OUT && g_CounterChange >= CHANGE_INTERVAL)
		{
			SetFade(MODE_GAME);
		}
}

//-----------------------------------------------------------------------------
//							背景の描画処理
//-----------------------------------------------------------------------------

void DrawChange(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//描画
	pDevice->SetStreamSource(0, g_pVtxBuffChange, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
			pDevice->SetTexture(0, g_pTextureChange[nCntTex]);//テクスチャの設定

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
				4 * nCntTex,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
	}
}

