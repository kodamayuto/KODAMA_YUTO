//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT		"data/TEXTURE/effect000.jpg"	// 読み込むテクスチャファイル名
#define	MAX_EFFECT			(8192)							// エフェクトの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
EFFECT					g_aEffect[MAX_EFFECT];		// エフェクトの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// テクスチャの開放
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	int nCntData;
	for (nCntData = 0; nCntData < MAX_EFFECT; nCntData++)
	{
		//変数宣言
		VERTEX_2D *pVtx;	//頂点情報へのポインタ

		// 頂点情報を設定
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
		
		pVtx += 4 * nCntData;

		if (g_aEffect[nCntData].bUse == true)
		{
			g_aEffect[nCntData].nLife--;
			if (g_aEffect[nCntData].nLife <= 0)
			{
				g_aEffect[nCntData].bUse = false;
			}
			/*サイズを小さくする(今回はこちらを採用)*/
			g_aEffect[nCntData].fRadius -= (BULLET_SIZE * 0.1f);
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);

			/*α値を下げる*/
			//g_aEffect[nCntData].col.a -= 0.1f;
			//pVtx[0].col = g_aEffect[nCntData].col;
			//pVtx[1].col = g_aEffect[nCntData].col;
			//pVtx[2].col = g_aEffect[nCntData].col;
			//pVtx[3].col = g_aEffect[nCntData].col;



		}
		//頂点バッファをアンロックする
		g_pVtxBuffEffect->Unlock();

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;
	
	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	//// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ポリゴンの描画
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,    //プリミティブの種類		//プリミティブ == ポリゴン
				4 * nCntEffect,					   //開始する頂点のインデックス(基本０)
				2);		   			   //プリミティブの数
		}
	}
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
	

}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntData;

	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT, &g_pTextureEffect);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						// 頂点情報を設定
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntData = 0; nCntData < MAX_EFFECT; nCntData++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(10,10,0.0f);
		pVtx[1].pos = D3DXVECTOR3(20,10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(10 ,20, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(20, 20, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();


}


//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	//変数宣言
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	int nCntData;


	for (nCntData = 0; nCntData < MAX_EFFECT; nCntData++)
	{
		if (g_aEffect[nCntData].bUse == false)
		{
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntData;

			g_aEffect[nCntData].pos = pos;
			g_aEffect[nCntData].col = col;

			pVtx[0].col = g_aEffect[nCntData].col;
			pVtx[1].col = g_aEffect[nCntData].col;
			pVtx[2].col = g_aEffect[nCntData].col;
			pVtx[3].col = g_aEffect[nCntData].col;

			g_aEffect[nCntData].fRadius = fRadius;

			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y - g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x - g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntData].pos.x + g_aEffect[nCntData].fRadius, g_aEffect[nCntData].pos.y + g_aEffect[nCntData].fRadius, 0.0f);

			g_aEffect[nCntData].nLife = nLife;
			g_aEffect[nCntData].bUse = true;
			//頂点バッファをアンロックする
			g_pVtxBuffEffect->Unlock();

			break;
		}
	}

}

//
//
//
EFFECT *GetEffect(void)
{
	return &g_aEffect[0];
}
