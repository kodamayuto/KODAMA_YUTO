//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "polygon.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_FILENAME0 "data/TEXTURE/field000.jpg"
#define POLYGON_FILENAME1 "data/TEXTURE/wall000.jpg"
#define MAX_POLYGON (1)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePolygon[2] = {};	    //テクスチャへのポインタ

POLYGON g_Polygon[MAX_POLYGON];

//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, POLYGON_FILENAME0, &g_pTexturePolygon[0]);
	D3DXCreateTextureFromFile(pDevice, POLYGON_FILENAME1, &g_pTexturePolygon[1]);

	MakeVertexPolygon(pDevice);

	//構造体の初期化
	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		g_Polygon[nCntPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[nCntPolygon].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Polygon[nCntPolygon].bUse = false;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// 頂点バッファの開放
	for (int nCntTex = 0; nCntTex < 2; nCntTex++)
	{
		if (g_pTexturePolygon[nCntTex] != NULL)
		{
			g_pTexturePolygon[nCntTex]->Release();
			g_pTexturePolygon[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	// ワールドマトリックスの初期化
	// ポリゴンの描画
	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		if (g_Polygon[nCntPolygon].bUse == true)
		{
			D3DXMatrixIdentity(&g_Polygon[nCntPolygon].g_mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Polygon[nCntPolygon].rot.y,
				g_Polygon[nCntPolygon].rot.x,
				g_Polygon[nCntPolygon].rot.z);

			D3DXMatrixMultiply(&g_Polygon[nCntPolygon].g_mtxWorld,
				&g_Polygon[nCntPolygon].g_mtxWorld,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Polygon[nCntPolygon].pos.x,
				g_Polygon[nCntPolygon].pos.y,
				g_Polygon[nCntPolygon].pos.z);

			D3DXMatrixMultiply(&g_Polygon[nCntPolygon].g_mtxWorld,
				&g_Polygon[nCntPolygon].g_mtxWorld,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Polygon[nCntPolygon].g_mtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

				// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePolygon[g_Polygon[nCntPolygon].type]);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				4 * nCntPolygon,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
		}
	}
}

//=============================================================================
// ポリゴンの設定
//=============================================================================
void SetPolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot,POLYGONTYPE type, float fWidth ,float fDepth)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		if (g_Polygon[nCntPolygon].bUse == false)
		{
			g_Polygon[nCntPolygon].pos = pos;
			g_Polygon[nCntPolygon].rot = rot;
			g_Polygon[nCntPolygon].fWidth = fWidth; 
			g_Polygon[nCntPolygon].fDepth = fDepth;
			g_Polygon[nCntPolygon].type = type;
			

			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += 4 * nCntPolygon;
			switch (g_Polygon[nCntPolygon].type)
			{
			case POLYGONTYPE_FIELD:
				pVtx[0].pos = D3DXVECTOR3(-g_Polygon[nCntPolygon].fWidth, 0.0f, g_Polygon[nCntPolygon].fDepth);
				pVtx[1].pos = D3DXVECTOR3(g_Polygon[nCntPolygon].fWidth, 0.0f, g_Polygon[nCntPolygon].fDepth);
				pVtx[2].pos = D3DXVECTOR3(-g_Polygon[nCntPolygon].fWidth, 0.0f, -g_Polygon[nCntPolygon].fDepth);
				pVtx[3].pos = D3DXVECTOR3(g_Polygon[nCntPolygon].fWidth, 0.0f, -g_Polygon[nCntPolygon].fDepth);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_Polygon[nCntPolygon].fWidth / 10.0f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, (g_Polygon[nCntPolygon].fDepth / 10.0f));
				pVtx[3].tex = D3DXVECTOR2((g_Polygon[nCntPolygon].fWidth / 10.0f), (g_Polygon[nCntPolygon].fDepth /10.0f));
			}


			//頂点バッファをアンロックする
			g_pVtxBuffPolygon->Unlock();
			g_Polygon[nCntPolygon].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	for (int nCntPolygon = 0; nCntPolygon < MAX_POLYGON; nCntPolygon++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntPolygon;

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
		g_pVtxBuffPolygon->Unlock();
	}
}

