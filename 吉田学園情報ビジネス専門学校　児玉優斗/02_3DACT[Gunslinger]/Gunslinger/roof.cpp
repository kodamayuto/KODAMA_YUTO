//=============================================================================
//
// 壁処理[roof.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "roof.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ROOF_FILENAME0 "data/TEXTURE/wall000.jpg"
#define ROOF_FILENAME1 "data/TEXTURE/wall000.jpg"
#define MAX_ROOF (256)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRoof(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRoof = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRoof[2] = {};	    //テクスチャへのポインタ

ROOF g_Roof[MAX_ROOF];
//=============================================================================
// 初期化処理
//=============================================================================
void InitRoof(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, ROOF_FILENAME0, &g_pTextureRoof[0]);
	D3DXCreateTextureFromFile(pDevice, ROOF_FILENAME1, &g_pTextureRoof[1]);

	MakeVertexRoof(pDevice);

	//構造体の初期化
	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		g_Roof[nCntRoof].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Roof[nCntRoof].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Roof[nCntRoof].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRoof(void)
{
	// 頂点バッファの開放
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTextureRoof[nCntTex] != NULL)
		{
			g_pTextureRoof[nCntTex]->Release();
			g_pTextureRoof[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRoof != NULL)
	{
		g_pVtxBuffRoof->Release();
		g_pVtxBuffRoof = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRoof(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRoof(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	// ワールドマトリックスの初期化
	// ポリゴンの描画
	//pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		if (g_Roof[nCntRoof].bUse == true)
		{
			D3DXMatrixIdentity(&g_Roof[nCntRoof].g_mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Roof[nCntRoof].rot.y,
				g_Roof[nCntRoof].rot.x,
				g_Roof[nCntRoof].rot.z);

			D3DXMatrixMultiply(&g_Roof[nCntRoof].g_mtxWorld,
				&g_Roof[nCntRoof].g_mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Roof[nCntRoof].pos.x,
				g_Roof[nCntRoof].pos.y,
				g_Roof[nCntRoof].pos.z);

			D3DXMatrixMultiply(&g_Roof[nCntRoof].g_mtxWorld,
				&g_Roof[nCntRoof].g_mtxWorld,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Roof[nCntRoof].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffRoof, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRoof[0]);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntRoof,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ポリゴンの設定
//=============================================================================
void SetRoof(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ROOFTYPE type, float fWidth ,float fHaight)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		if (g_Roof[nCntRoof].bUse == false)
		{
			g_Roof[nCntRoof].pos = pos;
			g_Roof[nCntRoof].rot = rot;
			g_Roof[nCntRoof].fWidth = fWidth;
			g_Roof[nCntRoof].Haight = fHaight;
			g_Roof[nCntRoof].type = type;
			

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffRoof->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntRoof;
			switch (g_Roof[nCntRoof].type)
			{
			case ROOFTYPE_1:

				pVtx[0].pos = D3DXVECTOR3(-g_Roof[nCntRoof].fWidth, g_Roof[nCntRoof].Haight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Roof[nCntRoof].fWidth, g_Roof[nCntRoof].Haight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_Roof[nCntRoof].fWidth,0.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Roof[nCntRoof].fWidth, 0.0f, 0.0f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Roof[nCntRoof].fWidth / 100.0f) + 1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, (g_Roof[nCntRoof].Haight / 100.0f) + 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_Roof[nCntRoof].fWidth / 100.0f) + 1.0f, (g_Roof[nCntRoof].Haight / 100.0f) + 1.0f);
				break;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffRoof->Unlock();
			g_Roof[nCntRoof].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRoof(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ROOF,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRoof,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntRoof = 0; nCntRoof < MAX_ROOF; nCntRoof++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffRoof->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntRoof;

		pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		pVtx[1].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
		pVtx[2].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffRoof->Unlock();
	}
}

