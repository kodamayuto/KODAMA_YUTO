//=============================================================================
//
// 矢印処理[arrow.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "arrow.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ARROW_POLYGON_FILENAME "data/TEXTURE/Draw010_Icon000.png"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexArrow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;	    //テクスチャへのポインタ

D3DXVECTOR3 g_posArrow;		//位置
D3DXVECTOR3 g_rotArrow;		//向き
D3DXMATRIX	g_mtxWorldArrow;	//ワールドマトリックス

Arrow g_Arrow;

//=============================================================================
// 初期化処理
//=============================================================================
void InitArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXCreateTextureFromFile(pDevice, ARROW_POLYGON_FILENAME, &g_pTextureArrow);

	MakeVertexArrow(pDevice);

	//構造体の初期化
		g_Arrow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Arrow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Arrow.bUse = false;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitArrow(void)
{
	// 頂点バッファの開放
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateArrow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
												// ポリゴンの描画

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Arrow.mtxWorldArrow);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_Arrow.rot.y,
				g_Arrow.rot.x,
				g_Arrow.rot.z);

			D3DXMatrixMultiply(&g_Arrow.mtxWorldArrow,
				&g_Arrow.mtxWorldArrow,
				&mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_Arrow.pos.x,
				g_Arrow.pos.y,
				g_Arrow.pos.z);

			D3DXMatrixMultiply(&g_Arrow.mtxWorldArrow,
				&g_Arrow.mtxWorldArrow,
				&mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Arrow.mtxWorldArrow);

			pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

			pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定


				// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureArrow);//テクスチャの設定

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
				0,					   //開始する頂点のインデックス(基本０)
				2);		   	       //プリミティブの数
	

}
//=============================================================================
// 矢印の設定
//=============================================================================
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{

		if (g_Arrow.bUse == false)
		{
			g_Arrow.pos = pos;
			g_Arrow.rot = rot;
			g_Arrow.bUse = true;

		}

}
//=============================================================================
// 矢印の更新
//=============================================================================
void SetPositionArrow(D3DXVECTOR3 pos)
{
	MODEL *pModel;
	pModel = GetModel();
	g_Arrow.pos = pos;

	g_Arrow.rot.y = RotOverwhelming(atan2f(pModel->pos.x - g_Arrow.pos.x, pModel->pos.z - g_Arrow.pos.z));
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexArrow(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].pos = D3DXVECTOR3(-30.0f, 0.0f, 30.0f);
		pVtx[1].pos = D3DXVECTOR3(30.0f, 0.0f, 30.0f);
		pVtx[2].pos = D3DXVECTOR3(-30.0f, 0.0f, -30.0f);
		pVtx[3].pos = D3DXVECTOR3(30.0f, 0.0f, -30.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffArrow->Unlock();

}

