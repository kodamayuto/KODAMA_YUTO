//=============================================================================
//
// 壁処理[effect.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "effect.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_FILENAME0 "data/TEXTURE/shadow000.jpg"
#define MAX_EFFECT (4096)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;	    //テクスチャへのポインタ

EFFECT g_Effect[MAX_EFFECT];

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, EFFECT_FILENAME0, &g_pTextureEffect);

	MakeVertexEffect(pDevice);

	//構造体の初期化
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Effect[nCntEffect].fWidth = 0.0f;
		g_Effect[nCntEffect].Haight = 0.0f;
		g_Effect[nCntEffect].nLife = 0;
		g_Effect[nCntEffect].bUse = false;
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	// 頂点バッファの開放
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
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			g_Effect[nCntEffect].nLife--;

			if (g_Effect[nCntEffect].nLife <= 0)
			{
				g_Effect[nCntEffect].col.a -= 0.2f;
				g_Effect[nCntEffect].fWidth -= 0.5f;
				g_Effect[nCntEffect].Haight -= 0.5f;

				if (g_Effect[nCntEffect].col.a < 0.0f)
				{
					g_Effect[nCntEffect].col.a = 0.0f;
					g_Effect[nCntEffect].bUse = false;
				}
			}
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntEffect;

			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);

			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;

			//頂点バッファをアンロックする
			g_pVtxBuffEffect->Unlock();

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans , mtxView;				// 計算用マトリックス

	// ポリゴンの描画
			//// αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			//αテストを有効にする
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 120);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// Zバッファを無効化
			pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

			// ライティングモードを無効化
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{

			D3DXMatrixIdentity(&g_Effect[nCntEffect].g_mtxWorld);

			g_Effect[nCntEffect].g_mtxWorld._11 = mtxView._11;
			g_Effect[nCntEffect].g_mtxWorld._12 = mtxView._21;
			g_Effect[nCntEffect].g_mtxWorld._13 = mtxView._31;
			g_Effect[nCntEffect].g_mtxWorld._21 = mtxView._12;
			g_Effect[nCntEffect].g_mtxWorld._22 = mtxView._22;
			g_Effect[nCntEffect].g_mtxWorld._23 = mtxView._32;
			g_Effect[nCntEffect].g_mtxWorld._31 = mtxView._13;
			g_Effect[nCntEffect].g_mtxWorld._32 = mtxView._23;
			g_Effect[nCntEffect].g_mtxWorld._33 = mtxView._33;
			
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Effect[nCntEffect].pos.x,
				g_Effect[nCntEffect].pos.y,
				g_Effect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_Effect[nCntEffect].g_mtxWorld,
				&g_Effect[nCntEffect].g_mtxWorld,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntEffect,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}

	}
	// ライティングモードを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zバッファの有効化
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//αテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		// αブレンディングを元に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// ポリゴンの設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float haight)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			g_Effect[nCntEffect].pos = pos;
			g_Effect[nCntEffect].rot = rot;
			g_Effect[nCntEffect].col = col;
			g_Effect[nCntEffect].fWidth = fWidth;
			g_Effect[nCntEffect].Haight = haight;
			g_Effect[nCntEffect].nLife = 10;


			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntEffect;
			pVtx[0].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fWidth, -g_Effect[nCntEffect].Haight, 0.0f);

			pVtx[0].col = g_Effect[nCntEffect].col;
			pVtx[1].col = g_Effect[nCntEffect].col;
			pVtx[2].col = g_Effect[nCntEffect].col;
			pVtx[3].col = g_Effect[nCntEffect].col;


			//頂点バッファをアンロックする
			g_pVtxBuffEffect->Unlock();
			g_Effect[nCntEffect].bUse = true;

			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntEffect;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
}

