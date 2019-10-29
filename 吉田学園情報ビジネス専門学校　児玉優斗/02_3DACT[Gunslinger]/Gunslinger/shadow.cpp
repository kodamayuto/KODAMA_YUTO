//=============================================================================
//
// 影処理[shadow.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "shadow.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADOW_POLYGON_FILENAME "data/TEXTURE/shadow000.jpg"
#define MAX_SHADOW (1024)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;	    //テクスチャへのポインタ

D3DXVECTOR3 g_posShadow;		//位置
D3DXVECTOR3 g_rotShadow;		//向き
D3DXMATRIX	g_mtxWorldShadow;	//ワールドマトリックス

Shadow g_Shadow[MAX_SHADOW];

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, SHADOW_POLYGON_FILENAME, &g_pTextureShadow);

	MakeVertexShadow(pDevice);

	//構造体の初期化
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	// 頂点バッファの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
												// ポリゴンの描画

	//αブレンディングを減算合成にする
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//// Zバッファを無効化
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorldShadow);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Shadow[nCntShadow].rot.y,
				g_Shadow[nCntShadow].rot.x,
				g_Shadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow,
				&g_Shadow[nCntShadow].mtxWorldShadow,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Shadow[nCntShadow].pos.x,
				g_Shadow[nCntShadow].pos.y,
				g_Shadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorldShadow,
				&g_Shadow[nCntShadow].mtxWorldShadow,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorldShadow);

			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定


				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntShadow,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
	////Zバッファの有効化
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// 影の設定
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].bUse = true;

		break;
		}
	}
	return nCntShadow;
}

//=============================================================================
// 影の位置設定
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_Shadow[nIdxShadow].pos = pos;
}

//=============================================================================
// 影のサイズ設定
//=============================================================================
void SetSizeShadow(int nIdxShadow, float posY, float Size)
{
	float fSize , fColA;
	//サイズ
	fSize = (posY / 2.0f) + Size;

	//α値
	fColA = (posY * -0.005f) + 0.5f;
	
	if (fColA <= 0.0f)
	{
		fColA = 0.0f;
	}
	else if (fColA >= 1.0f)
	{
		fColA = 1.0f;
	}

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * nIdxShadow;
	pVtx[0].pos = D3DXVECTOR3(-fSize, 0.0f, fSize);
	pVtx[1].pos = D3DXVECTOR3(fSize, 0.0f, fSize);
	pVtx[2].pos = D3DXVECTOR3(-fSize, 0.0f, -fSize);
	pVtx[3].pos = D3DXVECTOR3(fSize, 0.0f, -fSize);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fColA);

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// 影を消す
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	g_Shadow[nIdxShadow].bUse = false;
}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

}

